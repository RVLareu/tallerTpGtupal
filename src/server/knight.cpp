#include "knight.h"
#include <iostream>
Knight::Knight(int color, int probability_fraction_den, int probability_fraction_num) : Piece(color, probability_fraction_den, probability_fraction_num, color == 1 ? "n" : "N") {

}

std::vector<std::tuple<int, int>> Knight::can_move(int origin_row, int origin_col) {
    std::vector<std::tuple<int, int>> possible_moves;
    const std::vector<int> col_offset = {-2, -1, 1, 2, 2, 1, -1, -2};
    const std::vector<int> row_offset = {1, 2, 2, 1, -1, -2, -2, -1};
    
    for (int off = 0; off < 8; off++) {
        int dst_row = origin_row + row_offset[off];
        int dst_col = origin_col + col_offset[off];

        if (dst_row >= 0 and dst_row < 8 and dst_col >= 0 and dst_col < 8) {
            possible_moves.emplace_back(dst_row, dst_col);
        }
    }
    return std::move(possible_moves);
}


std::vector<Piece*> Knight::split() {
    this->right_child = new Knight(this->color, this->probability_fraction_den * 2, probability_fraction_num);
    this->left_child = new Knight(this->color, this->probability_fraction_den * 2, probability_fraction_num);

    right_child->parent = this;
    left_child->parent = this;

    std::vector<Piece*> childs;
    childs.push_back(right_child);
    childs[0]->parent = this;
    childs.push_back(left_child);
    childs[1]->parent = this;

    return childs; 
}

Piece* Knight::merge(Piece* knight) {
    // creo nodo merge y asigna la suma de la probabilidad de ambos padres
    Knight* new_knight = new Knight(this->color, this->probability_fraction_den, probability_fraction_num);
    this->right_child = new_knight;
    new_knight->parent_left_merge = this;
    
    new_knight->den_from_left_merge = this->probability_fraction_den;
    new_knight->num_from_left_merge = this->probability_fraction_num;


    knight->right_child = new_knight;
    new_knight->receive_probability(knight->probability_fraction_den, knight->probability_fraction_num);


    new_knight->parent_right_merge = knight;
    new_knight->den_from_right_merge = knight->probability_fraction_den;
    new_knight->num_from_right_merge = knight->probability_fraction_num;


    return new_knight;
}
