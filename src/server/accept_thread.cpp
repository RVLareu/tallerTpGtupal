#include "./accept_thread.h"
#include "./client.h"
#include "./game.h"
#include "../common/common_protocol.h"
#include "../common/common_socket.h"
#include <vector>
#include <utility>

AcceptThread::AcceptThread(Socket& socket,
                        std::vector<Client*>& clients,
                        Protocol& protocol,
                        Game& game):
                        socket(socket),
                        clients(clients),
                        protocol(protocol),
                        game(game),
                        is_running(true),
                        thread(&AcceptThread::run,this){}

void AcceptThread::run(){          
    while (this->is_running){
        try{
            Socket client_socket = this->socket.accept();                             
            this->clients.push_back(new Client(std::move(client_socket),
                                                this->protocol,
                                                // Solo los primeros 2 clientes son jugadores
                                                (this->clients.size() > 2) ? false : true,
                                                this->game
                                                ));
            std::cout << "NEW CLIENT!" << std::endl;
        }
        catch(...){
            this->is_running = false;
        }        
    }
    this->remove_clients();
}

void AcceptThread::remove_clients(){
    for (auto &client : this->clients){
        delete client;
    }
}

void AcceptThread::join(){
    this->thread.join();
}
