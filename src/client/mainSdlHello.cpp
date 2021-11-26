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

    // Initialize Menu
    Menu menu(std::ref(renderer), std::ref(window));
    // Menu loop
    menu.show_menu();

    // Initialize a board
    Board board(std::ref(renderer));

    board.create_spots();

    SDL2pp::Point mousePos;
    SDL_Event event;
    bool running = true;
    
    /*
        ejemplo para renderizar desde un vector de char

        PIEZA - PROBA - COL - FIL - ILUMINADO
    */
    // std::vector<char> pieces;
    
    // // reina blanca en [2,3], violeta
    // pieces.push_back('Q');
    // pieces.push_back(7);
    // pieces.push_back(2);
    // pieces.push_back(3);
    // pieces.push_back(1);
    // // Caballo blanco en [6,5], violeta
    // pieces.push_back('K');
    // pieces.push_back(7);
    // pieces.push_back(5);
    // pieces.push_back(6);
    // pieces.push_back(1);
    // // caballo negro en [1,1], original
    // pieces.push_back('k');
    // pieces.push_back(7);
    // pieces.push_back(1);
    // pieces.push_back(1);
    // pieces.push_back(0);
    // // peon blanco en [7,7], violeta
    // pieces.push_back('P');
    // pieces.push_back(7);
    // pieces.push_back(7);
    // pieces.push_back(7);
    // pieces.push_back(1);
    
    // // peon negro en [8,8], original
    // pieces.push_back('p');
    // pieces.push_back(8);
    // pieces.push_back(8);
    // pieces.push_back(8);
    // pieces.push_back(0);
    // //////////////////////////////

    std::vector<char> pieces = {'r',1,0,0,1,'n',1,1,0,1,'b',1,2,0,1,'k',1,3,0,1,'b',1,5,0,1,'n',1,6,0,1,'r',1,7,0,1,'p',1,0,1,1,'p',1,1,1,1,'p',1,2,1,1,'p',1,3,1,1,'p',1,4,1,1,'p',1,5,1,1,'p',1,6,1,1,'p',1,7,1,1,'q',1,4,4,1,'P',1,0,6,1,'P',1,1,6,1,'P',1,2,6,1,'P',1,3,6,1,'P',1,4,6,1,'P',1,5,6,1,'P',1,6,6,1,'P',1,7,6,1,'R',1,0,7,1,'N',1,1,7,1,'B',1,2,7,1,'K',1,3,7,1,'Q',1,4,7,1,'B',1,5,7,1,'N',1,6,7,1,'R',1,7,7,1};
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
                        std::cout << board.position_to_spot(mousePos); // mando al servidor, recibo la actualizacion
                    break;
                    }
            }
        }
        try {
            renderer.Clear();
            board.render_from_vector(pieces);
            renderer.Present();
            SDL_Delay(100);
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            return 1;
        }
    }
    return 0;
}
