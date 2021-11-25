#include "piece.h"

class Queen : public Piece {
    private:

    public:
        Queen(int col, int row, int color, float p);

    std::vector<std::tuple<int, int>> can_move(int col, int row) override;
};