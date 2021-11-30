
#ifndef CLIENT_H
#define CLIENT_H
#include <SDL.h>
#include <thread>
#include <string>
#include <SDL2pp/SDL2pp.hh>
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
        
    public:
        void receive_board_state_and_render(bool& running);
        void receive_client_input_and_send(SDL_Event event, SDL2pp::Point mousePos, bool& running);
        Client();
        int run();
};

#endif
