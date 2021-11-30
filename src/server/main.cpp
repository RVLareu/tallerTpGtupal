#include "game.h"
#include "server.h"

#include <iostream>
#include <functional>

#include <thread>

#include "../common/common_protocol.h"
#include "../common/common_socket.h"


int main(int argc, char* argv[]) {
    Server server;
    server.main_loop();
    return 0;
}
