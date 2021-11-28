#include "game.h"
#include <iostream>

Game::Game(Board& board) : board(board), whites_turn(true) {

}

void Game::process_position(int row, int col) {
    if (board.is_any_piece_selected()) {
        std::tuple<int, int> position_of_selected_piece = this->board.get_selected_piece_position();

        // El lugar al que la mueve está vacio
        if (this->board.square_is_empty(row, col)) {
            // Muevo y deselecciono 

            this->board.unselect_piece(std::get<0>(position_of_selected_piece), std::get<1>(position_of_selected_piece));
            this->board.move_piece(std::get<0>(position_of_selected_piece), std::get<1>(position_of_selected_piece), row, col);
            change_turn();
        } else {
            // Hay una pieza

            // es del mismo color que el del turno
            if ((this->board.is_piece_white(row, col) and is_whites_turn()) || (!this->board.is_piece_white(row, col) and !is_whites_turn())) {
                return;
            
            
            //color opuesto al turno
            } else if ((this->board.is_piece_white(row, col) and !is_whites_turn()) || (!this->board.is_piece_white(row, col) and is_whites_turn())) {
                this->board.move_piece(std::get<0>(position_of_selected_piece), std::get<1>(position_of_selected_piece), row, col);
                this->board.unselect_piece(std::get<0>(position_of_selected_piece), std::get<1>(position_of_selected_piece));
                change_turn();
            }
        }


    } else {
        if (this->board.square_is_empty(row, col)) {
            // nada
        } else {
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