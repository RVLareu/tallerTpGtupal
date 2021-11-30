#include "game.h"
#include <iostream>

Game::Game() : whites_turn(true) {

}

void Game::process_position(int row, int col) {
    /*
        Hay una pieza seleccionada
    */
    if (board.is_any_piece_selected()) {        
        std::cout << "HAY PIEZA SELECCIONADA";
        std::tuple<int, int> position_of_selected_piece = this->board.get_selected_piece_position();

        // El lugar al que muevo la pieza está vacio
        if (this->board.square_is_empty(row, col)) {

            // Muevo y deselecciono
            if (this->board.move_piece(std::get<0>(position_of_selected_piece), std::get<1>(position_of_selected_piece), row, col)) {
                this->board.unselect_piece(row, col);
                change_turn();            
            } 
        } else {
            // El lugar al que muevo la pieza no está vacio

            // es del mismo color que el del turno
            if ((this->board.is_piece_white(row, col) and is_whites_turn()) || (!this->board.is_piece_white(row, col) and !is_whites_turn())) {
                this->board.unselect_piece(row, col);
                this->board.select_piece(row, col);                
                return;
            //color opuesto al turno
            } else if ((this->board.is_piece_white(row, col) and !is_whites_turn()) || (!this->board.is_piece_white(row, col) and is_whites_turn())) {
                if (this->board.move_piece(std::get<0>(position_of_selected_piece), std::get<1>(position_of_selected_piece), row, col)) {
                    this->board.unselect_piece(row, col);
                    change_turn();
                
                }
            }
        }
    /*
        No hay pieza seleccionada
    */
    } else {        
        if (this->board.square_is_empty(row, col)) {
            // nada
        } else {
            //selecciono la pieza
            if ((this->board.is_piece_white(row, col) and is_whites_turn()) || (!this->board.is_piece_white(row, col) and !is_whites_turn())) {
                this->board.select_piece(row, col);                
            }            
        }
    }    
}
    
bool Game::is_whites_turn() {
    return whites_turn;
}

void Game::change_turn() {
    whites_turn = !whites_turn;
}

void Game::print_game() {
    this->board.print_board();
}