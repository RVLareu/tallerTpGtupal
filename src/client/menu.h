
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
        std::vector<SDL2pp::Texture> code_text_box;
        std::vector<SDL2pp::Texture> nickname_text_box;
        std::string code;
        std::string nickname;

    public:
        Menu(SDL2pp::Renderer& renderer, SDL2pp::Window& window);
        
        std::string show_menu();
        
        void code_text_box_bg();

        void nickname_text_box_bg();
};



#endif