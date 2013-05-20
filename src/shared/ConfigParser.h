/*
 * This file is part of ace_chat_example.
 *
 * ace_chat_example is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * ace_chat_example is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with ace_chat_example.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __CONFIG_PARSER_H__
#define __CONFIG_PARSER_H__

#include <ace/Singleton.h>
#include <ace/Null_Mutex.h>
#include <ace/Configuration.h>

#include <string>

/**
 *  @brief  Parses a config file.
 */
class ConfigParser
{
    public:
        /**
         *  @brief  Opens the config file via the given path.
         *  @return True on success false on failure.
         */
        bool Open(std::string const& path);
        /**
         *  @brief  Reloads the config which means re-opens the file and re-parses.
         *  @return True on success false on failure.
         */
        bool Reload();

        /**
         *  @brief  Gets a string value from a specific section with the given key.
         *          Example:
         *                   [eg_section]
         *                   egKey = eg string
         */
        std::string GetString(std::string const& section, std::string const& key);
        /**
         *  @brief  Gets an int value.
         */
        int GetInt(std::string const& section, const std::string& key);

    private:
        /**
         *  @brief  Path of the config file.
         *  @note   It can be just a simple file name.
         */
        std::string _configPath;

        /**
         *  @brief  An allocator based configuration database
                    implemented in the ACE framework.
         */
        ACE_Configuration_Heap _config;
};

/**
 *  @brief  ConfigParser should be accessed via this macro.
 */
#define sConfigParser ACE_Singleton<ConfigParser, ACE_Null_Mutex>::instance()

#endif /* __CONFIG_PARSER_H__ */
