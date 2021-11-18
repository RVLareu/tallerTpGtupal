#include <SDL2/SDL.h>
#include <iostream>
#include <exception>
#include "SdlWindow.h"
#include "SdlTexture.h"

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH  800

int main(int argc, char** argv){
    try {
        SdlWindow window(WINDOW_WIDTH, WINDOW_HEIGHT);
        window.fill();
        // Usar factory
        SdlTexture im("assets/cat.gif", window);
        // Dibujo la imagen en el centro de la pantalla
        //Area srcArea(0, 0, 800, 446);
        Area srcArea(0, 0, 300, 300);
        Area destArea((WINDOW_WIDTH / 2) - 400, (WINDOW_HEIGHT / 2) - 300, 800, 600);
        // El destination del stencil es mas grande que el tamaño de la pantalla para evitar fugas de luz
        Area stencilSrc(0, 0, 500, 500);
        Area stencilDest((WINDOW_WIDTH / 2) - 500, (WINDOW_HEIGHT / 2) - 500, 1000, 1000);
        // Cargo la imagen como textura, avisandolé a SDL que todo lo que sea de color blanco (0xffffff)
        // debe ser transparente en el dibujado (color keying).
        // El blending se usa para superponer dos texturas (como esto emula la sombra, quiero que sea semi-transparente)
        // El valor final es el alfa, que tan opaco quiero que se vea la imagen, a valor mas alto, menos transparente es.
        SdlTexture stencil("assets/stencil.png", window, Color{0xFF, 0xFF, 0xFF}, SDL_BLENDMODE_BLEND, 180);
        bool running = true;
        float angle = 0.0f;
        while (running) {
            SDL_Event event;
            window.fill(); // Repinto el fondo gris
            // Para el alumno: Buscar diferencia entre waitEvent y pollEvent
            SDL_WaitEvent(&event);
            switch(event.type) {
                case SDL_KEYDOWN: {
                        SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                        switch (keyEvent.keysym.sym) {
                            case SDLK_LEFT:
                                // cambio el angulo de rotacion del foco de luzsi,
                                angle -= 10.0f;
                                break;
                            case SDLK_RIGHT:
                                angle += 10.0f;
                                break;
                            }
                    } // Fin KEY_DOWN
                    break;
                case SDL_QUIT:
                    std::cout << "Quit :(" << std::endl;
                    running = false;
                    break;
            }
            im.render(srcArea, destArea);
            stencil.render(stencilSrc, stencilDest, angle);
            window.render();
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

