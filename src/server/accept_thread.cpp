#include "./accept_thread.h"
#include "./blocking_queue.h"
#include "./client.h"
#include "./game.h"
#include "../common/common_protocol.h"
#include "../common/common_socket.h"
#include <vector>
#include <utility>

AcceptThread::AcceptThread(Socket& socket,
                        std::list<Client*>& clients,
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
        check_dead_clients();        
    }
    this->remove_clients();
}

void AcceptThread::check_dead_clients() {
    std::list<Client*>::iterator it;
    for (it = this->clients.begin(); it != this->clients.end(); ++it) {
        if (!(*it)->is_dead()) {
            it = clients.erase(it);
            delete *it;
        }
    }
}

void AcceptThread::remove_clients(){
    std::list<Client*>::iterator it;
    for (it = this->clients.begin(); it != this->clients.end(); ++it) {
            it = this->clients.erase(it);
            delete *it;
    }
}

void AcceptThread::join(){
    this->thread.join();
}
