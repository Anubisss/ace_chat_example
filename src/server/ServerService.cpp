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

#include <ace/Thread_Manager.h>
#include <ace/INET_Addr.h>
#include <ace/Log_Msg.h>
#include <ace/Reactor.h>

#include <cstdio>

#include <shared/ConfigParser.h>

#include "ServerService.h"

void ServerService::Start()
{
    _acceptor = new ServerAcceptor();

    // binds
    if (_acceptor->open(ACE_INET_Addr(sConfigParser->GetString("Network", "BindAddress").c_str())) == -1)
    {
        printf("Can't bind to: %s\n", sConfigParser->GetString("Network", "BindAddress").c_str());
        ACE_ERROR((LM_ERROR, ACE_TEXT("%p\n"), ACE_TEXT("Error")));
        // don't have to free _acceptor because it's released by Cleanup()
        return;
    }

    activate();

    ACE_Thread_Manager::instance()->wait();
}

void ServerService::Stop()
{
    _isRunning = false;
    Cleanup();
}

void ServerService::Cleanup()
{
    delete _acceptor;
}

/* virtual */ int ServerService::svc()
{
    _isRunning = true;
    ACE_Reactor::instance()->owner(ACE_Thread_Manager::instance()->thr_self());
    ACE_Reactor::instance()->run_reactor_event_loop();
    return 0;
}
