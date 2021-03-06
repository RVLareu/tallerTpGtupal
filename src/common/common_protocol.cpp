#include <string>
#include <iostream>
#include <arpa/inet.h>
#include <tuple>
#include <vector>

#include "common_protocol.h"
#include "common_socket.h"

#include "../server/board.h"

#include "../server/blocking_queue.h"
#include <arpa/inet.h>

std::vector<char> Protocol::recv_board_status(Socket& socket){    
    //Primero se obtiene la longitud del mensaje
    uint16_t length;
    socket.recv((char *) &length, sizeof(length));
    // y luego el vector
    std::vector<char> vector_board(length);
    socket.recv(vector_board.data(), length);
    return vector_board;
}

void Protocol::send_finished_game(Socket& socket, bool white_wins){
    std::vector<char> vector_status;    
    vector_status.push_back('f'); //(f)inished
    if (white_wins){
        vector_status.push_back('w'); //(w)hites
    } else{
        vector_status.push_back('b'); //(b)lacks
    }
    //Envío de longitud del vector
    uint16_t length = vector_status.size();
    socket.send((char *) &length, sizeof(length));
    //Envio del vector
    socket.send(vector_status.data(), length);
}

void Protocol::send_board_status(Socket& socket,
                            Board& board){
    std::vector<char> vector_board;
    for (const auto merge_pos : board.selected_pieces_for_merge) {
        vector_board.push_back('h'); //(h)ighlight
        vector_board.push_back(std::get<0>(merge_pos));
        vector_board.push_back(std::get<1>(merge_pos));
        vector_board.push_back('g'); // Marcado para mer(g)ear
    }      
    // Se obtienen los posibles movimientos de la pieza seleccionada actualmente (de existir)    
    if (board.is_any_piece_selected()){
        std::tuple<int, int> selected_pos = board.get_selected_piece_position();
        // Se resalta la pieza seleccionada
        vector_board.push_back('h'); //(h)ighlight
        vector_board.push_back(std::get<0>(selected_pos));
        vector_board.push_back(std::get<1>(selected_pos));
        // Si la pieza seleccionada está marcada para hacer un split
        if (board.get_marked_for_split_position() == selected_pos){
            vector_board.push_back('t');// Pieza seleccionada para hacer un spli(t)
        } else {
            vector_board.push_back('s');// Pieza (s)eleccionada
        }
        // Se resaltan sus instancias
        vector<tuple<int, int>> piece_instances_positions = 
            board.get_piece_instances_positions(std::get<0>(selected_pos), 
                                                std::get<1>(selected_pos));
        for (const auto& position: piece_instances_positions) {
            if (position != selected_pos){// no se resalta a la pieza seleccionada
                vector_board.push_back('h'); //(h)ighlight
                vector_board.push_back(std::get<0>(position));
                vector_board.push_back(std::get<1>(position));
                vector_board.push_back('i'); // (i)nstancia de la misma pieza seleccionada
            }
        }
        // Envio de posibles movimientos:
        vector<tuple<int, int>> possible_movements = 
            board.get_piece_possible_movements(std::get<0>(selected_pos),
                                               std::get<1>(selected_pos));
        for (const auto& position: possible_movements) {
            vector_board.push_back('h'); //(h)ighlight
            vector_board.push_back(std::get<0>(position));
            vector_board.push_back(std::get<1>(position));
            // Si en el casillero hay una pieza, es un enemigo para comer
            if(!board.square_is_empty(std::get<0>(position),std::get<1>(position))){
                vector_board.push_back('e'); //(e)nemigo a comer
            }else{
                vector_board.push_back('m'); //(m)ovimiento posible
            }
        }
    } 
    // Si se está haciendo un merge, se muestran los posibles lugares en el se puede hacer.
    else if(board.selected_pieces_for_merge.size() >= 2){ 
        vector<tuple<int, int>> possible_movements = board.get_possible_merge_positions();
        for (const auto& position: possible_movements) {
            vector_board.push_back('h'); //(h)ighlight
            vector_board.push_back(std::get<0>(position));
            vector_board.push_back(std::get<1>(position));
            vector_board.push_back('m'); //(m)ovimiento posible
        }
    }
    // Se recorren todas las piezas del tablero
    for (const auto& key_value_board: board.board) {
        for (const auto& key_value_row: key_value_board.second) {
            vector_board.push_back('p');      
            vector_board.push_back(key_value_board.first);
            vector_board.push_back(key_value_row.first);
            Piece * piece = key_value_row.second;
            vector_board.push_back((char)piece->name[0]);
            vector_board.push_back(piece->probability_fraction_den);
            vector_board.push_back(piece->probability_fraction_num);
            //esta_pieza_esta_entrelazada_con_la_seleccionada
            vector_board.push_back(0);
            //esta_pieza_es_la_misma_que_seleccionada (split)
            vector_board.push_back(0);            
        }   
    }
    

    //Envío de longitud del vecto
    uint16_t length = vector_board.size();
    socket.send((char *) &length, sizeof(length));
    //Envio del vector
    socket.send(vector_board.data(), length);

}

void Protocol::recv_client_events(Socket& socket, 
                                  BlockingQueue& blocking_queue,
                                  int client_id){    
    std::vector<char> event;
    //Primero se obtiene el tipo de evento
    char event_type;
    socket.recv(&event_type, sizeof(event_type));

    if (event_type == 'c'){ // Click / selección
        uint16_t row;
        uint16_t col;

        socket.recv((char * ) &row, sizeof(row));
        row = ntohs(row);
        socket.recv((char * ) &col, sizeof(col));
        col = ntohs(col);

        event.push_back(event_type);
        event.push_back(row);
        event.push_back(col);        
                
    } else if (event_type == 'm') { //piece to merge
        uint16_t row;
        uint16_t col;

        socket.recv((char * ) &row, sizeof(row));
        row = ntohs(row);
        socket.recv((char * ) &col, sizeof(col));
        col = ntohs(col);

        event.push_back(event_type);
        event.push_back(row);
        event.push_back(col);   
    }
    // Se envia el color del jugador
    if (client_id == 0){
        event.push_back('w'); // (w)hite player
    } else {
        event.push_back('b'); // (b)lack player
    }
    blocking_queue.push(event);
    
}

void Protocol::send_selection(Socket& socket,
                            int row,
                            int col,
                            char selection) {
        //char selection = 'c';
        socket.send(&selection, sizeof(selection));

        uint16_t row_net = htons(row);
        uint16_t col_net = htons(col);
       
        socket.send((char*)&row_net, sizeof(row_net));
        socket.send((char*)&col_net, sizeof(col_net));   
}



