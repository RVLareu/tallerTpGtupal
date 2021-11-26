#include "piece.h"

class Queen : public Piece {
    private:

    public:
        Queen(int color, float p);

    std::vector<std::tuple<int, int>> can_move(int origin_row, int origin_col) override;
};