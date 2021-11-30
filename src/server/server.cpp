#include "./server.h"
#include "../common/common_socket.h"
#include "../common/common_protocol.h"
#include "./accept_thread.h"

#include <vector>

Server::Server(): game(this->blocking_queue, this->clients){
    this->socket.listen("localhost","7777",50);
};

void Server::main_loop(){     
    AcceptThread accept_thread(this->socket,
                            this->clients,                        
                            this->protocol,
                            this->blocking_queue);
    this->game.process_events(this->blocking_queue);
    std::string input = "";
    while (input != "q"){
        std::getline(std::cin,input);
    }
    this->socket.force_stop();
    accept_thread.join();
}