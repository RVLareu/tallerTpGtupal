
#include <SDL2pp/SDL2pp.hh>
#include <vector>

#ifndef MENU_H
#define MENU_H


class Menu {
    private:
        SDL2pp::Renderer& renderer;
        std::vector<SDL2pp::Texture> textures;
        SDL2pp::Window& window;
        void render();
        void play_background_music();
        std::vector<SDL2pp::Texture> text_box;
        std::string code;
    public:
        Menu(SDL2pp::Renderer& renderer, SDL2pp::Window& window);
        int show_menu();
        void render_text_box();
};



#endif