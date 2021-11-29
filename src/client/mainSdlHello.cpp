#include <iostream>
#include <exception>
#include <SDL2pp/SDL2pp.hh>
#include <list>
#include <SDL.h>
#include <iostream>

#include "../server/game.h"

#include "spot.h"
#include "renderpiece.h"
#include "chessboard.h"
#include "menu.h"
#include "endScreen.h"





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
    menu.show_menu();

    // Initialize a board
    ChessBoard board(std::ref(renderer));

    board.create_spots();

    SDL2pp::Point mousePos;
    SDL_Event event;
    bool running = true;
    
    std::vector<char> pieces;


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
    

    Board chBoard;
    Game game(std::ref(chBoard));
    while (running) {
        
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
                        game.process_position(std::get<0>(board.mouse_position_to_square(mousePos)), std::get<1>(board.mouse_position_to_square(mousePos)));
                    break;
                    }
            }
        }
        try {
            renderer.Clear();
            pieces = game.get_board();
            //std::cout << pieces.data();
            board.render_from_vector(pieces);
            renderer.Present();
            SDL_Delay(1000);
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            return 1;
        }
    }

    dev.Pause(true);
        //End Screen
    EndScreen endScreen(std::ref(renderer), std::ref(window), 'b');
    endScreen.show_end_screen();
    return 0;
}
