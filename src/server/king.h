#include "piece.h"

class King : public Piece {
    private:
        
    public:
        King(int col, int row, int color, float p);

    std::vector<std::tuple<int, int>> can_move(int col, int row) override;
};