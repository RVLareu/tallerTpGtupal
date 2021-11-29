#include <SDL2pp/SDL2pp.hh>
#include <vector>

#ifndef ENDSCREEN_H
#define ENDSCREEN_H


class EndScreen {
    private:
        SDL2pp::Renderer& renderer;
        std::vector<SDL2pp::Texture> textures;
        SDL2pp::Window& window;
        void render();
        void play_background_music();
    public:
        EndScreen(SDL2pp::Renderer& renderer, SDL2pp::Window& window, char winner);
        int show_end_screen();
};



#endif
