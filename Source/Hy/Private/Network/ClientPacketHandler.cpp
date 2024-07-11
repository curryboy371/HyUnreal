#pragma once
#include "ClientPacketHandler.h"
#include "Hy.h"
#include "HySpawnManager.h"
#include "HySession.h"

//#include "NetworkManager.h"
//#include "SessionManager.h"
//#include "UserManager.h"
//#include "User.h"
//#include "Room.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

/* 클라이언트 side 패킷 수신 */

/* 컨텐츠 수동 작업 */
bool INVALID_PACKET(HySessionRef& session, BYTE* buffer, int32 len)
{
    FPacketHeader* header = reinterpret_cast<FPacketHeader*>(buffer);
    LOG_V("Header Id : %d", header->PacketID);
    return false;
}

bool SC_LOGIN(HySessionRef& session, Protocol::SC_LOGIN& pkt)
{
    if (pkt.success() == true)
    {

        //// 게임 입장 시도
        Protocol::CS_ENTER_GAME enterPkt;

        enterPkt.set_player_id(pkt.user_info().id());
        SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(enterPkt);
        session->SendPacket(sendBuffer);

        //UserRef user = std::make_shared<User>();
        //user->Set_user_info(pkt.user_info());
        //user->Set_ownerSession(session);
        //
        //
        //GCinstance->GetManager<UserManager>()->AddClientSession(user);
        //
        //GCinstance->GetManager<NetworkManager>()->CallnetworkCB(HyPacketID::PKE_SC_LOGIN, 0);
        //DLOG_V("SC_LOGIN:: login success user", user->Get_user_infoRef().name());
        //
        //session->SetSessionStatus(E_SESSION_STATUS::E_LOGIN_STATUS);
        //

        //enterPkt.set_room_name("test room");
        //enterPkt.set_userid(user->GetUserID());
        //SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(enterPkt);
        //
        //session->PreSend(sendBuffer);
        //
        //DLOG_V("SC_LOGIN:: try enter the room - ", enterPkt.room_name());

    }
    else
    {
        //GCinstance->GetManager<NetworkManager>()->CallnetworkCB(HyPacketID::PKE_SC_LOGIN, 1);
        //DLOG("SC_LOGIN false!!!");
    }

    return true;
}

bool SC_REGIST(HySessionRef& session, Protocol::SC_REGIST& pkt)
{
    if (pkt.success() == true)
    {
        //GCinstance->GetManager<NetworkManager>()->CallnetworkCB(HyPacketID::PKE_SC_REGIST, 0);
        //DLOG_V("SC_REGIST:: sucess user : ", pkt.user_name());
    }
    else
    {
        //GCinstance->GetManager<NetworkManager>()->CallnetworkCB(HyPacketID::PKE_SC_REGIST, 1);
        //DLOG("SC_REGIST false!!!");
    }
    return true;
}

bool SC_ENTER_ROOM(HySessionRef& session, Protocol::SC_ENTER_ROOM& pkt)
{
    if (session)
    {
        bool bsuccess = pkt.success();

        //if (bsuccess)
        //{
        //    // 본인 입장
        //    UserRef myUser = GCinstance->GetManager<UserManager>()->GetMyUser(session->GetSessionKey());
        //
        //    // 신규 유저 입장 (본인 ) 
        //    GCinstance->Get_room()->Enter(myUser);
        //
        //    for (int32 i = 0; i < pkt.users_size(); ++i)
        //    {
        //        int64 userid = pkt.users()[i].id();
        //        //HySessionRef otherSession = GCinstance->GetManager<Client::SessionManager>()->GetUserSession(userid); //다른 유저 세션은 보관 안함
        //        if(Ginstance->GetManager<UserManager>()->AddUser(pkt.users()[i], nullptr))
        //        {
        //            UserRef newUser=  Ginstance->GetManager<UserManager>()->GetUser(pkt.users()[i].id());
        //            std::string username = pkt.users()[i].name();
        //            // 기존 유저정보
        //            GCinstance->Get_room()->Enter(newUser);
        //        }
        //    }
        //
        //    std::string msg = myUser->Get_user_infoRef().name() + " : Enter the room (me)";
        //    AddTextToOutput(msg);
        //}
    }

    return true;
}

bool SC_ENTER_GAME(HySessionRef& session, Protocol::SC_ENTER_GAME& pkt)
{
    if (pkt.success())
    {
        Protocol::hyps_pos_info MyPlayer = pkt.my_player();
        FObjectSpawnInfo SpawnInfo;
        SpawnInfo.ObjectID = MyPlayer.object_id();
        SpawnInfo.ObjectType = Protocol::hype_object_type::creature;
        SpawnInfo.Location = FVector(MyPlayer.x(), MyPlayer.y(), MyPlayer.z());
        SpawnInfo.Rotation = FRotator(0.f, MyPlayer.yaw(), 0.f);

        if (GGameInstance->GetManager<UHySpawnManager>())
        {
            GGameInstance->GetManager<UHySpawnManager>()->SpawnMyPlayer(SpawnInfo);
        }
    }
    else
    {
        ERR_V("fail");
        return false;
    }

    return true;
}

bool SC_LEAVE_GAME(HySessionRef& session, Protocol::SC_LEAVE_GAME& pkt)
{
    SCREEN_LOG_V("SC_Leave_Game");
    return true;
}

