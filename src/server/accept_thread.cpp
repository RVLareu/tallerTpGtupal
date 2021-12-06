#include "./accept_thread.h"
#include "./blocking_queue.h"
#include "./client.h"
#include "./game.h"
#include "../common/common_protocol.h"
#include "../common/common_socket.h"
#include <vector>
#include <utility>

AcceptThread::AcceptThread(Socket& socket,
                        std::vector<Client*>& clients,
                        Protocol& protocol,
                        BlockingQueue& blocking_queue):
                        socket(socket),
                        clients(clients),
                        protocol(protocol),                        
                        is_running(true),
                        thread(&AcceptThread::run,this),
                        blocking_queue(blocking_queue){}

void AcceptThread::run(){
    int clients_accepted = 0;          
    while (this->is_running){
        try{
            Socket client_socket = this->socket.accept();
            std::cout << "NEW CLIENT!" << std::endl;
            this->clients.push_back(new Client(std::move(client_socket),
                                                this->protocol,
                                                // Solo los primeros 2 clientes son jugadores
                                                (clients_accepted >= 2) ? false : true,
                                                this->blocking_queue
                                                ));
            // Encolamos el evento de conexion de cliente
            std::vector<char> event = {'n'}; //'n de (n)ew client
            this->blocking_queue.push(event);
            clients_accepted += 1;
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
