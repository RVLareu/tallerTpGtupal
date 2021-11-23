#include "piece.h"

class Rook : public Piece {
    private:

    public:
        Rook(int col, int row, int color, float p);
        bool can_move(int col, int row);
};