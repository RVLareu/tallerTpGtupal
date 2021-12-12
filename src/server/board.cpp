#include "board.h"

#include "piece.h"
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

Board::Board(): selected_piece_position(-1,-1){
    create_board();
}


void Board::create_board() {  
    // 1 black, 0 white
    /*
        PAWNS
    */
    for (int col = 0; col < 8; col++) {
        board[1][col] = new Pawn(1,float(1), float(1));
        board[6][col] = new Pawn(0,float(1), float(1));        
    }
    
    
    // /*
    //     ROOKS
    // */        
    board[0][7] =new Rook(1, float(1), float(1));
    board[0][0] =new Rook(1, float(1), float(1));

    board[7][0] =new Rook(0, float(1), float(1));
    board[7][7] =new Rook(0, float(1), float(1));
    // /*
    //     KNIGHTS
    // */
    board[0][1] = new Knight(1, float(1), float(1));
    board[0][6] = new Knight(1, float(1), float(1));
 
    board[7][1] = new Knight(0, float(1), float(1));
    board[7][6] = new Knight(0, float(1), float(1));
    // /*
    //     BISHOPS
    // */
    board[0][2] = new Bishop(1, float(1), float(1));
    board[0][5] = new Bishop(1, float(1), float(1));

    board[7][2] = new Bishop(0, float(1), float(1));
    board[7][5] = new Bishop(0, float(1), float(1));    
    // /*
    //     QUEENS
    // */
    board[0][4] = new Queen(1, float(1), float(1));
    // board[4][4] =new Queen(4, 4, 1, float(1), float(1));

    board[7][4] = new Queen(0, float(1), float(1));

    // /*
    //     KINGS
    // */
    board[0][3] = new King(1, float(1), float(1));

    board[7][3] = new King(0, float(1), float(1));

    this->split_piece(1, 1, 2, 2, 2, 3);
    this->split_piece(2, 3, 3, 3, 3, 4);

    this->split_piece(3, 4, 3, 5, 3, 6);
    this->split_piece(3, 5, 4, 5, 4, 6);


}

// bool Board::in_bounds(int col, int row) {
//     if (row > 7 || col > 7 || row < 0 || col < 0) return false;
//     return true;
// }

bool Board::is_piece_white(int row, int col) {
    return board[row][col]->is_white();
}

int Board::split_piece(int piece_row,
                int piece_col,
                int first_splited_piece_row,
                int first_splited_piece_col,
                int second_splited_piece_row,
                int second_splited_piece_col) {
    std::vector<Piece*> pieces = board.at(piece_row).at(piece_col)->split();
    board.at(piece_row).erase(piece_col);

    board[first_splited_piece_row][first_splited_piece_col] = pieces.at(0);
    board[second_splited_piece_row][second_splited_piece_col] = pieces.at(1);
    return 0;
}

int Board::move_piece(int start_row, int start_col, int end_row, int end_col) {    
    std::vector<std::tuple<int, int>> piece_poss_moves = get_piece_possible_movements(start_row, start_col);
       
    for (auto move : piece_poss_moves) {        
        if (std::get<0>(move) == end_row and std::get<1>(move) == end_col) {
            Piece * piece = board.at(start_row).at(start_col);
            board[start_row].erase(start_col);
            board[end_row][end_col] = piece;
            return 1;
        }    
    }
    return 0;  
}

vector<tuple<int, int>> Board::filter_possible_movements(std::vector<std::tuple<int, int>> positions_available, int row, int col, Piece * piece) {
    std::vector<std::tuple<int, int>> final_pos;
    
    //Si es caballo, no verifica que no haya piezas entre el origen y el destino
    if (piece->name == "n" || piece->name == "N") {
        for (auto square_dest : positions_available) {
            bool valid_square = false;
            int dest_row =  std::get<0>(square_dest);
            int dest_col =  std::get<1>(square_dest);
            //El casillero esta vacio
            if (this->square_is_empty(dest_row, dest_col)) {
                valid_square = true;
            }
            //El casillero contiene una pieza enemiga
            else if (this->board[dest_row][dest_col]->is_white() != piece->is_white()){
                valid_square = true;
            }
            if (valid_square){
                final_pos.push_back(square_dest);
            }
        } 
    } else { //En el resto de las piezas, verifica que no haya obstaculos entre el origen y el destino
        for (auto square_dest : positions_available) {
            int dest_row =  std::get<0>(square_dest);
            int dest_col =  std::get<1>(square_dest);
            
            // Vector con la dirección del movimiento de la pieza
            int row_dir = sign(dest_row - row);
            int col_dir = sign(dest_col - col);
            int current_row = row + row_dir;
            int current_col = col + col_dir;             

            int erased = false;
            //Se va revisando cada casillero desde la posicion de origen
            // hasta la posicion destino, hasta que se tope con un obstaculo.
            while(true) {
                // Hay una pieza en la posicion actual
                if (!this->square_is_empty(current_row, current_col)) {                    
                    //Es del mismo color
                    if(this->board[current_row][current_col]->is_white() == piece->is_white()){
                        erased = true;
                        break;
                    } else{
                        // Si es enemiga, se permite solo si se encuentra en la posicion destino.
                        if (!(dest_row == current_row and dest_col == current_col)){
                            erased = true;
                            break;
                        } 
                        // Pero si es peon, se permite si además es en diagonal
                        else if (piece->name == "p" || piece->name == "P") {
                            if (col == current_col){
                                erased = true;
                                break;                      
                            }
                        }
                    }
                }
                // Si es peon, solo mueve hacia adelante en casilleros vacios
                else if (piece->name == "p" || piece->name == "P") {
                    if (col != current_col){
                        erased = true;
                        break;                      
                    }
                }
                if (dest_row == current_row and dest_col == current_col){
                    break;
                }
                current_row += row_dir;
                current_col += col_dir;
            }
            if (!erased) {
                final_pos.push_back(square_dest);
            }
    
        }
    }     
    return std::move(final_pos);
}



