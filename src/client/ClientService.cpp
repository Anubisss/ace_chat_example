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

#include <ace/INET_Addr.h>
#include <ace/Thread_Manager.h>
#include <ace/OS.h>

#include <shared/ConfigParser.h>
#include <shared/BasicTypes.h>
#include <shared/Opcode.h>

#include "ClientService.h"
#include "Client.h"

ClientService::ClientService() : _connector(NULL), _stream(NULL), _rawBuffer(NULL), _byteBuffer(NULL)
{
    _rawBuffer = new char[_BUFFER_SIZE_];
}

ClientService::~ClientService()
{
    delete _connector;
    delete _stream;
    delete [] _rawBuffer;
}

bool ClientService::Start()
{
    _connector = new ClientConnector();
    _stream = new ClientStream();

    if (_connector->connect(*_stream, ACE_INET_Addr(sConfigParser->GetString("Network", "ConnectAddress").c_str())) == -1)
    {
        printf("Can't connect to the server: %s\n", sConfigParser->GetString("Network", "ConnectAddress").c_str());
        ACE_ERROR((LM_ERROR, ACE_TEXT("%p\n"), ACE_TEXT("Error"))); 
        // don't have to free up connector and stream object
        // because it will be released in the destructor
        return false;
    }
    printf("Connected to: %s with Nickname: %s\n", sConfigParser->GetString("Network", "ConnectAddress").c_str(), sClient->GetNickname().c_str());

    // turns the task into an active object
    // so create a thread, check ::svc
    activate();
    return true;
}

/* virtual */ int ClientService::svc()
{
    // TODO: needs something like IsRunning()
    while (1)
    {
        ssize_t receivedBytes = _stream->recv(_rawBuffer, _BUFFER_SIZE_);

        // should ACE_Svc_Handler::handle_input used?
        if (receivedBytes  > 0)
        {
            // TODO: move that code to Client::Receive

            printf("Packet received: '%s'[%d bytes]\n", _rawBuffer, receivedBytes);

            _byteBuffer = new ByteBuffer();
            _byteBuffer->Append((uint8*)_rawBuffer, receivedBytes);

            uint8 opcode = -1;
            *_byteBuffer >> opcode;

            // handles the packet
            switch (opcode)
            {
                case S2C_CLIENT_HAS_JOINED:
                    HandleOpcodeClientHasJoined();
                    break;
                case S2C_CLIENT_HAS_QUIT:
                    HandleOpcodeClientHasQuit();
                    break;
                case S2C_SEND_MESSAGE:
                    HandleOpcodeMessageSend();
                    break;
                default:
                    printf("Received an unhandled opcode: %u\n", opcode);
                    ACE_ASSERT(false);
                    return -1;
            }
        }

        // be nice and sleep some, 10 ms
        ACE_OS::sleep(ACE_Time_Value(0, 10000));
    }
    return 0;
}

void ClientService::HandleOpcodeClientHasJoined()
{
    std::string nickname = "";
    *_byteBuffer >> nickname;
    delete _byteBuffer;

    printf("%s has joined\n", nickname.c_str());
}

void ClientService::HandleOpcodeClientHasQuit()
{
    std::string leaverNickname = "";
    *_byteBuffer >> leaverNickname;
    delete _byteBuffer;

    printf("%s has quit\n", leaverNickname.c_str());
}

void ClientService::HandleOpcodeMessageSend()
{
    std::string senderNickname = "";
    std::string message = "";
    *_byteBuffer >> senderNickname;
    *_byteBuffer >> message;
    delete _byteBuffer;

    printf("[%s] %s\n", senderNickname.c_str(), message.c_str());
}
