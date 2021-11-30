#ifndef __SERVER_H__
#define __SERVER_H__

#include "../common/common_socket.h"
#include "./client.h"
#include "./game.h"

#include <thread>
#include <iostream>


Client::Client(Socket socket, Protocol& protocol, bool is_player, BlockingQueue& blocking_queue): 
                                socket(std::move(socket)),
                                protocol(protocol),
                                is_player(is_player),
                                recv_thread(&Client::recv_events,this),
                                blocking_queue(blocking_queue)
                                {};

void Client::recv_events(){

    while (true){
        if (is_player) {
            std::cout << "RECV EVENT" << std::endl;            
            this->protocol.recv_client_events(this->socket, this->blocking_queue);
        }
    }
    
};

void Client::send_board_status(Board& board){
    this->protocol.send_board_status(this->socket, board);
}

void Client::send_finished_game(bool white_wins){
    this->protocol.send_finished_game(this->socket, white_wins);
}
#endif