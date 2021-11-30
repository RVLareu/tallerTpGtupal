#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "../common/common_socket.h"
#include "../common/common_protocol.h"

#include <vector>
#include <tuple>
#include <map>
#include <thread>

class Client {
    private:
        Socket socket;
        Protocol& protocol;
        // Hilo para recibir eventos del cliente
        std::thread recv_thread;
        // Hilo para enviar estado del juego al cliente
        std::thread send_thread;
        bool is_player;
    
    public:
        Client(Socket socket, Protocol& protocol, bool is_player);
        void recv_events();
        void send_board_status();
};

#endif