#pragma once

#include <iostream>

#include "spdlog/spdlog.h"

#include "Engine.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "ECS.h"
#include "ScriptingManager.h"
#include "NetworkManager.h"

using namespace lilengine;

int main(int argc, const char* argv[]){
    spdlog::info("Starting server...\n");

    if(enet_initialize () != 0){
            spdlog::error("An error occurred while initializing ENer.\n");
            return EXIT_FAILURE;
        }

        atexit(enet_deinitialize);

    NetworkManager& networking_manager = gEngine.GetNetworkManager();

    networking_manager.server_address.host = ENET_HOST_ANY;
       /* Bind the server to port 1234 */
       networking_manager.server_address.port = 1234;

       networking_manager.server = enet_host_create (&networking_manager.server_address /* the addr  to bind the server host to */,
                                    32 /* allow up to 32 clients and/or outgoing connections */,
                                    1 /* allow up to 2 channels to be used, 0 and 1 */,
                                    0  /* assume any amount of incoming bandwidth */,
                                    0 /* assume any amount of outgoing bandwidth */);

    
        if(networking_manager.server == NULL){

            spdlog::error("An error occured while trying to create an ENet server host.\n");
            exit(EXIT_FAILURE);
        }

        spdlog::info("Server Created Successfully!\n");
        spdlog::info("Server Running!\n");

        while(true){

			while(enet_host_service(networking_manager.server, &networking_manager.server_event, 1000) > 0){
				printf("Updating server...\n");
				switch(networking_manager.server_event.type){

					case ENET_EVENT_TYPE_CONNECT:
						printf("A new client connected from %x:%u\n",
								networking_manager.server_event.peer -> address.host,
								networking_manager.server_event.peer -> address.port);
						break;
					
					case ENET_EVENT_TYPE_RECEIVE:
						printf("A packet of length %u containing %s was received from %x:%u on channel %u\n",
						networking_manager.server_event.packet -> dataLength/* length of data */,
						networking_manager.server_event.packet -> data/* containing data of packet*/,
						networking_manager.server_event.peer -> address.host,
						networking_manager.server_event.peer -> address.port,
						networking_manager.server_event.channelID);
						break;

					case ENET_EVENT_TYPE_DISCONNECT:
						printf("%xx:%u disconnected.\n",
								networking_manager.server_event.peer -> address.host,
								networking_manager.server_event.peer -> address.port);
						break;
				}
			}
        }
}