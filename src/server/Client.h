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

#include <ace/SOCK_Stream.h>
#include <ace/Assert.h>

#include <string>

/**
 *  @brief  Represents a connected client.
 */
class Client
{
    public:
        Client(std::string nickname, ACE_SOCK_Stream* stream)
        {
            _nickname = nickname;
            _stream = stream;
        }

        std::string const& GetName() const { return _nickname; }

        ACE_SOCK_Stream* GetStream() const { ACE_ASSERT(_stream); return _stream; }

    private:
        /**
         *  @brief  Client's nickname. Specified by the client via C2S_NICKNAME packet.
         */
        std::string _nickname;
        /**
         *  @brief  Packets should sended to a client via this stream.
         */
        ACE_SOCK_Stream* _stream;
};

#endif /* __CLIENT_H__ */
