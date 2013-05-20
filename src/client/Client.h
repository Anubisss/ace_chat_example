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

#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <ace/Singleton.h>
#include <ace/Null_Mutex.h>

#include <string>

#include <shared/ByteBuffer.h>
#include <shared/Packet.h>

/**
 *  @brief  Implements the client class.
 *          This class should be used to send packets to the server.
 */
class Client
{
    public:
        Client() : _nickname("") {}
        ~Client() {};

        void SetNickname(std::string nickname) { _nickname = nickname; }
        std::string GetNickname() const { return _nickname; }

        /**
         *  @brief  Connects to the server.
         *          This is the client's "main loop".
         */
        void Connect();

        /**
         *  @brief  Sends a packet to the server.
         */
        ssize_t SendPacket(Packet const& pkt);

        /**
         *  @brief  Sends a simple message (text) to the server.
         */
        size_t SendMessage(const char* msg);

    private:
        /**
         *  @brief  Sends the nickname to the server.
         */
        void Authorize();

        /**
         *  @brief  "Low level" implementation of packet sending.
         */
        ssize_t Send(ByteBuffer const& buffer);

        /**
         *  @brief  Nickname.
         */
        std::string _nickname;
};

/**
 *  @brief  Client should be access via this macro.
 */
#define sClient ACE_Singleton<Client, ACE_Null_Mutex>::instance()

#endif /* __CLIENT_H__ */
