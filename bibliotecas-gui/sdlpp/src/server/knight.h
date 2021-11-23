#include "piece.h"

class Knight : public Piece {
    private:

    public:
        Knight(int col, int row, int color, float p);

        bool can_move(int col, int row);
};