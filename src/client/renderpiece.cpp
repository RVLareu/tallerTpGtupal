#include <SDL2pp/SDL2pp.hh>
#include <math.h>
#include "renderpiece.h"

extern std::string ASSETS_PATH;
extern int RES_HEIGHT;
extern int RES_WIDTH;

RenderPiece::RenderPiece(SDL2pp::Renderer& renderer, int y, int x, std::string path, int probability_fraction_den, int probability_fraction_num) : renderer(renderer), sprite(renderer, path), x_top(x), y_top(y), selected(false), probability_fraction_den(probability_fraction_den), probability_fraction_num(probability_fraction_num) {

}

void RenderPiece::copy() {
    int width = RES_WIDTH / 8;
    int height = RES_HEIGHT / 8;
    this->renderer.Copy(sprite, SDL2pp::NullOpt, SDL2pp::Rect(x_top, y_top, width, height));
    if (this->probability_fraction_den != 0) {
        SDL2pp::SDLTTF ttf;
        SDL2pp::Font font(ASSETS_PATH + "assets/SIXTY.TTF", 50);  
        SDL2pp::Texture num_text(renderer, font.RenderText_Solid(std::to_string(this->probability_fraction_num), SDL_Color{255, 0, 0, 0}));
        SDL2pp::Texture dash(renderer, font.RenderText_Solid("-", SDL_Color{255, 0, 0, 0}));
        SDL2pp::Texture denom_text(renderer, font.RenderText_Solid(std::to_string(this->probability_fraction_den), SDL_Color{255, 0, 0, 0}));
        this->renderer.Copy(num_text, SDL2pp::NullOpt, SDL2pp::Rect(x_top + 5, y_top, 3, 20));
        this->renderer.Copy(dash, SDL2pp::NullOpt, SDL2pp::Rect(x_top , y_top + 10, 15, 20));
        this->renderer.Copy(denom_text, SDL2pp::NullOpt, SDL2pp::Rect(x_top + 5, y_top + 18, 3, 20));
    }
}

bool RenderPiece::clicked(SDL2pp::Point mousePos) {
    int width = RES_WIDTH / 8;
    int height = RES_HEIGHT / 8;
    return (mousePos.GetX() >= x_top and mousePos.GetX() < x_top + width and mousePos.GetY() > y_top and mousePos.GetY() < y_top + height);
}

void RenderPiece::set_position(int x, int y) {
    this->x_top = x;
    this->y_top = y;
}