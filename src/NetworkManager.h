#pragma once

#include <enet/enet.h>


namespace lilengine {

    
    

    class NetworkManager{

        public:
            ENetHost * server;
            ENetAddress server_address;
            ENetEvent server_event;
            
            ENetHost * client;
            ENetAddress client_address;
            ENetEvent client_event;// events we receive from the server
            ENetPeer * peer; // server client will connect too

            std::unordered_map< long , ENetHost * > id_to_client_map;
            
            // setup manager
            NetworkManager();
            ~NetworkManager();

            // start up networking environment
            int Startup();
            // destroy server
            void Shutdown(ENetHost * server);
            // create server
            void CreateENetServer();//ENetAddress server_address, ENetHost * server);
            // create client
            ENetHost * CreateClient();//ENetHost *client,ENetEvent client_event, ENetPeer * peer, ENetAddress address);
            // update client 
            void ClientUpdate(ENetHost * client, ENetEvent client_event);
            void UpdateServer();
            // disconnect client
            int DisconnectClient(ENetHost * client, ENetPeer * peer, ENetEvent client_event);
            int exit_success();
    };
}