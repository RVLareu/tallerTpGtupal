#include "piece.h"

class Pawn : public Piece {
    private:
        bool first_move_done;
    public:
        Pawn(int col, int row, int color, float p);

    std::vector<std::tuple<int, int>> can_move(int col, int row) override;

    //~Pawn();
};
