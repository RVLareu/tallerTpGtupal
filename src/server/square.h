#include "piece.h"
#include <vector>

class Square {
    private:
        int col;
        
        int row;
        
        Piece piece;
        
        bool empty;
    public:
        Square(int col, int row);
        
        void set_piece(Piece piece);
        
        void set_col(int col);
        
        void set_row(int row);
        
        bool is_empty();

        void empty_square();
};
