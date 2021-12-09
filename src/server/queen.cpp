#include "queen.h"
#include <iostream>

Queen::Queen(int color, int probability_fraction) : Piece(color, probability_fraction, color == 1 ? "q" : "Q") {
    
}

std::vector<std::tuple<int, int>> Queen::can_move(int origin_row, int origin_col) {
    std::vector<std::tuple<int, int>> possible_moves;    
    // diagonals
    for (int aux_row = 0; aux_row< 8; aux_row++) {
        for (int aux_col = 0; aux_col < 8; aux_col++) {
            if (!(aux_col - origin_col == aux_row - origin_row) != !(aux_col - origin_col == -(aux_row - origin_row))) {
                possible_moves.emplace_back(aux_row, aux_col);
            }
        }
    }
    // same row / col
    for (int aux_col = 0; aux_col< 8; aux_col++) {
        for (int aux_row = 0; aux_row < 8; aux_row++) {
            if (!(aux_col == origin_col) != !(aux_row == origin_row)) {
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




std::vector<Piece*> Queen::split() {
    this->right_child = new Queen(this->color, this->probability_fraction_den * 2);
    this->left_child = new Queen(this->color, this->probability_fraction_den * 2);

    right_child->parent = this;
    left_child->parent = this;

    std::vector<Piece*> childs;
    childs.push_back(right_child);
    childs[0]->parent = this;
    childs.push_back(left_child);
    childs[1]->parent = this;

    return childs; 
}
