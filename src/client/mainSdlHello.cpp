#include <iostream>
#include <exception>
#include <SDL2pp/SDL2pp.hh>
#include <list>
#include <SDL.h>
#include <iostream>
#include <thread>



#include "spot.h"
#include "renderpiece.h"
#include "chessboard.h"
#include "menu.h"
#include "endScreen.h"
#include "../common/common_socket.h"
#include "../common/common_protocol.h"


void receive_board_state_and_render(SDL2pp::Renderer& renderer, ChessBoard& board, bool& running, Socket& client_socket, Protocol& protocol) {
                
        while (running) {
            renderer.Clear();
            std::vector<char> pieces = protocol.recv_board_status(client_socket);
            std::cout << pieces.size() << std::endl;
            if (pieces.size() > 0){
                board.render_from_vector(pieces);
                renderer.Present();
            }
            // try {
            // } catch (std::exception& e) {
            //     std::cout << e.what() << std::endl;                
            // }
        }
}


void receive_client_input_and_send(SDL_Event event, SDL2pp::Point mousePos, bool& running, Socket& socket, ChessBoard& board, Protocol& protocol) {
    while(running) {
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;                    
                    break;
                case SDL_MOUSEMOTION:
                    mousePos.SetX(event.motion.x);
                    mousePos.SetY(event.motion.y);
                    break;
                case SDL_MOUSEBUTTONDOWN: 
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        protocol.send_selection(socket, std::get<0>(board.mouse_position_to_square(mousePos)), std::get<1>(board.mouse_position_to_square(mousePos)));
                        //game.process_position(std::get<0>(board.mouse_position_to_square(mousePos)), std::get<1>(board.mouse_position_to_square(mousePos)));
                    break;
                    }
            }
        }
    }
}


int main(int argc, char** argv){
    // Inicializo biblioteca de SDL
    SDL2pp::SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    // Creo una ventana dinamica con titulo "Chess set"
    SDL2pp::Window window("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        800, 800,
        SDL_WINDOW_RESIZABLE);

    // Creo renderer
    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);


    // Initialize Menu
    Menu menu(std::ref(renderer), std::ref(window));
    // Menu loop;
    std::string nickname = menu.show_menu();

    // Initialize a board
    ChessBoard board(std::ref(renderer));

    board.create_spots();

    SDL2pp::Point mousePos;
    SDL_Event event;
    bool running = true;
    
    std::vector<char> pieces;

    Socket client_socket;
    client_socket.connect("localhost", "7777");
    Protocol protocol;

    SDL2pp::Wav wav("assets/in_game_music.wav");
        uint8_t* wav_pos = wav.GetBuffer();
        SDL2pp::AudioDevice dev(SDL2pp::NullOpt, 0, wav.GetSpec(), [&wav, &wav_pos](Uint8* stream, int len) {
                    // Fill provided buffer with wave contents
                    Uint8* stream_pos = stream;
                    Uint8* stream_end = stream + len;

                    while (stream_pos < stream_end) {
                        Uint8* wav_end = wav.GetBuffer() + wav.GetLength();

                        size_t copylen = std::min(wav_end - wav_pos, stream_end - stream_pos);

                        std::copy(wav_pos, wav_pos + copylen, stream_pos);
                        stream_pos += copylen;
                        wav_pos += copylen;
                        if (wav_pos >= wav_end)
                            wav_pos = wav.GetBuffer();
                    }
                }
            );
        
    dev.Pause(false);
    

    

    std::thread client_input (receive_client_input_and_send, event, mousePos, std::ref(running), std::ref(client_socket), std::ref(board), std::ref(protocol));



    std::thread render_board (receive_board_state_and_render, std::ref(renderer), std::ref(board), std::ref(running), std::ref(client_socket), std::ref(protocol));

    client_input.join();
    // render_board.join();


    dev.Pause(true);
        //End Screen
    EndScreen endScreen(std::ref(renderer), std::ref(window), 'b', nickname);
    endScreen.show_end_screen();
    return 0;
}
