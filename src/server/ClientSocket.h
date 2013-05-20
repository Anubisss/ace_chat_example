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

#ifndef __CLIENT_SOCKET_H__
#define __CLIENT_SOCKET_H__

#include <ace/Svc_Handler.h>
#include <ace/SOCK_Stream.h>
#include <ace/Synch_Traits.h>

#include <shared/ByteBuffer.h>

#include "Client.h"

#define _BUFFER_SIZE_   128

/**
 *  @brief  Basically this object is created for every newly connected clients.
 */
class ClientSocket : public ACE_Svc_Handler<ACE_SOCK_Stream, ACE_MT_SYNCH>
{
    public:
        ClientSocket();

        /**
         *  @brief  Calls when the connection, client creation occurs.
         */
        /* virtual */ int open(void*);

        /**
         *  @brief  Calls when the client sends some packet.
         */
        /* virtual */ int handle_input(ACE_HANDLE);

        /**
         *  @brief  Calls when the client has disconnected.
         */
        /* virtual */ int handle_close(ACE_HANDLE, ACE_Reactor_Mask mask);

        /**
         *  @brief  Calls when C2S_NICKNAME packet receives.
         *          Basically this is an "authentication" method.
         */
        void HandleOpcodeNickname();
        /**
         *  @brief  Calls when C2S_SEND_MESSAGE receives.
         *          When a client sends a messsage to he server this is called on all clients.
         */
        void HandleOpcodeSendMessage();

    private:
        char* _rawBuffer;
        ByteBuffer* _byteBuffer;

        Client* _client;
};

#endif /* __CLIENT_SOCKET_H__ */
