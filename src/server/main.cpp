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

#include <ace/Sig_Handler.h>
#include <ace/Signal.h>

#include <cstdio>

#include <shared/ConfigParser.h>

#include "ServerService.h"
#include "ServerSignalHandler.h"
#include "ClientManager.h"

#ifndef _CONFIG_SERVER_
    #define _CONFIG_SERVER_  "server.conf"
#endif /* _CONFIG_SERVER_ */

void WaitForEnter()
{
    #ifdef WIN32
        printf("\n\nPlease press enter to exit.");
        getchar();
    #endif /* WIN32 */
    return;
}

int ACE_TMAIN(int argc, char **argv)
{
    if (!sConfigParser->Open(_CONFIG_SERVER_))
    {
        printf("Can't open the config file: %s\n", _CONFIG_SERVER_);
        WaitForEnter();
        return 1;
    }

    // creates the signal handlers
    ServerSignalHandler SignalINT(SIGINT);
    #ifdef WIN32
    ServerSignalHandler SignalBREAK(SIGBREAK);
    #endif /* WIN32 */

    // registers the signal handlers
    ACE_Sig_Handler handler;
    handler.register_handler(SIGINT, &SignalINT);
    #ifdef WIN32
    handler.register_handler(SIGBREAK, &SignalBREAK);
    #endif /* WIN32 */

    // starts the server
    sServerService->Start();

    return 0;
}
