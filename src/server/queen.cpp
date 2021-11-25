#include "queen.h"
#include <iostream>

Queen::Queen(int col, int row, int color, float p) : Piece(col, row, color, p, "q") {
    
}

std::vector<std::tuple<int, int>> Queen::can_move(int col, int row) {
    std::vector<std::tuple<int, int>> possible_moves;
    int b_col = this->col;
    int b_row = this->row;
    // diagonals
    for (int aux_row = 0; aux_row< 8; aux_row++) {
        for (int aux_col = 0; aux_col < 8; aux_col++) {
            if (!(aux_col - col == aux_row - row) != !(aux_col - col == -(aux_row - row))) {
                possible_moves.emplace_back(aux_row, aux_col);
            }
        }
    }
    // same row / col
    for (int aux_col = 0; aux_col< 8; aux_col++) {
        for (int aux_row = 0; aux_row < 8; aux_row++) {
            if (!(aux_col == col) != !(aux_row == row)) {
                possible_moves.emplace_back(aux_row, aux_col);
            }
        }
    }


//print 
    std::cout << "Queen\n";
    for (int row = 0; row < 8; row ++) {
        for (int col = 0; col < 8; col++) {
            int found = 0;
            for (auto t: possible_moves) {
                
                if (std::get<0>(t) == row and std::get<1>(t) == col) {
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
