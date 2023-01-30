#include <iostream>
#include <string>
#include <unordered_map>

#include "Common.h"

class GameServer : public olc::net::server_interface<GameMsg>
{
public:
    GameServer(const uint16_t port) : server_interface<GameMsg>(port)
    { }

    std::unordered_map<uint32_t, playerDescription> mapPlayerRoster;
    std::vector<uint32_t> garbageIDs;

protected:
    bool OnClientConnect(std::shared_ptr<olc::net::connection<GameMsg>> client) override
    {
        // For now we will allow all 
        return true;
    }

    void OnClientValidated(const std::shared_ptr<olc::net::connection<GameMsg>> client) override
    {
        // Client passed validation check, so send them a message informing
        // them they can continue to communicate
        olc::net::message<GameMsg> msg;
        msg.header.id = GameMsg::Client_Accepted;
        client->Send(msg);
    }

    void RemovePlayerFromRoster(const int id)
    {
        mapPlayerRoster.erase(id);
        garbageIDs.push_back(id);
    }

    void OnClientDisconnect(const std::shared_ptr<olc::net::connection<GameMsg>> client) override
    {
        if (client)
        {
            if (mapPlayerRoster.find(client->GetID()) == mapPlayerRoster.end())
            {
                // client never added to roster, so just let it disappear
            }
            else
            {
                const auto& pd = mapPlayerRoster[client->GetID()];
                std::cout << "[UNGRACEFUL REMOVAL]:" + std::to_string(pd.uniqueID) + "\n";
                RemovePlayerFromRoster(client->GetID());
            }
        }
    }

    void OnMessage(const std::shared_ptr<olc::net::connection<GameMsg>> client,
                   olc::net::message<GameMsg>& msg) override
    {
        if (!garbageIDs.empty())
        {
            for (auto pid : garbageIDs)
            {
                olc::net::message<GameMsg> m;
                m.header.id = GameMsg::Game_RemovePlayer;
                m << pid;
                std::cout << "Removing " << pid << "\n";
                MessageAllClients(m);
            }
            garbageIDs.clear();
        }

        switch (msg.header.id)
        {
        case GameMsg::Client_RegisterWithServer:
        {
            playerDescription desc;
            msg >> desc;
            desc.uniqueID = client->GetID();
            mapPlayerRoster.insert_or_assign(desc.uniqueID, desc);

            olc::net::message<GameMsg> msgSendID;
            msgSendID.header.id = GameMsg::Client_AssignID;
            msgSendID << desc.uniqueID;
            MessageClient(client, msgSendID);

            olc::net::message<GameMsg> msgAddPlayer;
            msgAddPlayer.header.id = GameMsg::Game_AddPlayer;
            msgAddPlayer << desc;
            MessageAllClients(msgAddPlayer);

            for (const auto& player : mapPlayerRoster)
            {
                olc::net::message<GameMsg> msgAddOtherPlayers;
                msgAddOtherPlayers.header.id = GameMsg::Game_AddPlayer;
                msgAddOtherPlayers << player.second;
                MessageClient(client, msgAddOtherPlayers);
            }

            break;
        }

        case GameMsg::Client_UnregisterWithServer:
        {
            int id;
            msg >> id;
            RemovePlayerFromRoster(id);
            break;
        }

        case GameMsg::Game_UpdatePlayer:
        {
            MessageAllClients(msg, client);
            break;
        }
        }
    }
};


int main()
{
    GameServer server(60000);
    server.Start();

    while (true)
    {
        server.Update(-1, true);
    }
    return 0;
}
