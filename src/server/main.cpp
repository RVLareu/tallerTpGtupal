#include "game.h"
#include "server.h"

#include <iostream>
#include <functional>

#include <thread>

#include "../common/common_protocol.h"
#include "../common/common_socket.h"


int main(int argc, char* argv[]) {

    if (argc != 3) {
        std::cout << "Invalid arguments, must be host port";
        return 0;
    }
    
    char* host = argv[1];
    char* port = argv[2];

    Server server(host, port);
    server.main_loop();
    return 0;
}
