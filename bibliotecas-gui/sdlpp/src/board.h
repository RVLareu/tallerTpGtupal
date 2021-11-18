#include <list>
#include "piece.h"
#include "spot.h"
#include <SDL2pp/SDL2pp.hh>

#ifndef BOARD_H
#define BOARD_H

class Board {
    private:
        std::list<Piece> pieces;
        std::list<Spot> spots;
        SDL2pp::Renderer& renderer;
        SDL2pp::Point clickOffset;

        void add_piece(std::string path);
    public:
        Board(SDL2pp::Renderer& renderer);
        void create_spots();
        void create_pieces();
        bool move_piece_if_selected(int pos_x, int pos_y);
        void select_piece(SDL2pp::Point mousePos);
        void render();
};

#endif

