#include "rook.h"

#include <vector>
#include <iostream>

Rook::Rook(int color, int probability_fraction_den, int probability_fraction_num) : Piece(color, probability_fraction_den, probability_fraction_num, color == 1 ? "r" : "R") {
    
}


/*
    Returns every possible square a rook could go given a starting position
    in an empty chess board
*/
std::vector<std::tuple<int, int>> Rook::can_move(int origin_row, int origin_col) {
    std::vector<std::tuple<int, int>> possible_moves;
    for (int aux_row = 0; aux_row< 8; aux_row++) {
        for (int aux_col = 0; aux_col < 8; aux_col++) {
            if (!(aux_col == origin_col) != !(aux_row == origin_row)) {
                possible_moves.emplace_back(aux_row, aux_col);
            }
        }
    }


    //print 
    std::cout << "Rook\n";
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


std::vector<Piece*> Rook::split() {
    std::cout << "SPLITING";
    this->right_child = new Rook(this->color, this->probability_fraction_den * 2, probability_fraction_num);
    this->left_child = new Rook(this->color, this->probability_fraction_den * 2, probability_fraction_num);

    right_child->parent = this;
    left_child->parent = this;

    std::vector<Piece*> childs;
    childs.push_back(right_child);
    childs[0]->parent = this;
    childs.push_back(left_child);
    childs[1]->parent = this;

    return childs; 
}
