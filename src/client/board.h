#include <list>
#include <vector>
#include <map>
#include <string>
#include "piece.h"
#include "spot.h"
#include <SDL2pp/SDL2pp.hh>

#ifndef BOARD_H
#define BOARD_H

class Board {
    private:
        std::map<char, std::string> map_pieces;
        
        std::list<Piece> pieces;
        
        std::list<Spot> spots;
        
        std::list<Spot> spots_painted;
        
        SDL2pp::Renderer& renderer;
        
        SDL2pp::Point clickOffset;
        
        void drawCircle(SDL2pp::Renderer& renderer, int radius, int centreX, int centreY);
        
    public:
        Board(SDL2pp::Renderer& renderer);
        
        void create_spots();
        
        bool move_piece_if_selected(int pos_x, int pos_y);
        
        void select_piece(SDL2pp::Point mousePos);
        
        void render();
        
        void render_from_vector(std::vector<char> board);
        
        int position_to_spot(SDL2pp::Point mousePos);
};

#endif

