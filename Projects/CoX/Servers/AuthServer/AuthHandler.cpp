#include "AuthHandler.h"

#include "AuthProtocol/AuthLink.h"
#include "AuthProtocol/AuthEvents.h"
#include "AuthClient.h"
#include "AdminServer/AccountInfo.h"
#include "Servers/AdminServerInterface.h"
#include "Servers/ServerManager.h"
#include "Servers/InternalEvents.h"

void AuthHandler::dispatch( SEGSEvent *ev )
{
    assert(ev);
    switch(ev->type())
    {
        case SEGS_EventTypes::evConnect:
            on_connect(static_cast<ConnectEvent *>(ev));
            break;
        case evLogin:
            on_login(static_cast<LoginRequest *>(ev));
            break;
        case evServerListRequest:
            on_server_list_request(static_cast<ServerListRequest *>(ev));
            break;
        case evServerSelectRequest:
            on_server_selected(static_cast<ServerSelectRequest *>(ev));
            break;
        case evDbError:
            // client sends this on exit sometimes ?
            on_disconnect(static_cast<DisconnectEvent *>(ev));
            break;
        case SEGS_EventTypes::evDisconnect:
            on_disconnect(static_cast<DisconnectEvent *>(ev));
            break;
            //////////////////////////////////////////////////////////////////////////
            //  Events from other servers
            //////////////////////////////////////////////////////////////////////////
        case Internal_EventTypes::evClientExpected:
            on_client_expected(static_cast<ClientExpected *>(ev)); break;
        default:
            assert(!"Unknown event encountered in dispatch.");
    }
}
SEGSEvent *AuthHandler::dispatchSync( SEGSEvent * )
{
    assert(!"No sync events known");
    return nullptr;
}

