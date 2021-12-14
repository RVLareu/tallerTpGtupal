#include "piece.h"

class Rook : public Piece {
    private:

    public:
        Rook(int color, int probability_fraction_den, int probability_fraction_num);

        std::vector<Piece*> split();

        Piece* merge(Piece* rook);
        
        std::vector<std::tuple<int, int>> can_move(int origin_row, int origin_col) override;
};