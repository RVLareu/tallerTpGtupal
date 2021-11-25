#include "rook.h"

#include <vector>
#include <iostream>

Rook::Rook(int col, int row, int color, float p) : Piece(col, row, color, p, "r") {
    
}
/*
    Returns every possible square a rook could go given a starting position
    in an empty chess board
*/
std::vector<std::tuple<int, int>> Rook::can_move(int col, int row) {
    std::vector<std::tuple<int, int>> possible_moves;
    int r_col = this->col;
    int r_row = this->row;
    for (int aux_col = 0; aux_col< 8; aux_col++) {
        for (int aux_row = 0; aux_row < 8; aux_row++) {
            if ((aux_col == col) || (aux_row == row)) {
                possible_moves.emplace_back(aux_row, aux_col);
            }
        }
    }

    //print 
    std::cout << "Rook\n";
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
