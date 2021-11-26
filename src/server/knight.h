#include "piece.h"

class Knight : public Piece {
    public:
        Knight(int color, float p);

    std::vector<std::tuple<int, int>> can_move(int origin_row, int origin_col) override;
};