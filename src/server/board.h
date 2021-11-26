#include "piece.h"

#include <vector>
#include <map>
using namespace std;

class Board;

typedef std::map<int, map<int,Piece*>> board_map;

class Board {
    private:        
        board_map board;        

        bool in_bounds(int col, int row);

        int sign(int n);
    public:

        Board();

        void create_board();
        
        // Check if square has piece or not
        bool square_is_empty(int row, int col);

        vector<tuple<int, int>> piece_can_move(int row, int col);
        
        void move_piece(int start_row, int start_col, int end_row, int end_col);

        void print_board();

        vector<tuple<int, int>> filter_possible_movements(std::vector<std::tuple<int, int>> positions_available, int row, int col, Piece * piece);

};