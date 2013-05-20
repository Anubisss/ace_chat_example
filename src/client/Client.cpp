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

#include <ace/OS.h>
#include <ace/Assert.h>
#include <ace/Thread_Manager.h>

#include <shared/ConfigParser.h>
#include <shared/Opcode.h>

#include "Client.h"
#include "ClientService.h"
#include "CommandLineInterface.h"

void Client::Connect()
{
    if (!sClientService->Start())
        return;

    Authorize();
    sCommandLineInterface->Start();

    ACE_Thread_Manager::instance()->wait();
}

void Client::Authorize()
{
    Packet data(C2S_NICKNAME);
    data << _nickname;

    SendPacket(data);
}

ssize_t Client::SendPacket(Packet const& pkt)
{
    ByteBuffer buffer;
    buffer << pkt.GetOpcode();
    buffer.Append(pkt); // copies the packet's content to the buffer

    printf("Packet[0x%X] sended '%s'[%u bytes]\n", pkt.GetOpcode(), pkt.GetContent(), pkt.GetSize());

    return Send(buffer);
}

ssize_t Client::Send(ByteBuffer const& buffer)
{
    printf("Bytes sended: '%s'[%u bytes]\n", buffer.GetContent(), buffer.GetSize());
    return sClientService->GetStream()->send(buffer.GetContent(), buffer.GetSize());
}

size_t Client::SendMessage(const char* msg)
{
    Packet data(C2S_SEND_MESSAGE);
    data << msg; // char*

    SendPacket(data);
    return ACE_OS::strlen(msg);
}
