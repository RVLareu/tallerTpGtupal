#include "piece.h"

class Bishop : public Piece {
    private:

    public:
        Bishop(int color, int probability_fraction);

        void split();

        std::vector<std::tuple<int, int>> can_move(int origin_row, int origin_col) override;
};
