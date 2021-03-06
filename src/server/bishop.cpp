#include "bishop.h"
#include <iostream>
Bishop::Bishop(int color, int probability_fraction_den, int probability_fraction_num) : Piece(color, probability_fraction_den, probability_fraction_num, color == 1 ? "b" : "B") {

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
    return std::move(possible_moves);
}

std::vector<Piece*> Bishop::split() {
    this->right_child = new Bishop(this->color, this->probability_fraction_den * 2, probability_fraction_num);
    this->left_child = new Bishop(this->color, this->probability_fraction_den * 2, probability_fraction_num);

    right_child->parent = this;
    left_child->parent = this;

    std::vector<Piece*> childs;
    childs.push_back(right_child);
    childs[0]->parent = this;
    childs.push_back(left_child);
    childs[1]->parent = this;

    return childs; 
}


Piece* Bishop::merge(Piece* bishop) {
    // creo nodo merge y asigna la suma de la probabilidad de ambos padres
    Bishop* new_bishop = new Bishop(this->color, this->probability_fraction_den, probability_fraction_num);
    this->right_child = new_bishop;
    new_bishop->parent_left_merge = this;
    
    new_bishop->den_from_left_merge = this->probability_fraction_den;
    new_bishop->num_from_left_merge = this->probability_fraction_num;


    bishop->right_child = new_bishop;
    new_bishop->receive_probability(bishop->probability_fraction_den, bishop->probability_fraction_num);


    new_bishop->parent_right_merge = bishop;
    new_bishop->den_from_right_merge = bishop->probability_fraction_den;
    new_bishop->num_from_right_merge = bishop->probability_fraction_num;


    return new_bishop;
}


