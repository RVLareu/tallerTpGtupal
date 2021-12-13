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
    /*
        Hay una pieza seleccionada
    */
    if ((this->board.selected_pieces_for_merge.size() >= 2) and type == 'c') {
        std::cout << "Attemp to merge"<< std::endl;
        std::tuple<int, int> first_piece_to_merge = this->board.selected_pieces_for_merge.at(0);
        std::tuple<int, int> second_piece_to_merge = this->board.selected_pieces_for_merge.at(1);
        if (this->board.merge_pieces(get<0>(first_piece_to_merge),
                                 get<1>(first_piece_to_merge),
                                 get<0>(second_piece_to_merge),
                                 get<1>(second_piece_to_merge),
                                 row,
                                 col)) {

            change_turn();
        }
        this->board.selected_pieces_for_merge.clear();
    }

    else if (board.is_any_piece_selected() and type == 'c') {
                
        std::cout << "HAY PIEZA SELECCIONADA" << std::endl;
        std::tuple<int, int> position_of_selected_piece = this->board.get_selected_piece_position();

        // El lugar seleccionado está vacio
        if (this->board.square_is_empty(row, col)) {
            // Había una pieza marcada para hacer split => se seleccionan los casilleros para hace el split.
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
                    std::cout << std::get<0>(marked_for_split_position) << " " << std::get<1>(marked_for_split_position) << std::endl;
                    std::cout << std::get<0>(this->board.first_split_position) << " " << std::get<1>(this->board.first_split_position) << std::endl;
                    std::cout << std::get<0>(this->board.second_split_position) << " " << std::get<1>(this->board.second_split_position) << std::endl;
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
                    this->board.unselect_piece();
                    this->change_turn();            
                } 
            }
        } else {
            // El lugar seleccionado no está vacio

            // hay una pieza del mismo color que el del turno
            if ((this->board.is_piece_white(row, col) and is_whites_turn()) || (!this->board.is_piece_white(row, col) and !is_whites_turn())) {
                // Es la misma pieza -> se quiere hacer un split
                if ( row == std::get<0>(position_of_selected_piece) && col == std::get<1>(position_of_selected_piece)){
                    std::cout << "MARK FOR SPLIT" << std::endl;
                    this->board.mark_for_split(row, col);
                    std::cout << std::get<0>(this->board.get_marked_for_split_position()) << " " << std::get<1>(this->board.get_marked_for_split_position()) << std::endl;
                }
                // Es otra pieza propia
                this->board.unselect_piece();
                this->board.select_piece(row, col);                
                return;
            //color opuesto al turno
            } else if ((this->board.is_piece_white(row, col) and !is_whites_turn()) || (!this->board.is_piece_white(row, col) and is_whites_turn())) {
                Piece * enemy_piece = this->board.board[row][col];
                std::string enemy_type = enemy_piece->name;
                if (enemy_piece->exists()){
                    std::vector<Piece*> dead_childs = enemy_piece->parent_im_here();
                    this->board.remove_pieces(dead_childs);
                    std::cout << "EXISTE LA PIEZA" << std::endl;
                    //Muere el rey
                    if (enemy_type == "K" || enemy_type == "k"){
                        this->is_running = false;
                    }
                } else{
                    enemy_piece->parent_kill_me();
                    delete enemy_piece;
                }
                if (this->board.move_piece(std::get<0>(position_of_selected_piece), std::get<1>(position_of_selected_piece), row, col)) {
                    this->board.unselect_piece();   
                    if (this->is_running){
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
        std::cout << "PROCESANDO EVENTOS" << std::endl;
        std::vector<char> event = blocking_queue.pop();
        std::cout << "PROCESANDO EVENTO" << std::endl;
        if (event[0] == 'c'){ // (c)lick
            this->process_position(event[1],event[2], 'c');
            this->print_game();
        } else if (event[0] == 'm') { // (m)erge
            this->process_position(event[1],event[2], 'm');
            this->print_game();        
        }
        // Se envia el estado actualizado a los clientes
        for (auto &client : this->clients){
            // Ya finalizó el juego
            if (!this->is_running){
                client->send_finished_game(this->is_whites_turn());
                running = false;
            } else{
                std::cout << "ENVIANDO TABLERO AL CLIENTE" << std::endl;
                client->send_board_status(this->board);
            }
        }
    }
}

void Game::print_game() {
    this->board.print_board();
}

