#ifndef __SERVER_H__
#define __SERVER_H__

#include "../common/common_socket.h"
#include "./client.h"
#include "./game.h"

#include <thread>
#include <iostream>


Client::Client(Socket socket, Protocol& protocol, 
               bool is_player, BlockingQueue& blocking_queue, 
               int client_id): 
                    socket(std::move(socket)),
                    protocol(protocol),
                    is_player(is_player),
                    recv_thread(&Client::recv_events,this),
                    blocking_queue(blocking_queue),
                    alive(true),
                    client_id(client_id)
                    {};

Client::~Client(){
    this->alive = false;
    recv_thread.join();
}

bool Client::is_dead() {
    return alive;
}

void Client::recv_events(){
    while (this->alive){
        if (is_player) {
            try {
                this->protocol.recv_client_events(this->socket, 
                                                  this->blocking_queue, 
                                                  this->client_id);
            } catch(std::runtime_error) {
                this->alive = false;
            }
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