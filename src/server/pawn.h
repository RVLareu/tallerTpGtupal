#include "piece.h"

class Pawn : public Piece {
    private:
        bool first_move_done;
    public:
        Pawn(int color, int probability_fraction_den, int probability_fraction_num);
        
        std::vector<Piece*> split();

    std::vector<std::tuple<int, int>> can_move(int origin_row, int origin_col) override;

    //~Pawn();
};
