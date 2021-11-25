#include "board.h"

#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"

#include <iostream>
#include <functional>

Board::Board() {
    create_board();
}


void Board::create_board() {

    board.resize(8);
    
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            board.at(row).push_back(std::move(Square(col, row)));
        }
    }
    
    // 1 black, 0 white
    /*
        PAWNS
    */
    for (int col = 0; col < 8; col++) {
        board.at(1).at(col).set_piece(new Pawn(col,1,1,float(1)));
        board.at(6).at(col).set_piece(new Pawn(col,6,0,float(1)));
    }

    /*
        ROOKS
    */
    board.at(0).at(7).set_piece(new Rook(7, 0, 1, float(1)));
    board.at(0).at(0).set_piece(new Rook(0, 0, 1, float(1)));

    board.at(7).at(0).set_piece(new Rook(0, 7, 0, float(1)));
    board.at(7).at(7).set_piece(new Rook(7, 7, 0, float(1)));
    /*
        KNIGHTS
    */
    board.at(0).at(1).set_piece(new Knight(1, 0, 1, float(1)));
    board.at(0).at(6).set_piece(new Knight(6, 0, 1, float(1)));

    board.at(7).at(1).set_piece(new Knight(1, 7, 0, float(1)));
    board.at(7).at(6).set_piece(new Knight(6, 7, 0, float(1)));
    /*
        BISHOPS
    */
    board.at(0).at(2).set_piece(new Bishop(2, 0, 1, float(1)));
    board.at(0).at(5).set_piece(new Bishop(5, 0, 1, float(1)));

    board.at(7).at(2).set_piece(new Bishop(2, 7, 0, float(1)));
    board.at(7).at(5).set_piece(new Bishop(5, 7, 0, float(1)));    
    /*
        QUEENS
    */
    board.at(0).at(4).set_piece(new Queen(4, 0, 1, float(1)));

    board.at(7).at(4).set_piece(new Queen(4, 7, 0, float(1)));

    /*
        KINGS
    */
    board.at(0).at(3).set_piece(new King(3, 0, 1, float(1)));

    board.at(7).at(3).set_piece(new King(3, 7, 0, float(1)));


}

bool Board::in_bounds(int col, int row) {
    if (row > 7 || col > 7 || row < 0 || col < 0) return false;
    return true;
}

void Board::move_piece(int start_col, int start_row, int end_col, int end_row) {
    Piece* piece = board.at(start_row).at(start_col).get_piece();
    board.at(end_row).at(end_col).set_piece(piece);
    board.at(start_row).at(start_col).empty_square();
}

std::vector<std::tuple<int, int>> Board::piece_can_move(int col, int row) {
    std::vector<std::tuple<int, int>> positions_available;
    if (!board.at(row).at(col).is_empty()) {
        positions_available = board.at(row).at(col).piece_can_move(col, row);
    }
    
    return std::move(positions_available);
}


void Board::print_board() {
    for (int i = 0; i < 8; i ++) {
        
        for (int j = 0; j < 8; j++) {
            if (board.at(i).at(j).is_empty()) {
                std::cout << "-";
            } else {
                std::cout << board.at(i).at(j).get_piece()->name;
            }
        }
        std::cout << "\n";
    }
}

Board::~Board() {

}

