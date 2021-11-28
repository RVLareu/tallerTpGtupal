#include <SDL2pp/SDL2pp.hh>
#include <math.h>
#include "renderpiece.h"


RenderPiece::RenderPiece(SDL2pp::Renderer& renderer, int y, int x, std::string path, float prob) : renderer(renderer), sprite(renderer, path), x_top(x), y_top(y), selected(false), prob(prob) {

}

void RenderPiece::copy() {
    this->renderer.Copy(sprite, SDL2pp::NullOpt, SDL2pp::Rect(x_top, y_top, 80, 80));
    if (prob != 0) {
        SDL2pp::SDLTTF ttf;
        SDL2pp::Font font("assets/SIXTY.TTF", 50);  
        SDL2pp::Texture prob_text(renderer, font.RenderText_Solid(std::to_string(this->prob), SDL_Color{255, 0, 0, 0}));
        this->renderer.Copy(prob_text, SDL2pp::NullOpt, SDL2pp::Rect(x_top + 10, y_top, 80, 15));
    }
}

bool RenderPiece::clicked(SDL2pp::Point mousePos) {
    return (mousePos.GetX() >= x_top and mousePos.GetX() < x_top + 80 and mousePos.GetY() > y_top and mousePos.GetY() < y_top + 80);
}

void RenderPiece::set_position(int x, int y) {
    this->x_top = x;
    this->y_top = y;
}