#include "piece.h"

class Bishop : public Piece {
    private:

    public:
        Bishop(int col, int row, int color, float p);
        std::vector<std::tuple<int, int>> can_move(int col, int row) override;
};
