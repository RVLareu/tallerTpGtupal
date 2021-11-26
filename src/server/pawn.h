#include "piece.h"

class Pawn : public Piece {
    private:
        bool first_move_done;
    public:
        Pawn(int color, float p);

    std::vector<std::tuple<int, int>> can_move(int origin_row, int origin_col) override;

    //~Pawn();
};
