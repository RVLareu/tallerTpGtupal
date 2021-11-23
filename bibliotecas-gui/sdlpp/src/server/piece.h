#include <tuple>

#ifndef PIECE_H
#define PIECE_H

class Piece {
    private:

    public:
        int color;

        bool superposicion;

        float p;
        
        int col;
        
        int row; 

        Piece();

        Piece(int col, int row, int color, float p);
        
        std::tuple<int, int> get_position();
        
        bool is_white();
        
        void set_position(int col, int row);
        
        void set_prob(float p);
        
        virtual bool can_move(int col, int row);
};

#endif

