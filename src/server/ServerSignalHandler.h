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

#ifndef __SERVER_SIGNAL_HANDLER_H__
#define __SERVER_SIGNAL_HANDLER_H__

#include <ace/Event_Handler.h>
#include <ace/Assert.h>
#include <ace/Reactor.h>

#include <string>

/**
 *  @brief  This signal handler will stops the server's loop.
 */
class ServerSignalHandler : public ACE_Event_Handler
{
    public:
        ServerSignalHandler(int sigNum) : _sigNum(sigNum) {}

        /**
         *  @brief  Called when the specific signal occured.
         */
        /* virtual */ int handle_signal(int sigNum, siginfo_t* = NULL, ucontext_t* = NULL);

        /**
         *  @brief  Returns the specific signal's name.
         */
        std::string GetSignalName(int sigNum);

    private:
        /**
         *  @brief  Stores the signal's numeric code.
         */
        int _sigNum;
};

#endif /* __SERVER_SIGNAL_HANDLER_H__ */
