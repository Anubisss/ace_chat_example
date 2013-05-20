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

#ifndef __SERVER_H__
#define __SERVER_H__

#include <ace/Singleton.h>
#include <ace/Null_Mutex.h>

#include <list>

#include <shared/Packet.h>
#include <shared/ByteBuffer.h>

#include "Client.h"

/**
 *  @brief  Packets should be sended to clients via this class.
 */
class Server
{
    public:
        /**
         *  @brief  This type is used to store all the connected clients.
         */
        typedef std::list<Client*> ClientsList;

        /**
         *  @brief  Sends the given packet to all the connected clients except to skippedClient.
         */
        size_t BroadcastPacket(Packet const& pkt, Client const* skippedClient = NULL);
        /**
         *  @brief  Sends the specific packet to a specific client.
         */
        ssize_t SendPacket(Packet const& pkt, Client const* target);
        /**
         *  @brief  "Low level" implementation of packet sending.
         */
        ssize_t Send(ByteBuffer const& buffer, Client const* target);
};

/**
 *  @brief  Access Server class via this macro.
 */
#define sServer ACE_Singleton<Server, ACE_Null_Mutex>::instance()

#endif /* __SERVER_H__ */
