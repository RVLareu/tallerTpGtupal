#include <SDL2pp/SDL2pp.hh>


#ifndef SPOT_H
#define SPOT_H

class Spot {
    private:
        SDL2pp::Renderer& renderer;
        
        SDL2pp::Rect rect;
        
        SDL2pp::Color originalColor;

    public:
        bool selected;
        
        SDL2pp::Color color;
        
        Spot(SDL2pp::Renderer& renderer, SDL2pp::Rect rect, SDL2pp::Color color);
        
        void render();
        
        bool clicked(SDL2pp::Point mousePos);
        
        void set_color(SDL2pp::Color color);
        
        void setOriginalColor();
};

#endif

