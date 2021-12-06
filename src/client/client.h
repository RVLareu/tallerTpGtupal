
#ifndef CLIENT_H
#define CLIENT_H
#include <SDL.h>
#include <thread>
#include <string>
#include <SDL2pp/SDL2pp.hh>
#include <queue>
#include <vector>
#include "../common/common_socket.h"
#include "../common/common_protocol.h"

#include "chessboard.h"

class Client {
    private:

        Protocol protocol;
        Socket socket;
        SDL2pp::SDL sdl;
        SDL2pp::Window window;
        SDL2pp::Renderer renderer;
        ChessBoard board;

        char winner;
        void in_game_loop();
        std::string nickname;

        bool running;

        std::queue<std::vector<char>> status_queue;
        std::queue<std::tuple<int, int>> selection_queue;

    public:
        int receive_board_state_and_render();
        int receive_client_input_and_send();
        Client();
        int run();
        void send_selection();
        void receive_status();
};

#endif
