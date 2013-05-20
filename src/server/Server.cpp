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

#include <ace/Assert.h>

#include <cstdio>

#include "Server.h"
#include "ClientManager.h"

size_t Server::BroadcastPacket(Packet const& pkt, Client const* skippedClient /* = NULL */)
{
    // number of the clients which will receive this packet
    size_t count = 0;
    for (ClientManager::Clients::const_iterator itr = sClientManager->GetClients().begin(); itr != sClientManager->GetClients().end(); ++itr)
    {
        if (!skippedClient || skippedClient != *itr)
        {
            SendPacket(pkt, *itr);
            ++count;
        }
    }
    return count;
}

ssize_t Server::SendPacket(Packet const& pkt, Client const* target)
{
    ACE_ASSERT(target);

    ByteBuffer buffer;
    buffer << pkt.GetOpcode();
    buffer.Append(pkt); // copy the packet's content to the buffer

    printf("Packet [0x%X] sended '%s' [%u bytes] to client: %s\n", pkt.GetOpcode(), pkt.GetContent(), pkt.GetSize(), target->GetName().c_str());

    return Send(buffer, target);
}

ssize_t Server::Send(ByteBuffer const& buffer, Client const* target)
{
    ACE_ASSERT(target);
    printf("Bytes sended: '%s' [%u bytes] to client: %s\n", buffer.GetContent(), buffer.GetSize(), target->GetName().c_str());
    return target->GetStream()->send(buffer.GetContent(), buffer.GetSize());
}
