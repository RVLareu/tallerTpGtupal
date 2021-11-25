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

        bool in_bounds(int col, int row);

    public:

        Board();

        void create_board();

        vector<tuple<int, int>> piece_can_move(int col, int row);
        
        void move_piece(int start_col, int start_row, int end_col, int end_row);

        void print_board();

        ~Board();


};