#include "piece.h"

class King : public Piece {
    private:

    public:
        King(int col, int row, int color, float p);

        bool can_move(int col, int row);
};