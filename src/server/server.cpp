#include "./server.h"
#include "../common/common_socket.h"
#include "../common/common_protocol.h"
#include "./accept_thread.h"

#include <vector>

Server::Server(char* host, char* port): game(this->blocking_queue, this->clients){
    this->socket.listen(host, port, 50);
};

void Server::main_loop(){     
    AcceptThread accept_thread(this->socket,
                            this->clients,                        
                            this->protocol,
                            this->blocking_queue);
    this->game.process_events(this->blocking_queue);
    this->socket.force_stop();
    accept_thread.join();
}