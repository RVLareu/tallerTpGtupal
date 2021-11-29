#include <SDL2pp/SDL2pp.hh>
#include <math.h>
#include "renderpiece.h"


RenderPiece::RenderPiece(SDL2pp::Renderer& renderer, int y, int x, std::string path, int probability_fraction) : renderer(renderer), sprite(renderer, path), x_top(x), y_top(y), selected(false), probability_fraction(probability_fraction) {

}

void RenderPiece::copy() {
    this->renderer.Copy(sprite, SDL2pp::NullOpt, SDL2pp::Rect(x_top, y_top, 80, 80));
    if (this->probability_fraction != 0) {
        SDL2pp::SDLTTF ttf;
        SDL2pp::Font font("assets/SIXTY.TTF", 50);  
        SDL2pp::Texture num_text(renderer, font.RenderText_Solid("1", SDL_Color{255, 0, 0, 0}));
        SDL2pp::Texture dash(renderer, font.RenderText_Solid("-", SDL_Color{255, 0, 0, 0}));
        SDL2pp::Texture denom_text(renderer, font.RenderText_Solid(std::to_string(this->probability_fraction), SDL_Color{255, 0, 0, 0}));
        this->renderer.Copy(num_text, SDL2pp::NullOpt, SDL2pp::Rect(x_top + 5, y_top, 3, 20));
        this->renderer.Copy(dash, SDL2pp::NullOpt, SDL2pp::Rect(x_top , y_top + 10, 15, 20));
        this->renderer.Copy(denom_text, SDL2pp::NullOpt, SDL2pp::Rect(x_top + 5, y_top + 18, 3, 20));
    }
}

bool RenderPiece::clicked(SDL2pp::Point mousePos) {
    return (mousePos.GetX() >= x_top and mousePos.GetX() < x_top + 80 and mousePos.GetY() > y_top and mousePos.GetY() < y_top + 80);
}

void RenderPiece::set_position(int x, int y) {
    this->x_top = x;
    this->y_top = y;
}