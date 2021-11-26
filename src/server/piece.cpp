#include "piece.h"
#include <iostream>

Piece::Piece(int color, float p, std::string name) :                                                 
                                        color(color),
                                        p(p), 
                                        name(name){
}

bool Piece::is_white() {
    return this->color;
}

void Piece::set_prob(float p) {
    this->p = p;
}

