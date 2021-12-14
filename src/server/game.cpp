#include "./game.h"
#include "./blocking_queue.h"
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>

Game::Game(BlockingQueue& blocking_queue, std::list<Client *>& clients) : whites_turn(true),
                                                                            blocking_queue(blocking_queue),                                                                             
                                                                            clients(clients),
                                                                            is_running(true){}

void Game::process_position(int row, int col, char type) {
    // MERGE
    if ((this->board.selected_pieces_for_merge.size() == 2) and type == 'c') {
        if (this->board.merge_pieces(row, col)) {
            change_turn();
        }
        this->board.selected_pieces_for_merge.clear();
    }

    /*
        Hay una pieza seleccionada
    */
    else if (board.is_any_piece_selected() and type == 'c') {                        
        std::tuple<int, int> position_of_selected_piece = this->board.get_selected_piece_position();

        // El lugar seleccionado está vacio
        if (this->board.square_is_empty(row, col)) {
            // Había una pieza marcada para hacer split => se seleccionan los casilleros para hacer el split.
            std::tuple<int, int> marked_for_split_position = this->board.get_marked_for_split_position();
            std::tuple<int, int> null_tuple = std::make_tuple(-1, -1);
            if (marked_for_split_position != null_tuple){ 
                std::vector<tuple<int, int>> marked_for_split_piece_moves = this->board.get_piece_possible_movements(std::get<0>(marked_for_split_position), std::get<1>(marked_for_split_position));
                // Se revisa que la posicion seleccionada para hacer split sea un movimiento válido de la pieza
                if (std::find(marked_for_split_piece_moves.begin(), marked_for_split_piece_moves.end(), std::make_tuple(row, col)) == marked_for_split_piece_moves.end()){
                    return;
                }
                // Seleccion primer posicion para split
                if (this->board.first_split_position == null_tuple){
                    this->board.first_split_position = std::make_tuple(row, col);
                } else { // Seleccion segunda posicion para split
                    this->board.second_split_position = std::make_tuple(row, col);
                    this->board.split_piece(std::get<0>(marked_for_split_position),
                                            std::get<1>(marked_for_split_position),
                                            std::get<0>(this->board.first_split_position),
                                            std::get<1>(this->board.first_split_position),
                                            row,
                                            col );
                    this->board.unmark_for_split();
                    this->board.unselect_piece();
                    this->change_turn();                    
                    return;        
                }
            } else {
                // Muevo y deselecciono
                if (this->board.move_piece(std::get<0>(position_of_selected_piece), std::get<1>(position_of_selected_piece), row, col)) {
                    this->change_turn();            
                } 
            }
        } else {
            // El lugar seleccionado no está vacio

            // hay una pieza del mismo color que el del turno
            if ((this->board.is_piece_white(row, col) and is_whites_turn()) 
                || 
                (!this->board.is_piece_white(row, col) and !is_whites_turn())) {
                // Es la misma pieza -> se quiere hacer un split
                if ( row == std::get<0>(position_of_selected_piece) && col == std::get<1>(position_of_selected_piece)){
                    this->board.mark_for_split(row, col);                    
                } else{
                    // Es otra pieza propia
                    // Intenta moverse (por si la pieza propia esta en superposicion)
                    if (this->board.move_piece(std::get<0>(position_of_selected_piece), 
                                            std::get<1>(position_of_selected_piece), 
                                            row, 
                                            col)){
                        this->change_turn();
                        
                    } else{ // Si no, se cambia la pieza seleccionada
                        this->board.select_piece(row, col);
                    }
                    
                }
                return;
            //color opuesto al turno
            } else if ((this->board.is_piece_white(row, col) and !is_whites_turn()) 
                        || 
                       (!this->board.is_piece_white(row, col) and is_whites_turn())) {
                if (this->board.move_piece(std::get<0>(position_of_selected_piece), std::get<1>(position_of_selected_piece), row, col)) {
                    if (!this->board.dead_king){
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
            this->board.unmark_for_split();
            this->board.unselect_piece();
            this->board.selected_pieces_for_merge.clear();
        } else {
            //selecciono la pieza
            if ((this->board.is_piece_white(row, col) and is_whites_turn()) 
                || (!this->board.is_piece_white(row, col) and !is_whites_turn())) {
                if (type == 'm') {
                    this->board.unselect_piece();
                    this->board.select_piece_for_merge(row, col);

                } else {
                    this->board.select_piece(row, col);                
                }
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
        std::vector<char> event = blocking_queue.pop();        
        // Check de que el evento pertenezca al jugador del turno actual
        if ((event[3] == 'w') == this->is_whites_turn()){
            if (event[0] == 'c'){ // (c)lick
                this->process_position(event[1],event[2], 'c');
            } else if (event[0] == 'm') { // (m)erge
                this->process_position(event[1],event[2], 'm');       
            }
        }
        // Se envia el estado actualizado a los clientes
        for (auto &client : this->clients){
            // Ya finalizó el juego
            if (this->board.dead_king){
                client->send_finished_game(this->is_whites_turn());
                running = false;
            } else{
                client->send_board_status(this->board);
            }
        }            
    }
}
