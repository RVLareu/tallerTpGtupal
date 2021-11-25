#include "square.h"

#include <vector>
#include <map>
using namespace std;

class Board;

typedef vector<tuple<int, int>> (Board::*board_method_t)(int,int);
typedef map<string, board_method_t> board_piece_map;



class Board {
    private:
        std::vector<std::vector<Square>> board;

        board_piece_map pieces_movement;

        void set_movement_rules();

        vector<tuple<int, int>> king_possible_moves(int col, int row);

        bool in_bounds(int col, int row);

    public:

        Board();

        void create_board();

        void print_board();

        vector<tuple<int, int>> piece_can_move(int col, int row);

        


};