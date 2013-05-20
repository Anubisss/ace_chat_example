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

#include <ace/Signal.h>

#include "ServerSignalHandler.h"

/* virtual */ int ServerSignalHandler::handle_signal(int sigNum, siginfo_t* /* = NULL */, ucontext_t* /* = NULL */)
{
    // makes sure the right handler called back
    ACE_ASSERT(sigNum == _sigNum);

    printf("ServerSignalHandler: %s (%d) occured\n", GetSignalName(sigNum).c_str(), sigNum);
    // stops the main loop
    ACE_Reactor::instance()->end_reactor_event_loop();
    return 0;
}

std::string ServerSignalHandler::GetSignalName(int sigNum)
{
    std::string sigNumName;

    switch (sigNum)
    {
        case SIGINT:    sigNumName = "SIGINT";      break;
        #ifdef WIN32
        case SIGBREAK:  sigNumName = "SIGBREAK";    break;
        #endif /* WIN32 */
        default:        ACE_ASSERT(false);          break;
    }

    return sigNumName;
}
