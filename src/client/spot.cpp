#include "spot.h"

Spot::Spot(SDL2pp::Renderer& renderer, SDL2pp::Rect rect, SDL2pp::Color color) : renderer(renderer) , rect(rect), color(color), selected(false), originalColor(color){

}
void Spot::render() {
    this->renderer.SetDrawColor(this->color);
    this->renderer.FillRect(rect);
}
bool Spot::clicked(SDL2pp::Point mousePos) {
    return (mousePos.GetX() >= rect.GetX() and mousePos.GetX() < rect.GetX2() and mousePos.GetY() >= rect.GetY() and mousePos.GetY() < rect.GetY2());
}
void Spot::set_color(SDL2pp::Color color) {
    this->color = color;
}
void Spot::setOriginalColor() {
    this->color = originalColor;
}

