#pragma once

#include <iostream>

#include "spdlog/spdlog.h"
#include <string>

#include "Engine.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "ECS.h"
#include "ScriptingManager.h"
#include "NetworkManager.h"
#include "Chatbox.h"


using namespace lilengine;
static ChatBox& chatbox = gEngine.GetChatBox();

void SendPacket(ENetPeer * peer, const char* data){

    ENetPacket * packet = enet_packet_create(data, strlen(data) + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);


};

int main(int argc, const char* argv[]){

    printf("Please enter your username\n");
    char username[80];
    scanf("%s", &username);

    spdlog::info("Creating client...\n");

    if(enet_initialize () != 0){
            spdlog::error("An error occurred while initializing ENet!.\n");
            return EXIT_FAILURE;
        }

        atexit(enet_deinitialize);

    NetworkManager& networking_manager = gEngine.GetNetworkManager();


       networking_manager.client = enet_host_create (NULL /* the addr  to bind the server host to */,
                                    1 /* allow up to 32 clients and/or outgoing connections */,
                                    1 /* allow up to 2 channels to be used, 0 and 1 */,
                                    0  /* assume any amount of incoming bandwidth */,
                                    0 /* assume any amount of outgoing bandwidth */);

    
        if(networking_manager.client == NULL){

            spdlog::error("An error occured while trying to create an ENet client host.\n");
            exit(EXIT_FAILURE);
        }

        spdlog::info("Client Created Successfully!\n");
       
         enet_address_set_host(&networking_manager.client_address, "127.0.0.1");
        networking_manager.client_address.port = 1234;

        networking_manager.peer = enet_host_connect(networking_manager.client,
                                &networking_manager.client_address,
                                1 /* channelss*/,
                                0 /* data we want to send*/);

       if( networking_manager.peer == NULL){
            spdlog::error("No available peers for initiating an ENet connection!\n");
            return EXIT_FAILURE;
        }         

        if(enet_host_service(networking_manager.client, &networking_manager.client_event, 5000) > 0 && 
           networking_manager.client_event.type == ENET_EVENT_TYPE_CONNECT){// if we receive events data thats about connection to server{

                printf("Connection to 127.0.0.1:%d succeeded!\n", networking_manager.client_address.port);

        }
        else{// if connection unsuccessful
            
            enet_peer_reset(networking_manager.peer);
            spdlog::info("Connection to server failed!\n");

            // return exit_success
            return EXIT_SUCCESS;

        }

        SendPacket(networking_manager.peer, "test_data");
    

    chatbox.Init();

    bool running = true;
    

    while(running){


        string message = chatbox.CheckBoxInput();

        char strarr[message.length() + 1];
        strcpy(strarr, message.c_str());
        chatbox.PostMessage(username, strarr);

        if(message == "/exit") running = false;

    }

    enet_peer_disconnect(networking_manager.peer, 0);

    while(enet_host_service(networking_manager.client, &networking_manager.client_event, 3000) > 0){

        switch(networking_manager.client_event.type){

            case ENET_EVENT_TYPE_RECEIVE:
                enet_packet_destroy(networking_manager.client_event.packet);
                break;
            
            case ENET_EVENT_TYPE_DISCONNECT:
                spdlog::info("Disconnection Succeded.");
                break;
        }
    }
   


    return EXIT_SUCCESS;
}