#include "piece.h"
#include <iostream>
Piece::Piece() {
    
}



Piece::Piece(int col, int row, int color, float p, std::string name) : 
                                                col(col),
                                                    row(row),
                                                        color(color),
                                                            p(p), name(name){

}
std::tuple<int, int> Piece::get_position() {
    std::tuple<int, int> position;
    std::get<0>(position) = this->row;
    std::get<1>(position) = this->col;
    return std::move(position);
}

bool Piece::is_white() {
    return this->color;
}

void Piece::set_position(int col, int row) {
    this->col = col;
    this->row = row;
}
void Piece::set_prob(float p) {
    this->p = p;
}

std::vector<std::tuple<int, int>> Piece::can_move(int col, int row) {
    std::vector<std::tuple<int, int>> moves;
    std::cout << "ASDASDSAAAAAAAAAAAAa";
    return moves;
}

