#include "piece.h"
#include <iostream>

Piece::Piece(int color, int probability_fraction, std::string name) :
                                        alive(true),                                                 
                                        color(color),
                                        probability_fraction(probability_fraction), 
                                        name(name),
                                        selected(false){

}

bool Piece::is_white() {
    return this->color == 0;
}

void Piece::set_prob(int probability_fraction) {
    this->probability_fraction = probability_fraction;
}

bool Piece::is_selected() {
    return selected;
}

void Piece::select_piece() {
    selected = true;
}

void Piece::unselect_piece() {
    selected = false;
}
