#include "knight.h"
#include <iostream>
Knight::Knight(int col, int row, int color, float p) : Piece(col, row, color, p, "n") {

}

std::vector<std::tuple<int, int>> Knight::can_move(int col, int row) {
    std::vector<std::tuple<int, int>> possible_moves;
    std::vector<int> col_offset = {-2, -1, 1, 2, 2, 1, -1, -2};
    std::vector<int> row_offset = {1, 2, 2, 1, -1, -2, -2, -1};

    int n_col = this->col;
    int n_row = this->row;
    for (int off = 0; off < 8; off++) {
        int dst_row = n_row + row_offset[off];
        int dst_col = n_col + col_offset[off];

        if (dst_row >= 0 and dst_row < 8 and dst_col >= 0 and dst_col < 8) {
            possible_moves.emplace_back(dst_row, dst_col);
        }
    }

//print 
    std::cout << "Knight\n";
    std::vector<std::tuple<int, int>>::iterator it;
    for (int i = 0; i < 8; i ++) {
        for (int j = 0; j < 8; j++) {
            int found = 0;
            for (auto t: possible_moves) {
                
                if (std::get<0>(t) == i and std::get<1>(t) == j) {
                    std::cout << " x ";
                    found = 1;
                    break;
                }

            }
            if (found == 0) {
                std::cout << " . ";
            }
        }
        std::cout << "\n";
    }
    return std::move(possible_moves);
}
