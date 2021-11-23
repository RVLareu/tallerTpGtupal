#include "piece.h"

class Queen : public Piece {
    private:

    public:
        Queen(int col, int row, int color, float p);

        bool can_move(int col, int row);
};