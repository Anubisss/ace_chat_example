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

#include <shared/ConfigParser.h>

#include <cstdio>
#include <iostream> 

#include "Client.h"

// name of the client config file
#ifndef _CONFIG_CLIENT_
    #define _CONFIG_CLIENT_  "client.conf"
#endif /* _CONFIG_CLIENT_ */

// max length of the nickname
#define _NICKNAME_MAX_LENGTH_   64

// win32 workaround
void WaitForEnter()
{
    #ifdef WIN32
        printf("\n\nPlease press enter to exit.\n");
        getchar();
    #endif /* WIN32 */
    return;
}

int ACE_TMAIN(int argc, char **argv)
{
    // parsed the config
    if (!sConfigParser->Open(_CONFIG_CLIENT_))
    {
        printf("Can't open the config file: %s\n", _CONFIG_CLIENT_);
        WaitForEnter();
        return 1;
    }

    // gets the nickname from the config file if it's given
    std::string nickname = sConfigParser->GetString("Chat", "Nickname");

    // no nickname in the config file so let's ask one from the user
    while (nickname.empty())
    {
        char Nick[_NICKNAME_MAX_LENGTH_];
        printf("Nickname can't be empty. Please type one.\n");
        printf("Nickname: ");
        std::cin.getline(Nick, _NICKNAME_MAX_LENGTH_);
        nickname = std::string(Nick);
    }
    // sets the nickname
    sClient->SetNickname(nickname);

    // connects to the server
    sClient->Connect();

    WaitForEnter();
    return 0;
}
