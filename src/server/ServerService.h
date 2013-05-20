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

#ifndef __SERVER_SERVICE_H__
#define __SERVER_SERVICE_H__

#include <ace/Singleton.h>
#include <ace/Null_Mutex.h>
#include <ace/Task.h>
#include <ace/Acceptor.h>
#include <ace/SOCK_Acceptor.h>

#include "ClientSocket.h"

/**
 *  @brief  Defines the acceptor.
 *          A ClientSocket object will be created if a client has connected to the server.
 */
typedef ACE_Acceptor<ClientSocket, ACE_SOCK_Acceptor> ServerAcceptor;

class ServerService : public ACE_Task_Base
{
    public:
        ServerService() : _acceptor(NULL), _isRunning(false) {}
        ~ServerService()
        {
            Cleanup();
        }

        /**
         *  @brief  Starts the service.
         */
        void Start();
        /**
         *  @brief  Stops the service.
         */
        void Stop();

        /**
         *  @brief  Releases the resources.
         */
        void Cleanup();

        /**
         *  @brief  Main loop.
         */
        /* virtual */ int svc();

    private:
        ServerAcceptor* _acceptor;

        /**
         *  @brief  True if the server is running.
         *          If false server should be shutdowned.
         */
        bool _isRunning;
};

/**
 *  @brief  Server service should be accessed via this macro.
 */
#define sServerService ACE_Singleton<ServerService, ACE_Null_Mutex>::instance()

#endif /* __SERVER_SERVICE_H__ */
