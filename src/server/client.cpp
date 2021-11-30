#ifndef __SERVER_H__
#define __SERVER_H__

#include "../common/common_socket.h"
#include "./client.h"

#include <thread>


Client::Client(Socket socket, Protocol& protocol, bool is_player): 
                                socket(std::move(socket)),
                                protocol(protocol),
                                is_player(is_player),
                                recv_thread(&Client::recv_events,this)                                
                                {};

void Client::recv_events(){
    while (true){
        this->protocol.recv_client_events(this->socket);        
    }
    
};

#endif