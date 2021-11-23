#include <SDL2pp/SDL2pp.hh>

#include "piece.h"


Piece::Piece(SDL2pp::Renderer& renderer, int x, int y, std::string path) : renderer(renderer), sprite(renderer, path), x_top(x), y_top(y), selected(false) {

}

void Piece::copy() {
    this->renderer.Copy(sprite, SDL2pp::NullOpt, SDL2pp::Rect(x_top, y_top, 80, 80));
}

bool Piece::clicked(SDL2pp::Point mousePos) {
    return (mousePos.GetX() >= x_top and mousePos.GetX() < x_top + 80 and mousePos.GetY() > y_top and mousePos.GetY() < y_top + 80);
}

void Piece::set_position(int x, int y) {
    this->x_top = x;
    this->y_top = y;
}