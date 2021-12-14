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
        
        
    public:
        ChessBoard(SDL2pp::Renderer& renderer);
        
        // crea los casillers
        void create_spots();
        
        void render();
        
        // renderiza a partir de un vector con estado del tablero
        void render_from_vector(std::vector<char> board);
        
        // traduce una posicion del mouse a una posicion en el tablero
        std::tuple<int, int> mouse_position_to_square(SDL2pp::Point mousePos);
};

#endif

