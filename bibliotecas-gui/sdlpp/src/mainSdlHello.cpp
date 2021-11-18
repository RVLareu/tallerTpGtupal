#include <iostream>
#include <exception>
#include <SDL2pp/SDL2pp.hh>
#include <list>
#include <SDL.h>
#include <iostream>


#include "spot.h"
#include "piece.h"
#include "board.h"
#include "menu.h"






int main(int argc, char** argv){
    // Inicializo biblioteca de SDL
    SDL2pp::SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    // Creo una ventana dinamica con titulo "Chess set"
    SDL2pp::Window window("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        800, 800,
        SDL_WINDOW_RESIZABLE);

    // Creo renderer
    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);


    Menu menu(std::ref(renderer), std::ref(window));
    menu.show_menu();

    // Initialize a board
    Board board(std::ref(renderer));
    board.create_spots();
    board.create_pieces();

    SDL2pp::Point mousePos;
    
        


    
    SDL_Event event;
    bool running = true;


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
                        if (!board.move_piece_if_selected(mousePos.GetX(), mousePos.GetY())) { 
                            board.select_piece(mousePos);        
                        }
                    }
                    break;
            }
        }
        try {
            renderer.Clear();
            board.render();

            renderer.Present();
            SDL_Delay(100);

        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            return 1;
        }
    }

    return 0;
}
