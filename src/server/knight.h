#include "piece.h"

class Knight : public Piece {
    public:
        Knight(int color, int probability_fraction);

        std::vector<Piece*> split();

    std::vector<std::tuple<int, int>> can_move(int origin_row, int origin_col) override;
};