std::vector<std::tuple<int, int>> Board::get_piece_possible_movements(int row, int col) {
    std::vector<std::tuple<int, int>> final_pos;
    if (!this->square_is_empty(row, col)) {         
        std::vector<std::tuple<int, int>> positions_available = board[row][col]->can_move(row, col);
        final_pos = filter_possible_movements(std::move(positions_available), row, col, board[row][col]);
        
        //print 
        // std::cout << "BOARD\n";      
        for (int row = 0; row < 8; row ++) {
            for (int col = 0; col < 8; col++) {
                int found = 0;
                for (auto t: final_pos) {
                    
                    if (std::get<0>(t) == row and std::get<1>(t) == col) {
                        // std::cout << " x ";
                        found = 1;
                        break;
                    }

                }
                if (found == 0) {
                    // std::cout << " . ";
                }
            }
            // std::cout << "\n";
        }
    }
    return std::move(final_pos);
}


void Board::remove_pieces(std::vector<Piece*>  pieces) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col ++) {
            if (!this->square_is_empty(row, col)){
                Piece* piece_in_board = board[row][col];
                for (auto piece : pieces) {
                    if (piece == piece_in_board) {
                        board[row].erase(col);
                        piece->parent_kill_me();
                        break;
                    }
                }                
            }
        }
    }

}



std::vector<std::tuple<int, int>> Board::get_piece_instances_positions(int row, int col) {
    std::vector<std::tuple<int, int>> instances_positions;
    std::vector<Piece*> instances = board[row][col]->get_piece_instances();
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col ++) {
            if (!this->square_is_empty(row, col)){
                Piece* piece_in_board = board[row][col];
                for (auto piece_instance : instances) {
                    if (piece_in_board == piece_instance) {
                    std::cout << "instance found" << row << "," << col << "\n";
                        instances_positions.push_back(std::tuple<int, int>(row, col));
                        break;
                    }
                }                
            }
        }
    }
    return instances_positions;
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
    return this->selected_piece_position;
}

bool Board::is_any_piece_selected() {
    if (std::get<0>(this->selected_piece_position)!= -1 && std::get<1>(this->selected_piece_position) != -1){
        return true;
    }
    return false;
}

void Board::select_piece(int row, int col) {
    if(!this->square_is_empty(row,col)){
        this->selected_piece_position = std::make_tuple(row, col);
    }    
}

void Board::unselect_piece(int row, int col) {
    this->selected_piece_position = std::make_tuple(-1, -1);
}


void Board::print_board() {    
    std::cout << "\n";    
     for (int row = 0; row < 8; row++) {
         for (int col = 0; col < 8; col ++) {
             if (!this->square_is_empty(row, col)){
                //  std::cout << " " << board[row][col]->name << " ";                
             } else {
                //  std::cout << " - ";
             }
         }
        //  std::cout << "\n";
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
    
    // Se obtienen los posibles movimientos de la pieza seleccionada actualmente (de existir)    
    if (this->is_any_piece_selected()){
        std::tuple<int, int> selected_pos = this->get_selected_piece_position();
        // Se resalta la pieza seleccionada
        vector_board.push_back('h');
        vector_board.push_back(std::get<0>(selected_pos));
        vector_board.push_back(std::get<1>(selected_pos));
        vector_board.push_back('s');
        vector<tuple<int, int>> selected_piece_possible_movements = 
            get_piece_possible_movements(std::get<0>(selected_pos),std::get<1>(selected_pos));       
        for (const auto& position: selected_piece_possible_movements) {
            vector_board.push_back('h');
            vector_board.push_back(std::get<0>(position));
            vector_board.push_back(std::get<1>(position));
            // Si en el casillero hay una pieza, es un enemigo para comer
            if(!square_is_empty(std::get<0>(position),std::get<1>(position))){
                vector_board.push_back('e'); //(e)nemigo a comer
            }else{
                vector_board.push_back('m'); //(m)ovimiento posible
            }
        }
    }
    
    // Se recorren todas las piezas del tablero
    for (const auto& key_value_board: this->board) {
        for (const auto& key_value_row: key_value_board.second) {
            vector_board.push_back('p');      
            vector_board.push_back(key_value_board.first);
            vector_board.push_back(key_value_row.first);
            Piece * piece = key_value_row.second;
            vector_board.push_back((char)piece->name[0]);
            vector_board.push_back(piece->probability_fraction_den);
            //esta_pieza_esta_entrelazada_con_la_seleccionada
            vector_board.push_back(0);
            //esta_pieza_es_la_misma_que_seleccionada (split)
            vector_board.push_back(0);            
        }   
    }    
    return std::move(vector_board);
}


