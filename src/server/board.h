
#include "piece.h"

#include <vector>
#include <tuple>
#include <map>

using namespace std;

#ifndef BOARD_H
#define BOARD_H


class Board;

typedef map<int, map<int,Piece*>> board_map;

class Board {
    private:        

        bool in_bounds(int col, int row);

        int sign(int n);
        
        tuple<int, int> selected_piece_position;

    public:
        board_map board;        

        vector<tuple<int, int>> piece_moves;        

        Board();

        void create_board();
        
        // Check if square has piece or not
        bool square_is_empty(int row, int col);

        vector<tuple<int, int>> get_piece_possible_movements(int row, int col);
        
        int move_piece(int start_row, int start_col, int end_row, int end_col);

        void print_board();

        vector<tuple<int, int>> filter_possible_movements(vector<tuple<int, int>> positions_available, int row, int col, Piece * piece);

        tuple<int, int> get_selected_piece_position();

        void select_piece(int row, int col);

        void unselect_piece(int row, int col);

        bool is_piece_white(int row, int col);
        
        bool is_any_piece_selected();

        std::vector<char> get_vector_board();
};

#endif
