#include "pawn.h"
#include <iostream>
Pawn::Pawn(int color, int probability_fraction_den, int probability_fraction_num) : Piece(color, probability_fraction_den, probability_fraction_num, color == 1 ? "p" : "P"), first_move_done(false) {

}

/*
    No devuelve posiciones en diagonal (captura) -> TODO ?
*/

std::vector<std::tuple<int, int>> Pawn::can_move(int origin_row, int origin_col) {
    std::vector<std::tuple<int, int>> possible_moves;
    // 1 BLACK (top of chessboard), 0 WHITE (bottom of chessboard)
    if (this->color == 1) {
        //Hacia adelante
        possible_moves.emplace_back(origin_row + 1, origin_col);   
        if (origin_row == 1){ //Es su primer movimiento
            possible_moves.emplace_back(origin_row + 2, origin_col);            
        }            
        //En diagonal (para comer)
        possible_moves.emplace_back(origin_row + 1, origin_col + 1);
        possible_moves.emplace_back(origin_row + 1, origin_col - 1);        
    } else {
        //Hacia adelante
        possible_moves.emplace_back(origin_row - 1, origin_col);                
        if (origin_row == 6){ //Es su primer movimiento            
            possible_moves.emplace_back(origin_row - 2, origin_col);
        }            
        //En diagonal (para comer)
        possible_moves.emplace_back(origin_row - 1, origin_col + 1);
        possible_moves.emplace_back(origin_row - 1, origin_col - 1);        
    }
    return std::move(possible_moves);

}




std::vector<Piece*> Pawn::split() {
    this->right_child = new Pawn(this->color, this->probability_fraction_den * 2, probability_fraction_num);
    this->left_child = new Pawn(this->color, this->probability_fraction_den * 2, probability_fraction_num);

    right_child->parent = this;
    left_child->parent = this;

    std::vector<Piece*> childs;
    childs.push_back(right_child);
    childs[0]->parent = this;
    childs.push_back(left_child);
    childs[1]->parent = this;

    return std::move(childs);
}

Piece* Pawn::merge(Piece* pawn) {
    // creo nodo merge y asigna la suma de la probabilidad de ambos padres
    Pawn* new_pawn = new Pawn(this->color, this->probability_fraction_den, probability_fraction_num);
    this->right_child = new_pawn;
    new_pawn->parent_left_merge = this;
    
    new_pawn->den_from_left_merge = this->probability_fraction_den;
    new_pawn->num_from_left_merge = this->probability_fraction_num;


    pawn->right_child = new_pawn;
    new_pawn->receive_probability(pawn->probability_fraction_den, pawn->probability_fraction_num);


    new_pawn->parent_right_merge = pawn;
    new_pawn->den_from_right_merge = pawn->probability_fraction_den;
    new_pawn->num_from_right_merge = pawn->probability_fraction_num;


    return new_pawn;
}


