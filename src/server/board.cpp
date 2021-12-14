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

#include <vector>
#include <tuple>



int Board::sign(int n) {
    if (n > 0) {
        return 1;
    } else if (n < 0) {
        return -1;
    } else {
        return 0;
    }
}

Board::Board(): selected_piece_position(-1,-1), 
                marked_for_split_position(-1,-1), 
                first_split_position(-1,-1), 
                second_split_position(-1,-1){
    create_board();
}

Board::~Board(){
    for (const auto& key_value_board: this->board) {
        for (const auto& key_value_row: key_value_board.second) {
            Piece * piece = key_value_row.second;
            delete piece;
        }
    }
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
    this->split_piece(2, 2, 3, 2, 3, 3);
    this->split_piece(3, 2, 4, 4, 5, 5);
    this->split_piece(4, 4, 4, 5, 4, 6);
    this->split_piece(7, 4, 3, 1, 4, 1);

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

std::vector<tuple<int, int>> Board::get_possible_merge_positions(){
    // Posiciones de las piezas a mergear
    int first_piece_row = std::get<0>(this->selected_pieces_for_merge[0]);
    int first_piece_col = std::get<1>(this->selected_pieces_for_merge[0]);
    int second_piece_row = std::get<0>(this->selected_pieces_for_merge[1]);
    int second_piece_col = std::get<1>(this->selected_pieces_for_merge[1]);
    
    // Se quitan los casilleros en los que hay enemigos
    // (no se puede hacer merge en un casillero ocupado)
    // Movimientos posibles de la primer pieza
    std::vector<tuple<int, int>> first_piece_moves = this->get_piece_possible_movements(first_piece_row, first_piece_col, false);
    // Movimientos posibles de la segunda pieza
    std::vector<tuple<int, int>> second_piece_moves = this->get_piece_possible_movements(second_piece_row, second_piece_col, false);
    
    
    std::vector<tuple<int, int>> possible_merge_positions;

    // Se busca la interseccion de los movimientos posibles de ambas piezas
    std::sort(first_piece_moves.begin(), first_piece_moves.end());
    std::sort(second_piece_moves.begin(), second_piece_moves.end());
    std::set_intersection(first_piece_moves.begin(),first_piece_moves.end(),
                          second_piece_moves.begin(),second_piece_moves.end(),
                          back_inserter(possible_merge_positions));

    // Se agregan las posiciones de ambas piezas
    // (Se puede hacer el merge de ambas piezas en la posicion de cualquiera de las dos)
    possible_merge_positions.push_back(std::tuple<int, int>{first_piece_row, first_piece_col});
    possible_merge_positions.push_back(std::tuple<int, int>{second_piece_row, second_piece_col});
    return possible_merge_positions;
}

int Board::merge_pieces(int dst_row, int dst_col) { 
    // se pueden mover al destino ambas
    std::vector<tuple<int, int>> possible_merge_positions = this->get_possible_merge_positions();
    if (std::find(possible_merge_positions.begin(), possible_merge_positions.end(), tuple<int, int>{dst_row, dst_col}) != possible_merge_positions.end()) { 
        int first_piece_row = std::get<0>(this->selected_pieces_for_merge[0]);
        int first_piece_col = std::get<1>(this->selected_pieces_for_merge[0]);
        int second_piece_row = std::get<0>(this->selected_pieces_for_merge[1]);
        int second_piece_col = std::get<1>(this->selected_pieces_for_merge[1]);
        Piece* first_piece = board.at(first_piece_row).at(first_piece_col);
        board.at(first_piece_row).erase(first_piece_col);
        Piece* second_piece = board.at(second_piece_row).at(second_piece_col);
        board.at(second_piece_row).erase(second_piece_col);
        Piece* merged_piece = first_piece->merge(second_piece);
        board[dst_row][dst_col] = merged_piece;
        return 1;
    }
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

vector<tuple<int, int>> Board::filter_possible_movements(std::vector<std::tuple<int, int>> positions_available, 
                                                         int row, 
                                                         int col, 
                                                         Piece * piece, 
                                                         bool include_enemies_and_superpositions) {
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
            } else if (include_enemies_and_superpositions){
                //El casillero contiene una pieza enemiga 
                if ((this->board[dest_row][dest_col]->is_white() != piece->is_white())
                    // o una pieza propia en superposición 
                    // que no es una instancia de la pieza actualmente seleccionada
                    || ((this->board[dest_row][dest_col]->probability_fraction_den != 1)
                    && (piece->get_piece_instances() != this->board[dest_row][dest_col]->get_piece_instances()))
                ){
                    valid_square = true;
                }
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
                    if (!include_enemies_and_superpositions){
                        erased = true;
                        break;
                    } else{
                        // Si del mismo color, se permite solo si la pieza está en superposición, 
                        // no es una instancia de la pieza seleccionada actualmente
                        // y solo si se encuentra en la posición de destino.
                        if(this->board[current_row][current_col]->is_white() == piece->is_white()){
                            if (!(dest_row == current_row and dest_col == current_col) 
                                || (this->board[current_row][current_col]->probability_fraction_den == 1)
                                || (piece->get_piece_instances() == this->board[current_row][current_col]->get_piece_instances())
                            ){
                                erased = true;
                                break;
                            }
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



std::vector<std::tuple<int, int>> Board::get_piece_possible_movements(int row, int col, bool include_enemies_and_superpositions) {
    std::vector<std::tuple<int, int>> final_pos;
    if (!this->square_is_empty(row, col)) {         
        std::vector<std::tuple<int, int>> positions_available = board[row][col]->can_move(row, col);
        final_pos = filter_possible_movements(std::move(positions_available), row, col, board[row][col], include_enemies_and_superpositions);
        
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
                        delete piece;
                        break;
                    }
                }                
            }
        }
    }

}



std::vector<std::tuple<int, int>> Board::get_piece_instances_positions(int row, int col) {
    std::vector<std::tuple<int, int>> instances_positions;
    if (!this->square_is_empty(row, col)){
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

void Board::select_piece_for_merge(int row, int col) {
    if(!this->square_is_empty(row,col)){
        std::tuple<int, int> selected_position = std::make_tuple(row, col);
        Piece * selected_piece = this->board[row][col];
        // Si la probabilidad de la pieza seleccionada es 1, no puede mergearse.
        if (selected_piece->probability_fraction_den == 1){
            return;
        }
        // Nos fijamos que la pieza marcada para mergear no haya sido marcada antes
        std::vector<std::tuple<int, int>>::iterator pos = std::find(this->selected_pieces_for_merge.begin(), 
                                                            this->selected_pieces_for_merge.end(), 
                                                            selected_position);
        // Si ya fue marcada, se desmarca
        if (pos != this->selected_pieces_for_merge.end()){
            this->selected_pieces_for_merge.erase(pos);
        } else{
            // Si ya hay piezas marcadas, la nueva seleccion tiene que ser una instancia de ellas.
            if (this->selected_pieces_for_merge.size() > 0){
                Piece * marked_piece = this->board[std::get<0>(this->selected_pieces_for_merge[0])]
                                                  [std::get<1>(this->selected_pieces_for_merge[0])];
                std::vector<Piece *> marked_piece_instances = marked_piece->get_piece_instances();
                if (std::find(marked_piece_instances.begin(), 
                              marked_piece_instances.end(), 
                              selected_piece) == marked_piece_instances.end()){
                    return;
                }                
            }
            // Si ya hay dos piezas marcadas para mergear, las 
            // siguientes selecciones reemplazan a la segunda selección
            if (this->selected_pieces_for_merge.size() == 2){
                this->selected_pieces_for_merge[1] = selected_position;
            } else{
                this->selected_pieces_for_merge.push_back(selected_position);
            }
        }
    }    
}

void Board::unselect_piece() {
    this->selected_piece_position = std::make_tuple(-1, -1);
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

void Board::mark_for_split(int row, int col){
    this->marked_for_split_position = std::make_tuple(row, col);
    this->first_split_position = std::make_tuple(-1, -1);
    this->first_split_position = std::make_tuple(-1, -1);
}

void Board::unmark_for_split(){
    this->marked_for_split_position = std::make_tuple(-1, -1);
    this->first_split_position = std::make_tuple(-1, -1);
    this->first_split_position = std::make_tuple(-1, -1);
}

tuple<int, int> Board::get_marked_for_split_position(){
    return this->marked_for_split_position;
}   
