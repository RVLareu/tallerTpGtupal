#ifndef __SERVER_H__
#define __SERVER_H__

#include "./client.h"
#include "./game.h"
#include "./blocking_queue.h"
#include "../common/common_socket.h"
#include "../common/common_protocol.h"

#include <vector>
#include <tuple>
#include <map>


class Server {
    private:
        Socket socket;
        Protocol protocol;        
        std::vector<Client*> clients;
        Game game;
        BlockingQueue blocking_queue;

    public:
        Server();
        void main_loop();
};

#endif