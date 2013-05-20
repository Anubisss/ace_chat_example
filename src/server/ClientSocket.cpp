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
#include <ace/Reactor.h>
#include <ace/Assert.h>
#include <ace/Event_Handler.h>

#include <string>

#include <shared/BasicTypes.h>
#include <shared/Opcode.h>

#include "ClientSocket.h"
#include "ClientManager.h"
#include "Server.h"

ClientSocket::ClientSocket() : _rawBuffer(NULL), _byteBuffer(NULL), _client(NULL)
{
    _rawBuffer = new char[_BUFFER_SIZE_];
}

/* virtual */ int ClientSocket::open(void*)
{
    ACE_INET_Addr clientAddress;
    if (peer().get_remote_addr(clientAddress) == -1)
        return -1;

    if (ACE_Reactor::instance()->register_handler(this, ACE_Event_Handler::READ_MASK) == -1)
        return -1;

    printf("ClientSocket:\tA client connected from %s:%u, host: %s\n", clientAddress.get_host_addr(), clientAddress.get_port_number(), clientAddress.get_host_name());

    return 0;
}

/* virtual */ int ClientSocket::handle_input(ACE_HANDLE)
{
    ACE_OS::memset(_rawBuffer, 0, _BUFFER_SIZE_);
    ssize_t receivedBytes = peer().recv(_rawBuffer, _BUFFER_SIZE_);
    if (receivedBytes < 1)
        return -1;

    printf("ClientSocket:\tBytes received: '%s' [%d bytes]\n", _rawBuffer, receivedBytes);

    // the resource should be deallocated in the handlers
    _byteBuffer = new ByteBuffer();
    _byteBuffer->Append((uint8*)_rawBuffer, receivedBytes);

    uint8 opcode = -1;
    *_byteBuffer >> opcode;

    // handles the packet
    switch (opcode)
    {
        case C2S_NICKNAME:
            HandleOpcodeNickname();
            break;
        case C2S_SEND_MESSAGE:
            HandleOpcodeSendMessage();
            break;
        default:
            printf("ClientSocket:\tReceived an unhandled opcode: %u\n", opcode);
            ACE_ASSERT(false);
            return -1;
    }

    return 0;
}

void ClientSocket::HandleOpcodeNickname()
{
    std::string nickname = "";
    *_byteBuffer >> nickname;
    delete _byteBuffer;

    _client = new Client(nickname, &peer());

    // Broadcasts when at least one client has connected
    if (!sClientManager->IsEmpty())
    {
        Packet pkt(S2C_CLIENT_HAS_JOINED);
        pkt << nickname;
        sServer->BroadcastPacket(pkt, _client);
    }

    // adds the client
    sClientManager->Add(_client);
}

void ClientSocket::HandleOpcodeSendMessage()
{
    std::string message = "";
    *_byteBuffer >> message;
    delete _byteBuffer;

    printf("ClientSocket:\tReceived a message: '%s' from: '%s'\n", message.c_str(), _client->GetName().c_str());

    Packet pkt(S2C_SEND_MESSAGE);
    pkt << _client->GetName();
    pkt << message;
    sServer->BroadcastPacket(pkt, _client);
}

/* virtual */ int ClientSocket::handle_close(ACE_HANDLE, ACE_Reactor_Mask mask)
{
    // FIXME: _client can be NULL if HandleOpcodeNickname() not called
    ACE_ASSERT(_client);

    // ALL_EVENTS_MASK setted when the server shuts down
    if (mask != ACE_Event_Handler::ALL_EVENTS_MASK)
    {
        std::string clientName = _client->GetName();

        // removes the client
        sClientManager->Remove(_client);

        Packet pkt(S2C_CLIENT_HAS_QUIT);
        pkt << clientName;
        sServer->BroadcastPacket(pkt);
    }

    delete [] _rawBuffer;

    destroy();
    return 0;
}
