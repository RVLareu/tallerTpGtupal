#include "king.h"
#include <cmath>
#include <iostream>
King::King(int color, int probability_fraction_den, int probability_fraction_num) : Piece(color, probability_fraction_den, probability_fraction_num, color == 1 ? "k" : "K") {
    
}

std::vector<std::tuple<int, int>> King::can_move(int origin_row, int origin_col) {
    std::vector<std::tuple<int, int>> possible_moves;
    for (int aux_col = 0; aux_col< 8; aux_col++) {
        for (int aux_row = 0; aux_row < 8; aux_row++) {
            float distance = sqrt(pow(aux_col - origin_col, 2) + pow(aux_row - origin_row, 2) * 1.0);
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


std::vector<Piece*> King::split() {
    std::cout << "SPLITING";
    this->right_child = new King(this->color, this->probability_fraction_den * 2, probability_fraction_num);
    this->left_child = new King(this->color, this->probability_fraction_den * 2, probability_fraction_num);

    right_child->parent = this;
    left_child->parent = this;

    std::vector<Piece*> childs;
    childs.push_back(right_child);
    childs[0]->parent = this;
    childs.push_back(left_child);
    childs[1]->parent = this;

    return childs; 
}
