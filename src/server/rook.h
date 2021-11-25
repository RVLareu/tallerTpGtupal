#include "piece.h"

class Rook : public Piece {
    private:

    public:
        Rook(int col, int row, int color, float p);


    std::vector<std::tuple<int, int>> can_move(int col, int row) override;
};