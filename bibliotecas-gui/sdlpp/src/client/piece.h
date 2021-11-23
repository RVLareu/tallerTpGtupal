
#include <SDL2pp/SDL2pp.hh>

#ifndef PIECE_H
#define PIECE_H

class Piece {
    private:
        SDL2pp::Renderer& renderer;
        SDL2pp::Texture sprite;

    public:
        int x_top;
        int y_top;
        bool selected;
        Piece(SDL2pp::Renderer& renderer, int x, int y, std::string path);
        void copy();
        bool clicked(SDL2pp::Point mousePos);
        void set_position(int x, int y);

};

#endif