void AuthHandler::on_connect( ConnectEvent *ev )
{
    // TODO: guard for link state update ?
    AuthLink *lnk=static_cast<AuthLink *>(ev->src());
    assert(lnk!=nullptr);
    if(lnk->m_state!=AuthLink::INITIAL)
    {
        ACE_ERROR((LM_ERROR,ACE_TEXT ("(%P|%t) %p\n"),  ACE_TEXT ("Multiple connection attempts from the same addr/port")));
    }
    lnk->m_state=AuthLink::CONNECTED;
    uint32_t seed = 0x1; //TODO: rand()
    lnk->init_crypto(30206,seed);
    ACE_DEBUG((LM_WARNING,ACE_TEXT("(%P|%t) Crypto seed %08x\n"), seed ));
    lnk->putq(new AuthorizationProtocolVersion(this,30206,seed));
}
void AuthHandler::on_disconnect( DisconnectEvent *ev )
{
    AuthLink *lnk=static_cast<AuthLink *>(ev->src());
    AdminServerInterface *adminserv;
    adminserv = ServerManager::instance()->GetAdminServer();
    if(lnk->client())
    {
        lnk->client()->link_state().setState(ClientLinkState::NOT_LOGGED_IN);
        adminserv->Logout(lnk->client()->account_info());
        m_link_store[lnk->client()->account_info().account_server_id()] = nullptr;
        //if(lnk->m_state!=AuthLink::CLIENT_AWAITING_DISCONNECT)
    }
    else
    {
        ACE_DEBUG((LM_WARNING,ACE_TEXT("(%P|%t) Client disconnected without a valid login attempt. Old client ?\n")));
    }
}
void AuthHandler::no_admin_server(EventProcessor *lnk)
{
    lnk->putq(new AuthorizationError(this,4));
}
void AuthHandler::unknown_error(EventProcessor *lnk)
{
    lnk->putq(new AuthorizationError(this,AUTH_UNKN_ERROR));
}
void AuthHandler::auth_error(EventProcessor *lnk,uint32_t code)
{
    lnk->putq(new AuthorizationError(this,code));
}
void AuthHandler::on_login( LoginRequest *ev )
{
    AdminServerInterface *adminserv = ServerManager::instance()->GetAdminServer();
    AuthServerInterface *authserv = ServerManager::instance()->GetAuthServer();
    AuthClient *client = nullptr;
    AuthLink *lnk = static_cast<AuthLink *>(ev->src());
    assert(adminserv);
    assert(authserv); // if this fails it means we were not created.. ( AuthServer is creation point for the Handler)

    if(!adminserv)
        return no_admin_server(lnk); // we cannot do much without that

    if(lnk->m_state!=AuthLink::CONNECTED)
        return unknown_error(lnk);

    ACE_DEBUG ((LM_DEBUG,ACE_TEXT ("(%P|%t) User %s trying to login from %s.\n"),ev->login,lnk->peer_addr().get_host_addr()));
    if(strlen(ev->login)<=2)
        return auth_error(lnk,AUTH_ACCOUNT_BLOCKED); // invalid account

    client = authserv->GetClientByLogin(ev->login);
    // TODO: Version 0.3 will need to use admin tools instead of creating accounts willy-nilly
    if(!client) // no client exists, create one ( step 3c )
    {
        adminserv->SaveAccount(ev->login,ev->password); // Autocreate/save account to DB
        client = authserv->GetClientByLogin(ev->login);
    }
    if(!client) {
        ACE_ERROR ((LM_ERROR,ACE_TEXT ("(%P|%t) User %s from %s - couldn't get/create account.\n"),ev->login,lnk->peer_addr().get_host_addr()));
        return auth_error(lnk,AUTH_DATABASE_ERROR);
    }

    AccountInfo & acc_inf(client->account_info());  // all the account info you can eat!
    lnk->client(client);                            // now link knows what client it's responsible for
    client->link_state().link(lnk);                 // and client knows what link it's using
    eAuthError err = AUTH_WRONG_LOGINPASS;          // this is default for case we don't have that client
    bool no_errors=false;                           // this flag is set if there were no errors during client pre-processing
    // pre-process the client, check if the account isn't blocked, or if the account isn't already logged in
    ACE_DEBUG ((LM_DEBUG,ACE_TEXT ("\t\tid : %I64u\n"),acc_inf.account_server_id()));
    // step 3d: checking if this account is blocked
    if(client->account_blocked())
        err = AUTH_ACCOUNT_BLOCKED;
    else if(client->isLoggedIn())
    {
        // step 3e: asking game server connection check
        // TODO: client->forceGameServerConnectionCheck();
        err = AUTH_ALREADY_LOGGEDIN;
    }
    else if(client->link_state().getState()==ClientLinkState::NOT_LOGGED_IN)
        no_errors = true;
    // if there were no errors and the provided password is valid and admin server has logged us in.
    if(
            no_errors &&
            adminserv->ValidPassword(acc_inf,ev->password) &&
            adminserv->Login(acc_inf,lnk->peer_addr()) // this might fail somehow
            )
    {
        // inform the client of the successful login attempt
        ACE_DEBUG ((LM_DEBUG,ACE_TEXT ("\t\t : succeeded\n")));
        client->link_state().setState(ClientLinkState::LOGGED_IN);
        lnk->m_state = AuthLink::AUTHORIZED;
        lnk->putq(new LoginResponse());
        m_link_store[acc_inf.account_server_id()] = lnk; // remember client link
    }
    else
    {
        ACE_DEBUG ((LM_DEBUG,ACE_TEXT ("\t\t : failed\n")));
        auth_error(lnk,err);
    }
}
void AuthHandler::on_server_list_request( ServerListRequest *ev )
{
    AuthLink *lnk=static_cast<AuthLink *>(ev->src());
    if(lnk->m_state!=AuthLink::AUTHORIZED)
    {
        unknown_error(lnk);
        return;
    }
    ACE_DEBUG ((LM_DEBUG,ACE_TEXT ("(%P|%t) Client requesting server list\n")));
    lnk->m_state = AuthLink::CLIENT_SERVSELECT;
    ServerListResponse *r=new ServerListResponse;
    const ServerManagerC::dGameServer *servers = ServerManager::instance()->getGameServerList();
    std::deque<GameServerInfo> info;
    for(size_t idx=0; idx<servers->size(); ++idx) {
        GameServerInfo inf;
        GameServerInterface *iface = servers->at(idx);
        inf.id=iface->getId();
        inf.addr = iface->getAddress().get_ip_address();
        inf.port = iface->getAddress().get_port_number();
        inf.unknown_1 = iface->getUnkn1();
        inf.unknown_2 = iface->getUnkn2();
        inf.current_players = iface->getCurrentPlayers();
        inf.max_players = iface->getMaxPlayers();
        inf.online = iface->Online();
        info.push_back(inf);
    }
    r->set_server_list(info);
    lnk->putq(r);
}
void AuthHandler::on_server_selected(ServerSelectRequest *ev)
{
    AuthLink *lnk=static_cast<AuthLink *>(ev->src());
    if(lnk->m_state!=AuthLink::CLIENT_SERVSELECT)
    {
        unknown_error(lnk);
        return;
    }
    ACE_ERROR ((LM_DEBUG,ACE_TEXT ("(%P|%t) Client selected server %d!\n"),ev->m_server_id));
    GameServerInterface *gs = ServerManager::instance()->GetGameServer(ev->m_server_id-1);
    gs->event_target();
    if(!gs)
    {
        ACE_ERROR ((LM_DEBUG,ACE_TEXT ("(%P|%t) Client selected non existant server !\n")));
        auth_error(lnk,rand()%33);
        return;
    }
    AuthClient *cl= lnk->client();
    cl->setSelectedServer(gs);
    AccountInfo &acc_inf(cl->account_info());
    ExpectClient *cl_ev=new ExpectClient(this,acc_inf.account_server_id(),acc_inf.access_level(),cl->link_state().getPeer());
    gs->event_target()->putq(cl_ev); // sending request to game server
    // client's state will not change until we get response from GameServer
}
void AuthHandler::on_client_expected(ClientExpected *ev)
{
    if(m_link_store.find(ev->client_id)==m_link_store.end())
    {
        assert(!"client disconnected before receiving game cookie");
        return;
    }
    AuthLink *lnk = m_link_store[ev->client_id];
    lnk->m_state = AuthLink::CLIENT_AWAITING_DISCONNECT;
    lnk->putq(new ServerSelectResponse(this,0xCAFEF00D,ev->cookie));
}
