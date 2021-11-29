
#include <SDL2pp/SDL2pp.hh>

#ifndef RENDERPIECE_H
#define RENDERPIECE_H

class RenderPiece {
    private:
        SDL2pp::Renderer& renderer;
        SDL2pp::Texture sprite;

    public:
        int x_top;
        int y_top;
        int probability_fraction;
        bool selected;
        RenderPiece(SDL2pp::Renderer& renderer, int y, int x, std::string path, int probability_fraction);
        void copy();
        bool clicked(SDL2pp::Point mousePos);
        void set_position(int x, int y);
};

#endif
