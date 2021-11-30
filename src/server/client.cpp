#ifndef __SERVER_H__
#define __SERVER_H__

#include "../common/common_socket.h"
#include "./client.h"
#include "./game.h"

#include <thread>


Client::Client(Socket socket, Protocol& protocol, bool is_player, Game& game): 
                                socket(std::move(socket)),
                                protocol(protocol),
                                is_player(is_player),
                                recv_thread(&Client::recv_events,this),
                                game(game)
                                {};

void Client::recv_events(){

    while (true){
        if (is_player) {
            this->protocol.recv_client_events(this->socket, this->game);
        }
    }
};

#endif