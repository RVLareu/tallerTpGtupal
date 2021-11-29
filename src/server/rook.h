#include "piece.h"

class Rook : public Piece {
    private:

    public:
        Rook(int color, int probability_fraction);


    std::vector<std::tuple<int, int>> can_move(int origin_row, int origin_col) override;
};