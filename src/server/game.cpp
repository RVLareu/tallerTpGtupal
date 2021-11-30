#include "./game.h"
#include "./blocking_queue.h"
#include <vector>
#include <iostream>

Game::Game(BlockingQueue& blocking_queue, std::vector<Client *>& clients) : whites_turn(true),
                                                                            blocking_queue(blocking_queue),                                                                             
                                                                            clients(clients),
                                                                            is_running(true){}

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
                std::string enemy_type = this->board.board[row][col]->name;
                if (this->board.move_piece(std::get<0>(position_of_selected_piece), std::get<1>(position_of_selected_piece), row, col)) {
                    this->board.unselect_piece(row, col);
                    //Muere el rey
                    if (enemy_type == "K" || enemy_type == "k"){
                        this->is_running = false;
                    } else{
                        change_turn();
                    }
                
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


void Game::process_events(BlockingQueue& blocking_queue) {
    bool running = true;
    while(running){
        std::cout << "PROCESaNDo EVENTOSS" << std::endl;
        // std::vector<char> pepe2 = {'c',1,1};
        // this->blocking_queue.push(pepe2);
        std::vector<char> event = blocking_queue.pop();
        std::cout << "PROCESANDO EVENTO" << std::endl;
        if (event[0] == 'c'){
            this->process_position(event[1],event[2]);
            this->print_game();
        }
        // Se envia el estado actualizado a los clientes
        for (auto &client : this->clients){
            // Ya finalizó el juego
            if (!this->is_running){
                client->send_finished_game(this->is_whites_turn());
            } else{
                client->send_board_status(this->board);
            }

        }
        
    }
}

void Game::print_game() {
    this->board.print_board();
}