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

}

std::vector<std::tuple<int, int>> Board::piece_can_move(int col, int row) {
     std::vector<std::tuple<int, int>> positions_available;
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
        Pawn pawnB(col, 1, 1, float(1));
        Pawn pawnW(col, 6, 0, float(1));
        board.at(1).at(col).set_piece(std::move(pawnB));
        board.at(6).at(col).set_piece(std::move(pawnW));
    }

    /*
        ROOKS
    */
    board.at(0).at(7).set_piece(std::move(Rook(7, 0, 1, float(1))));
    board.at(0).at(0).set_piece(std::move(Rook(0, 0, 1, float(1))));

    board.at(7).at(0).set_piece(std::move(Rook(0, 7, 0, float(1))));
    board.at(7).at(7).set_piece(std::move(Rook(7, 7, 0, float(1))));
    /*
        KNIGHTS
    */
    board.at(0).at(1).set_piece(std::move(Knight(1, 0, 1, float(1))));
    board.at(0).at(6).set_piece(std::move(Knight(6, 0, 1, float(1))));

    board.at(7).at(1).set_piece(std::move(Knight(1, 7, 0, float(1))));
    board.at(7).at(6).set_piece(std::move(Knight(6, 7, 0, float(1))));
    /*
        BISHOPS
    */
    board.at(0).at(2).set_piece(std::move(Bishop(2, 0, 1, float(1))));
    board.at(0).at(5).set_piece(std::move(Bishop(5, 0, 1, float(1))));

    board.at(7).at(2).set_piece(std::move(Bishop(2, 7, 0, float(1))));
    board.at(7).at(5).set_piece(std::move(Bishop(5, 7, 0, float(1))));    
    /*
        QUEENS
    */
    board.at(0).at(4).set_piece(std::move(Queen(4, 0, 1, float(1))));

    board.at(7).at(4).set_piece(std::move(Queen(4, 7, 0, float(1))));

    /*
        KINGS
    */
    board.at(0).at(3).set_piece(std::move(King(3, 0, 1, float(1))));

    board.at(7).at(3).set_piece(std::move(King(3, 7, 0, float(1))));



    set_movement_rules();
}

bool Board::in_bounds(int col, int row) {
    if (row > 7 || col > 7 || row < 0 || col < 0) return false;
    return true;
}

vector<tuple<int, int>> Board::king_possible_moves(int col, int row) {
    vector<tuple<int, int>> possible_moves;
    for (int r = -1; r < 2; r++) {
        for (int c = -1; c < 2; c ++) {
            if (r != 0 and c != 0) {
                if (in_bounds(col + c, row + r)) {
                    if (board.at(row + c).at(col + c).is_empty()) {
                        possible_moves.emplace_back(row + r, col + c);
                    }
                }
            }
        }

    }

}


void Board::set_movement_rules() {
    //board_piece_map["k"] = king_possible_moves;
    cout<<"error";
}



void Board::print_board() {
    for (int i = 0; i < 8; i++) {
        std::cout << "\n";
        for (int j = 0; j < 8; j++) {
            if (board.at(i).at(j).is_empty()) {
                std::cout << "-";

            } else {
                std::cout << "X";
            }
        }
    }
}