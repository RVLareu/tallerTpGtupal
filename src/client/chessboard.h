#include <list>
#include <vector>
#include <map>
#include <string>
#include "renderpiece.h"
#include "spot.h"
#include <SDL2pp/SDL2pp.hh>

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

class ChessBoard {
    private:
        std::map<char, std::string> map_pieces;
        
        std::list<RenderPiece> pieces;
        
        std::list<Spot> spots;
        
        std::list<Spot> spots_painted;
        
        SDL2pp::Renderer& renderer;
        
        SDL2pp::Point clickOffset;
        
        void drawCircle(SDL2pp::Renderer& renderer, int radius, int centreX, int centreY);
        
    public:
        ChessBoard(SDL2pp::Renderer& renderer);
        
        void create_spots();
        
        bool move_piece_if_selected(int pos_x, int pos_y);
        
        void select_piece(SDL2pp::Point mousePos);
        
        void render();
        
        void render_from_vector(std::vector<char> board);
        
        std::tuple<int, int> mouse_position_to_square(SDL2pp::Point mousePos);
};

#endif

