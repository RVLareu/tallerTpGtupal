#include "piece.h"
#include <iostream>

Piece::Piece(int color, int probability_fraction, std::string name) :
                                        alive(true),                                                 
                                        color(color),
                                        probability_fraction(probability_fraction), 
                                        name(name){

}

bool Piece::is_white() {
    return this->color == 0;
}

void Piece::set_prob(int probability_fraction) {
    this->probability_fraction = probability_fraction;
}
