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

    return childs;
}


