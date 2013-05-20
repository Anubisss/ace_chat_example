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

#include <ace/OS.h>
#include <ace/SString.h>
#include <ace/Configuration_Import_Export.h>

#include <cstdio>
#include <cstdlib>

#include "ConfigParser.h"

bool ConfigParser::Open(std::string const& path)
{
    _configPath = path;

    _config.open();
    if (!Reload())
        return false;

    return true;
}

bool ConfigParser::Reload()
{
    // imports the configuration database from filename as strings
    ACE_Ini_ImpExp importer(_config);

    if (importer.import_config(_configPath.c_str()) == -1)
        return false; // Can't open the config file

    return true;
}

std::string ConfigParser::GetString(std::string const& section, std::string const& key)
{
    ACE_TString str;
    ACE_Configuration_Section_Key configSection;

    if (_config.open_section(_config.root_section(), ACE_TEXT(section.c_str()), 0, configSection) == -1)
    {
        printf("Config file: %s doesn't contain this section: [%s]\n", _configPath.c_str(), section.c_str());
        exit(1);
    }
    else if (_config.get_string_value(configSection, key.c_str(), str) == -1)
    {
        printf("Config file(%s)'s section: [%s] doesn't contain this key: %s\n", _configPath.c_str(), section.c_str(), key.c_str());
        exit(1);
    }

    return std::string(str.c_str());
}

int ConfigParser::GetInt(std::string const& section, const std::string& key)
{
    std::string stringValue = GetString(section, key);
    int intValue = ACE_OS::atoi(stringValue.c_str());
    return intValue;
}
