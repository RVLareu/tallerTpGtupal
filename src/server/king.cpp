#include "king.h"
#include <cmath>
#include <iostream>
King::King(int col, int row, int color, float p) : Piece(col, row, color, p, "k") {
    
}

std::vector<std::tuple<int, int>> King::can_move(int col, int row) {
    std::vector<std::tuple<int, int>> possible_moves;
    int k_col = this->col;
    int k_row = this->row;
    for (int aux_col = 0; aux_col< 8; aux_col++) {
        for (int aux_row = 0; aux_row < 8; aux_row++) {
            float distance = sqrt(pow(aux_col - k_col, 2) + pow(aux_row - k_row, 2) * 1.0);
            if (distance < 1.45 and distance > 0.0) {
                possible_moves.emplace_back(aux_row, aux_col);
            }
        }
    }
    std::cout << "KING\n";
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
