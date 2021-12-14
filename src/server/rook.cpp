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

    return std::move(possible_moves);
}


std::vector<Piece*> Rook::split() {
    this->right_child = new Rook(this->color, this->probability_fraction_den * 2, probability_fraction_num);
    this->left_child = new Rook(this->color, this->probability_fraction_den * 2, probability_fraction_num);

    right_child->parent = this;
    left_child->parent = this;

    std::vector<Piece*> childs;
    childs.push_back(right_child);
    childs[0]->parent = this;
    childs.push_back(left_child);
    childs[1]->parent = this;

    return std::move(childs); 
}


Piece* Rook::merge(Piece* rook) {
    // creo nodo merge y asigna la suma de la probabilidad de ambos padres
    Rook* new_rook = new Rook(this->color, this->probability_fraction_den, probability_fraction_num);
    this->right_child = new_rook;
    new_rook->parent_left_merge = this;
    
    new_rook->den_from_left_merge = this->probability_fraction_den;
    new_rook->num_from_left_merge = this->probability_fraction_num;


    rook->right_child = new_rook;
    new_rook->receive_probability(rook->probability_fraction_den, rook->probability_fraction_num);


    new_rook->parent_right_merge = rook;
    new_rook->den_from_right_merge = rook->probability_fraction_den;
    new_rook->num_from_right_merge = rook->probability_fraction_num;


    return new_rook;
}