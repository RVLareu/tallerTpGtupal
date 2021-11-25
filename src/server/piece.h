#include <tuple>
#include <vector>

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

        std::string name;

        Piece();

        Piece(int col, int row, int color, float p, std::string name);
        
        std::tuple<int, int> get_position();
        
        bool is_white();
        
        void set_position(int col, int row);
        
        void set_prob(float p);
        
        virtual std::vector<std::tuple<int, int>> can_move(int col, int row) = 0;

        // virtual ~Piece() = 0;
};

#endif

