#include "piece.h"

class Bishop : public Piece {
    private:

    public:
        Bishop(int col, int row, int color, float p);
        bool can_move(int col, int row);
};
