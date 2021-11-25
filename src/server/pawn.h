#include "piece.h"

class Pawn : public Piece {
    private:

    public:
        Pawn(int col, int row, int color, float p);
        bool can_move(int col, int row);
};
