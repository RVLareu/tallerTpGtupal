#include "piece.h"

class Knight : public Piece {
    public:
        Knight(int color, int probability_fraction_den, int probability_fraction_num);

        std::vector<Piece*> split();
Piece* merge(Piece* knight);
    std::vector<std::tuple<int, int>> can_move(int origin_row, int origin_col) override;
};