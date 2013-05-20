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

#include "ClientManager.h"

void ClientManager::Add(Client* newClient)
{
    ACE_ASSERT(newClient);

    printf("ClientManager:\tClient: '%s' added.\n", newClient->GetName().c_str());
    _clients.insert(newClient);
}

void ClientManager::Remove(Client* removedClient)
{
    ACE_ASSERT(removedClient);

    printf("ClientManager:\tClient: '%s' removed.\n", removedClient->GetName().c_str());
    _clients.erase(removedClient);
    delete removedClient;
}

bool ClientManager::IsNicknameExists(std::string const& nickname)
{
    for (Clients::const_iterator itr = _clients.begin(); itr != _clients.end(); ++itr)
    {
        if ((*itr)->GetName() == nickname)
            return true;
    }
    return false;
}
