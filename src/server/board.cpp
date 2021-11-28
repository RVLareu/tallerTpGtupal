#include "board.h"

#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"

#include <iostream>
#include <functional>
#include <cctype>
#include <algorithm>



int Board::sign(int n) {
    if (n > 0) {
        return 1;
    } else if (n < 0) {
        return -1;
    } else {
        return 0;
    }
}

Board::Board() {
    create_board();
}


void Board::create_board() {  
    // 1 black, 0 white
    /*
        PAWNS
    */
    for (int col = 0; col < 8; col++) {
        board[1][col] = new Pawn(1,float(1));
        board[6][col] = new Pawn(0,float(1));        
    }

    // /*
    //     ROOKS
    // */        
    board[0][7] =new Rook(1, float(1));
    board[0][0] =new Rook(1, float(1));

    board[7][0] =new Rook(0, float(1));
    board[7][7] =new Rook(0, float(1));
    // /*
    //     KNIGHTS
    // */
    board[0][1] = new Knight(1, float(1));
    board[0][6] = new Knight(1, float(1));
 
    board[7][1] = new Knight(0, float(1));
    board[7][6] = new Knight(0, float(1));
    // /*
    //     BISHOPS
    // */
    board[0][2] =new Bishop(1, float(1));
    board[0][5] =new Bishop(1, float(1));

    board[7][2] =new Bishop(0, float(1));
    board[7][5] =new Bishop(0, float(1));    
    // /*
    //     QUEENS
    // */
    board[0][4] =new Queen(1, float(1));
    // board[4][4] =new Queen(4, 4, 1, float(1));

    board[7][4] =new Queen(0, float(1));

    // /*
    //     KINGS
    // */
    board[0][3] =new King(1, float(1));

    board[7][3] =new King(0, float(1));

}

// bool Board::in_bounds(int col, int row) {
//     if (row > 7 || col > 7 || row < 0 || col < 0) return false;
//     return true;
// }

bool Board::is_piece_white(int row, int col) {
    return board[row][col]->is_white();
}

int Board::move_piece(int start_row, int start_col, int end_row, int end_col) {
    // por alguna razon vine vacio este vector, la funcion calcula bien
    //std::vector<std::tuple<int, int>> piece_moves = get_piece_possible_movements(start_row, start_col);
    //for (auto move : piece_moves) {
    //    std::cout << std::get<0>(move) << std::get<1>(move);
    
       // if (std::get<0>(move) == end_row and std::get<1>(move) == end_col) {
            Piece * piece = board.at(start_row).at(start_col);
            board[start_row].erase(start_col);
            board[end_row][end_col] = piece;
            return 1;
        //}
    //}
    return 0;


    
}

vector<tuple<int, int>> Board::filter_possible_movements(std::vector<std::tuple<int, int>> positions_available, int row, int col, Piece * piece) {
    std::vector<std::tuple<int, int>> final_pos;
    
    //Si no es caballo, se verifica que no haya piezas entre el origen y el destino
    if (piece->name != "n") {
        for (auto square_dest : positions_available) {
            
            // Vectores con la dirección del movimiento de la pieza
            int row_dir = sign(std::get<0>(square_dest) - row);
            int col_dir = sign(std::get<1>(square_dest) - col);
            std::tuple<int, int> current(row + row_dir, col + col_dir);            

            int erased = false;
            while(1) {
                if (!this->square_is_empty(std::get<0>(current),std::get<1>(current))) {                    
                    erased = true;
                    break;
                }
                if (std::get<0>(square_dest) ==  std::get<0>(current) and std::get<1>(square_dest) == std::get<1>(current)) {
                    break;
                }
                std::get<0>(current) += row_dir;
                std::get<1>(current) += col_dir;
            }
            if (!erased) {
                final_pos.push_back(square_dest);
            }
    
        }
    } else {
        for (auto square_dest : positions_available) {
            if (this->square_is_empty(std::get<0>(square_dest), std::get<1>(square_dest))) {
                final_pos.push_back(square_dest);
            }
        }           
    }
    
    return std::move(final_pos);
}


std::vector<std::tuple<int, int>> Board::get_piece_possible_movements(int row, int col) {
    std::vector<std::tuple<int, int>> positions_available;
    if (!this->square_is_empty(row, col)) {
        positions_available = board[row][col]->can_move(row, col);
        vector<tuple<int, int>> final_pos = filter_possible_movements(std::move(positions_available), row, col, board[row][col]);
        
        //print 
        std::cout << "BOARD\n";      
        for (int row = 0; row < 8; row ++) {
            for (int col = 0; col < 8; col++) {
                int found = 0;
                for (auto t: final_pos) {
                    
                    if (std::get<0>(t) == row and std::get<1>(t) == col) {
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
    }

 

    return std::move(positions_available);
}


bool Board::square_is_empty(int row, int col) {
    if (board.count(row) > 0) {
        if (board[row].count(col) > 0){                    
            return false;
        }                
    }
    return true;
}

std::tuple<int, int> Board::get_selected_piece_position() {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (!square_is_empty(row, col)) {
                if (board.at(row).at(col)->is_selected()) {
                    return std::tuple<int, int>{row, col};
                }
            }
        }
    }
    return std::tuple<int, int>{NULL, NULL};
}

bool Board::is_any_piece_selected() {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (!square_is_empty(row, col)) {
                if (board.at(row).at(col)->is_selected()) {
                    return true;
                }
            }
        }
    }
    return false;
}


void Board::select_piece(int row, int col) {
    board.at(row).at(col)->select_piece();
}

void Board::unselect_piece(int row, int col) {
    board.at(row).at(col)->unselect_piece();
}


void Board::print_board() {    
    std::cout << "\n";    
     for (int row = 0; row < 8; row++) {
         for (int col = 0; col < 8; col ++) {
             if (!this->square_is_empty(row, col)){
                 std::cout << " " << board[row][col]->name << " ";                
             } else {
                 std::cout << " - ";
             }
         }
         std::cout << "\n";
     }
    
    /*for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col ++) {
            if (!this->square_is_empty(row, col)){
                Piece * piece = board[row][col];                
                std::cout << "*";
                std::cout << piece->name;
                std::cout << "*," << 1 << "," << col << ","<< row << ","<< 1;   
                if (row != 7 || col !=7) {
                    std::cout << ",";
                }              
            }
        }        
    }*/
    
}



std::vector<char> Board::get_vector_board() {    
    std::vector<char> vector_board;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col ++) {
            if (!this->square_is_empty(row, col)){
                Piece * piece = board[row][col];
                vector_board.push_back((char)piece->name[0]);
                vector_board.push_back(1);
                vector_board.push_back(row); 
                vector_board.push_back(col);
                vector_board.push_back(1);
            }
        }        
    }
    return std::move(vector_board);
}

