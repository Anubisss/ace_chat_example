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

#ifndef __CLIENT_SERVICE_H__
#define __CLIENT_SERVICE_H__

#include <ace/Singleton.h>
#include <ace/Null_Mutex.h>
#include <ace/Task.h>
#include <ace/SOCK_Connector.h>
#include <ace/SOCK_Stream.h>
#include <ace/Time_Value.h>

#include <shared/ByteBuffer.h>

/**
 *  @brief  This connector connects to a remote address/port via TCP/IP.
 */
typedef ACE_SOCK_Connector ClientConnector;
/**
 * @brief  This stream is a buffer which receives and sends the packets.
 */
typedef ACE_SOCK_Stream ClientStream;

#define _BUFFER_SIZE_   128

class ClientService : public ACE_Task_Base
{
    public:
        ClientService();
        ~ClientService();

        /**
         *  @brief  Start the client service.
         *          The service's main loop is svc().
         *  @see    svc()
         */
        bool Start();

        /**
         *  @brief  Main loop of the client service, running on seperate thread.
         */
        /* virtual */ int svc();

        /**
         *  @brief  Returns the stream object.
         *          This should be used from the Client to send packets.
         */
        ClientStream* GetStream() const { return _stream; }

        /**
         *  @brief  Called if a client connected.
         *  @todo   This should be moved to class Client.
         *  @see    Client
         */
        void HandleOpcodeClientHasJoined();
        /**
         *  @brief  Called if a client disconnected.
         *  @todo   This should be moved to class Client.
         *  @see    Client
         */
        void HandleOpcodeClientHasQuit();
        /**
         *  @brief  Called if a client sended a message.
         *  @todo   This should be moved to class Client.
         *  @see    Client
         */
        void HandleOpcodeMessageSend();

    private:
        ClientConnector* _connector;
        ClientStream* _stream;

        /**
         *  @brief  This raw buffer stores the bytes which are received.
         */
        char* _rawBuffer;
        /**
         *  @brief  This byte buffer is filling from from _rawBuffer.
         *          Contains the actually received packet.
         */
        ByteBuffer* _byteBuffer;
};

/**
 *  @brief  ClientService should be access via this macro.
 */
#define sClientService ACE_Singleton<ClientService, ACE_Null_Mutex>::instance()

#endif /* __CLIENT_SERVICE_H__ */
