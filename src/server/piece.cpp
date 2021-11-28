#include "piece.h"
#include <iostream>

Piece::Piece(int color, float p, std::string name) :                                                 
                                        color(color),
                                        p(p), 
                                        name(name),
                                        selected(false){
}

bool Piece::is_white() {
    return this->color == 0;
}

void Piece::set_prob(float p) {
    this->p = p;
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
