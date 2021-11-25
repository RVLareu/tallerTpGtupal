#include "piece.h"

class Knight : public Piece {
    private:

    public:
        Knight(int col, int row, int color, float p);

    std::vector<std::tuple<int, int>> can_move(int col, int row) override;
};