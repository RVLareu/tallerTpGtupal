#ifndef __ACCEPT_THREAD_H__
#define __ACCEPT_THREAD_H__

#include <atomic>
#include <thread>
#include <iostream>
#include <vector>
#include "../common/common_protocol.h"
#include "../common/common_socket.h"
#include "./client.h"
#include "./game.h"

// Hilo "aceptador". Se encarga de aceptar nuevos clientes 
// y asignarles un Client.

class AcceptThread{
    private:
        // Socket del que se aceptarán clientes
        Socket& socket;
        // Vector de clientes
        std::vector<Client*>& clients;     
        Protocol& protocol;
        std::atomic<bool> is_running;
        std::thread thread;        
        BlockingQueue& blocking_queue;
        
    public:
        AcceptThread(Socket& socket, std::vector<Client*>& clients, Protocol& protocol, BlockingQueue& blocking_queue);
        //Libera los clientes
        void remove_clients();
        // Join al hilo "thread"
        void join();
        // Función principal que es ejecutada por el hilo "thread"
        void run();
        // remueve clientes desconectados
        void check_dead_clients();
};

#endif
