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

#include <cstdio>
#include <cstring>

#include <shared/BasicTypes.h>

#include "CommandLineInterface.h"
#include "Client.h"

#define _COMMAND_LINE_BUFFER_SIZE_ 256

/* virtual */ int CommandLineInterface::svc()
{
    while (1)
    {
        char* buffer = new char[_COMMAND_LINE_BUFFER_SIZE_];
        printf("Message: ");

        fgets(buffer, _COMMAND_LINE_BUFFER_SIZE_, stdin);

        // doesn't empty
        if (buffer != NULL && strcmp(buffer, "\n"))
        {
            for (uint8 i = 0; buffer[i]; ++i)
            {
                if (buffer[i] == '\n')
                {
                    buffer[i] = '\0';
                    break;
                }
            }
            // send the message
            sClient->SendMessage(buffer);
        }
        delete [] buffer;
    }
    return 0;
}
