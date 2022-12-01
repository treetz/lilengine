#pragma once

#include "spdlog/spdlog.h"

#include "NetworkManager.h"

namespace lilengine {



    NetworkManager::NetworkManager() {}

	NetworkManager::~NetworkManager() {}

	int NetworkManager::Startup() {

        spdlog::info("Starting up network...\n");

        if(enet_initialize () != 0){
            spdlog::error("An error occurred while initializing ENer.\n");
            return EXIT_FAILURE;
        }

        atexit(enet_deinitialize);
        CreateENetServer();//server_address,server);
        return 0;
    }

    void NetworkManager::CreateENetServer(){//ENetAddress address, ENetHost * server) {

        spdlog::info("Creating your server!\n");

        /*
            Bind the server to the default localhost.
            A specific host addr can be specified by
            enet_address_set_host (& address, "x.x.x.x");
        */
       server_address.host = ENET_HOST_ANY;
       /* Bind the server to port 1234 */
       server_address.port = 1234;

       server = enet_host_create (&server_address /* the addr  to bind the server host to */,
                                    32 /* allow up to 32 clients and/or outgoing connections */,
                                    1 /* allow up to 2 channels to be used, 0 and 1 */,
                                    0  /* assume any amount of incoming bandwidth */,
                                    0 /* assume any amount of outgoing bandwidth */);

    
        if(server == NULL){

            spdlog::error("An error occured while trying to create an ENet server host.\n");
            exit(EXIT_FAILURE);
        }

        
    }

    ENetHost * NetworkManager::CreateClient(){//ENetHost * client,ENetEvent client_event, ENetPeer * peer, ENetAddress address){

        spdlog::info("Creating your client!\n");
        
        client = enet_host_create(NULL/* create a client host */,
            1/* only allow 1 outgoing connection */,
            1/* allow up to 2 channels to be used, 0 and 1 */,
            0/* assume any amount of incoming bandwidth */,
            0/* assume any amount of outgoing bandwidth */);

        if(client == NULL){
            spdlog::error("An error occured while trying to create an ENet client host.\n");
            exit(EXIT_FAILURE);
        }

        enet_address_set_host(&client_address, "127.0.0.1");
        client_address.port = 1234;

        peer = enet_host_connect(client,
                                &client_address,
                                1 /* channelss*/,
                                0 /* data we want to send*/);

       if( peer == NULL){
            spdlog::error("No available peers for initiating an ENet connection!\n");
            exit(EXIT_FAILURE);
        }         

        if(enet_host_service(client, &client_event, 5000) > 0 && 
           client_event.type == ENET_EVENT_TYPE_CONNECT){// if we receive events data thats about connection to server{

                printf("Connection to 127.0.0.1:%d succeeded!\n", client_address.port);
                return client;

        }
        else{// if connection unsuccessful
            
            enet_peer_reset(peer);
            spdlog::info("Connection to server failed!\n");

            // return exit_success
            exit_success();

        }



    }

    int NetworkManager::exit_success(){
        return EXIT_SUCCESS;
    }

    void NetworkManager::UpdateServer(){


        while(enet_host_service(server, &server_event, 1000) > 0){
            printf("Updating server...\n");
            switch(server_event.type){

                case ENET_EVENT_TYPE_CONNECT:
                    printf("A new client connected from %x:%u\n",
                            server_event.peer -> address.host,
                            server_event.peer -> address.port);
                    break;
                
                case ENET_EVENT_TYPE_RECEIVE:
                    printf("A packet of length %u containing %s was received from %x:%u on channel %u\n",
                    server_event.packet -> dataLength/* length of data */,
                    server_event.packet -> data/* containing data of packet*/,
                    server_event.peer -> address.host,
                    server_event.peer -> address.port,
                    server_event.channelID);
                    break;

                case ENET_EVENT_TYPE_DISCONNECT:
                    printf("%xx:%u disconnected.\n",
                            server_event.peer -> address.host,
                            server_event.peer -> address.port);
                    break;
            }
        }
    }
    // void NetworkManager::ClientUpdate(ENetHost * client, ENetEvent client_event){

    //     while
    // }

    // may not need this anymore since we can use deinitialize
    void NetworkManager::Shutdown(ENetHost * server){
        enet_host_destroy(server);
        spdlog::info("Shutdown Server.\n");
    }

    int NetworkManager::DisconnectClient(ENetHost * client, ENetPeer * peer, ENetEvent event){

        enet_peer_disconnect(peer, 0);

        while(enet_host_service(client, &event, 3000) > 0){

            switch(event.type){
                case ENET_EVENT_TYPE_RECEIVE:
                    // destroy packet
                    enet_packet_destroy(event.packet);
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    spdlog::info("Disconnection Succeeded.\n");
                    break;
            }
        }

        return EXIT_SUCCESS;
    }


}