#include "piece.h"

class King : public Piece {
    private:
        
    public:
        King(int color, float p);

    std::vector<std::tuple<int, int>> can_move(int origin_row, int origin_col) override;
};