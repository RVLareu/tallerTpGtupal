#include "square.h"
#include <iostream>
#include <functional>

Square::Square(int col, int row) : col(col), row(row), empty(true) {

}

Square::Square() {

}

void Square::set_piece(Piece* piece) {
    this->piece = piece;
    this->empty = false;
}

void Square::empty_square() {
    this->piece = nullptr;
    this->empty = true;
}

void Square::set_col(int col) {
    this->col = col;
}

void Square::set_row(int row) {
    this->row = row;
}

bool Square::is_empty() {
    return empty;
}

Piece* Square::get_piece() {
    return this->piece;
}

std::vector<std::tuple<int, int>> Square::piece_can_move(int col, int row) {


    return std::move(this->piece->can_move(col, row));
}

Square::~Square() {
}

