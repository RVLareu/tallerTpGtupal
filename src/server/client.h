#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "../common/common_socket.h"
#include "../common/common_protocol.h"
#include "./game.h"

#include <vector>
#include <tuple>
#include <map>
#include <thread>
#include <condition_variable>
#include <mutex>
class Client {
    private:
        Socket socket;
        Protocol& protocol;
        // Hilo para recibir eventos del cliente
        std::thread recv_thread;        
        // Hilo para enviar board al cliente
        std::thread send_thread;        
        bool is_player;
        Game& game;
        std::condition_variable condition_variable;
        std::mutex mutex;
    
    public:
        Client(Socket socket, Protocol& protocol, bool is_player, Game& game);
        void recv_events();
        void send_board_status();
};

#endif