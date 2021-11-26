#include "pawn.h"
#include <iostream>
Pawn::Pawn(int color, float p) : Piece(color, p, color == 1 ? "p" : "P"), first_move_done(false) {

}

/*
    No devuelve posiciones en diagonal (captura) -> TODO ?
*/

std::vector<std::tuple<int, int>> Pawn::can_move(int origin_row, int origin_col) {
    std::vector<std::tuple<int, int>> possible_moves;
    // 1 BLACK (top of chessboard), 0 WHITE (bottom of chessboard)
    if (this->color == 1) {
        possible_moves.emplace_back(origin_row + 1, origin_col);
        if (!first_move_done) {
            possible_moves.emplace_back(origin_row + 2, origin_col);
        }
    } else {
        possible_moves.emplace_back(origin_row - 1, origin_col);
        if (!first_move_done) {
            possible_moves.emplace_back(origin_row - 2, origin_col);
        }
    }
    std::cout << "Pawn\n";
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
