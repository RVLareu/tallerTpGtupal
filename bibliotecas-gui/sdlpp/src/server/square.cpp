#include "square.h"

#include <functional>

Square::Square(int col, int row) : col(col), row(row) {

}


void Square::set_piece(Piece piece) {
    this->piece = std::move(piece);
    this->empty = false;
}

void Square::empty_square() {
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