#include <tuple>
#include <vector>

#ifndef PIECE_H
#define PIECE_H

class Piece {
    private:

    public:
        // 1 black, 0 white
        int color;

        bool superposition;

        int probability_fraction;

        std::string name;

        bool selected;        

        Piece(int color, int probability_fraction, std::string name);
                
        bool is_white();                
        
        void set_prob(int probability_fraction);
        
        bool is_selected();

        void select_piece();

        void unselect_piece();

        virtual std::vector<std::tuple<int, int>> can_move(int origin_row, int origin_col) = 0;
     
};

#endif