bool BC_LEAVE_GAME(HySessionRef& session, Protocol::BC_LEAVE_GAME& pkt)
{

    return true;
}

bool SC_SPAWN(HySessionRef& session, Protocol::SC_SPAWN& pkt)
{
    for (int32 i = 0; i < pkt.players_size(); ++i)
    {
        Protocol::hyps_object_info object_info = pkt.players(i);

        if (object_info.object_type() == Protocol::hype_object_type::creature)
        {
            Protocol::hyps_pos_info pos_info = object_info.pos_info();

            FObjectSpawnInfo SpawnInfo;
            SpawnInfo.ObjectID = object_info.object_id();
            SpawnInfo.ObjectType = Protocol::hype_object_type::creature;
            SpawnInfo.Location = FVector(pos_info.x(), pos_info.y(), pos_info.z());
            SpawnInfo.Rotation = FRotator(0.f, pos_info.yaw(), 0.f);

            if (GGameInstance->GetManager<UHySpawnManager>())
            {
                GGameInstance->GetManager<UHySpawnManager>()->SpawnObject(SpawnInfo);
            }
        }
    }



    return true;
}

bool BC_SPAWN(HySessionRef& session, Protocol::BC_SPAWN& pkt)
{
    for (int32 i = 0; i < pkt.players_size(); ++i)
    {
        Protocol::hyps_object_info object_info = pkt.players(i);

        if (object_info.object_type() == Protocol::hype_object_type::creature)
        {
            Protocol::hyps_pos_info pos_info = object_info.pos_info();

            FObjectSpawnInfo SpawnInfo;
            SpawnInfo.ObjectID = object_info.object_id();
            SpawnInfo.ObjectType = Protocol::hype_object_type::creature;
            SpawnInfo.Location = FVector(pos_info.x(), pos_info.y(), pos_info.z());
            SpawnInfo.Rotation = FRotator(0.f, pos_info.yaw(), 0.f);

            if (GGameInstance->GetManager<UHySpawnManager>())
            {
                GGameInstance->GetManager<UHySpawnManager>()->SpawnObject(SpawnInfo);
            }
        }
    }
    return true;
}

bool SC_DESPAWN(HySessionRef& session, Protocol::SC_DESPAWN& pkt)
{
    if (session == nullptr)
    {
        return false;
    }



    return true;
}

bool BC_DESPAWN(HySessionRef& session, Protocol::BC_DESPAWN& pkt)
{
    if (session == nullptr)
    {
        return false;
    }

    UHySpawnManager* SpawnMgr = GGameInstance->GetManager<UHySpawnManager>();
    if (SpawnMgr == nullptr)
    {
        return false;
    }

    int32 object_size = pkt.object_ids_size();
    
    for (int32 i = 0; i < object_size; ++i)
    {
        int64 id = pkt.object_ids(i);
        SpawnMgr->DeSpawnObject(id);
    }

    return true;
}

bool SC_MOVE_OBJECT(HySessionRef& session, Protocol::SC_MOVE_OBJECT& pkt)
{
    if (session == nullptr)
    {
        return false;
    }

    UHySpawnManager* SpawnMgr = GGameInstance->GetManager<UHySpawnManager>();
    if (SpawnMgr == nullptr)
    {
        return false;
    }

    Protocol::hyps_pos_info pos_info = pkt.move_info();
    
    SpawnMgr->MoveObject(pos_info);

    return true;
}


bool BC_ENTER_ROOM_OTHERS(HySessionRef& session, Protocol::BC_ENTER_ROOM_OTHERS& pkt)
{
    if (session)
    {
        bool bsuccess = pkt.success();

        //if (bsuccess)
        //{
        //    for (int32 i = 0; i < pkt.users_size(); ++i)
        //    {
        //        int64 userid = pkt.users()[i].id();
        //        //HySessionRef otherSession = GCinstance->GetManager<Client::SessionManager>()->GetUserSession(userid);
        //        if (Ginstance->GetManager<UserManager>()->AddUser(pkt.users()[i], nullptr))
        //        {
        //            UserRef newUser = Ginstance->GetManager<UserManager>()->GetUser(pkt.users()[i].id());
        //
        //            // 신규 유저 입장 ( 다른유저 ) 
        //            GCinstance->Get_room()->Enter(newUser);
        //            std::string msg = newUser->Get_user_infoRef().name() + " : Enter the room";
        //            AddTextToOutput(msg);
        //        }
        //    }
        //}
    }
    return true;
}

bool SC_CHAT(HySessionRef& session, Protocol::SC_CHAT& pkt)
{
    FString MsgAsFString(ANSI_TO_TCHAR(pkt.msg().c_str()));
    LOG_V("msg : %s", *MsgAsFString);
    return true;
}

bool BC_GL_CHAT(HySessionRef& session, Protocol::BC_GL_CHAT& pkt)
{
    FString MsgAsFString(ANSI_TO_TCHAR(pkt.msg().c_str()));
    LOG_V("msg : %s", *MsgAsFString);
    return true;
}

bool BC_GL_ECHO(HySessionRef& session, Protocol::BC_GL_ECHO& pkt)
{
    FString MsgAsFString(ANSI_TO_TCHAR(pkt.msg().c_str()));
    LOG_V("msg : %s", *MsgAsFString);
    return true;
}
