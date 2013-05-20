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

#ifndef __COMMAND_LINE_INTERFACE_H__
#define __COMMAND_LINE_INTERFACE_H__

#include <ace/Task.h>
#include <ace/Singleton.h>
#include <ace/Null_Mutex.h>

/**
 *  @brief  This is a basic CLI to send messages to the server.
 */
class CommandLineInterface : public ACE_Task_Base
{
    public:
        /**
         *  @brief  Starts the CLI thread.
         */
        void Start()
        {
            // activates the main loop
            activate();
        }

        /**
         *  @brief  Main loop of the CLI.
         *          Message processing should be here.
         */
        /* virtual */ int svc();
};

/**
 *  @brief  This macro should used to access that class.
 */
#define sCommandLineInterface ACE_Singleton<CommandLineInterface, ACE_Null_Mutex>::instance()

#endif /* __COMMAND_LINE_INTERFACE_H__ */
