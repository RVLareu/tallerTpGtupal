#include "queen.h"
#include <iostream>

Queen::Queen(int color, int probability_fraction_den, int probability_fraction_num) : Piece(color, probability_fraction_den, probability_fraction_num, color == 1 ? "q" : "Q") {
    
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
    // std::cout << "Queen\n";
    // for (int row = 0; row < 8; row ++) {
    //     for (int col = 0; col < 8; col++) {
    //         int found = 0;
    //         for (auto t: possible_moves) {
                
    //             if (std::get<0>(t) == row and std::get<1>(t) == col) {
    //                 std::cout << " x ";
    //                 found = 1;
    //                 break;
    //             }

    //         }
    //         if (found == 0) {
    //             std::cout << " . ";
    //         }
    //     }
    //     std::cout << "\n";
    // }
    return std::move(possible_moves);
}




std::vector<Piece*> Queen::split() {
    this->right_child = new Queen(this->color, this->probability_fraction_den * 2, probability_fraction_num);
    this->left_child = new Queen(this->color, this->probability_fraction_den * 2, probability_fraction_num);

    right_child->parent = this;
    left_child->parent = this;

    std::vector<Piece*> childs;
    childs.push_back(right_child);
    childs[0]->parent = this;
    childs.push_back(left_child);
    childs[1]->parent = this;

    return childs; 
}


Piece* Queen::merge(Piece* queen) {
    // creo nodo merge y asigna la suma de la probabilidad de ambos padres
    Queen* new_queen = new Queen(this->color, this->probability_fraction_den, probability_fraction_num);
    this->right_child = new_queen;
    new_queen->parent_left_merge = this;
    
    new_queen->den_from_left_merge = this->probability_fraction_den;
    new_queen->num_from_left_merge = this->probability_fraction_num;


    queen->right_child = new_queen;
    new_queen->receive_probability(queen->probability_fraction_den, queen->probability_fraction_num);


    new_queen->parent_right_merge = queen;
    new_queen->den_from_right_merge = queen->probability_fraction_den;
    new_queen->num_from_right_merge = queen->probability_fraction_num;


    return new_queen;
}
