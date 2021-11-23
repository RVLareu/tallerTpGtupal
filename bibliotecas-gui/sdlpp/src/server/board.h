#include "square.h"

#include <vector>

class Board {
    private:
        std::vector<std::vector<Square>> board;
    public:
        Board();

        void create_board();

        void print_board();
};