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

#ifndef __CLIENT_MANAGER_H__
#define __CLIENT_MANAGER_H__

#include <ace/Singleton.h>
#include <ace/Null_Mutex.h>
#include <ace/Assert.h>

#include <set>
#include <string>
#include <cstdio>

#include "Client.h"

/**
 *  @brief  Basically just stores the connected clients.
 */
class ClientManager
{
    public:
        /**
         *  @brief  This type is for storing clients.
         */
        typedef std::set<Client*> Clients;

        /**
         *  @brief  Frees the resources which allocated by the stored clients.
         */
        ~ClientManager()
        {
            for (Clients::const_iterator itr = _clients.begin(); itr != _clients.end(); ++itr)
                delete *itr;
            _clients.clear();
        }

        /**
         *  @brief  Add a client to the container.
         */
        void Add(Client* newClient);
        /**
         *  @brief  Deletes a client from the container.
         */
        void Remove(Client* removedClient);

        /**
         *  @brief  Returns true if the given nickname is already exists
         *          Otherwise false.
         */
        bool IsNicknameExists(std::string const& nickname);

        Clients const& GetClients() { return _clients; }
        bool IsEmpty() const { return _clients.empty(); }

    private:
        Clients _clients;
};

/**
 *  @brief  ClientManager should be accessed by that macro.
 */
#define sClientManager ACE_Singleton<ClientManager, ACE_Null_Mutex>::instance()

#endif /* __CLIENT_MANAGER_H__ */
