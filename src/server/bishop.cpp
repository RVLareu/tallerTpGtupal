#include "bishop.h"
#include <iostream>
Bishop::Bishop(int color, int probability_fraction) : Piece(color, probability_fraction, color == 1 ? "b" : "B") {

}

/*
    Returns every possible square a bishop could go given a starting position
    in an empty chess board
*/
std::vector<std::tuple<int, int>> Bishop::can_move(int origin_row, int origin_col) {
    std::vector<std::tuple<int, int>> possible_moves;    
    for (int aux_row = 0; aux_row< 8; aux_row++) {
        for (int aux_col = 0; aux_col < 8; aux_col++) {
            if (!(aux_col - origin_col == aux_row - origin_row) != !(aux_col - origin_col == -(aux_row - origin_row))) {
                possible_moves.emplace_back(aux_row, aux_col);
            }
        }
    }

    //print
    std::cout << "Bishop\n";
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



