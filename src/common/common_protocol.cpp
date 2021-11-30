#include <string>
#include <iostream>
#include <arpa/inet.h>
#include <tuple>
#include <vector>

#include "common_protocol.h"
#include "common_socket.h"

#include "../server/board.h"

std::vector<char> Protocol::recv_board_status(Socket& socket){    
    //Primero se obtiene la longitud del mensaje
    uint16_t length;
    socket.recv((char *) &length, sizeof(length));
    length = ntohs(length);
    // y luego el vector
    std::vector<char> vector_board(length);
    socket.recv(vector_board.data(), length);
    return std::move(vector_board);
}

void Protocol::send_board_status(Socket& socket,
                            Board& board){
    std::vector<char> vector_board;    
    // Se obtienen los posibles movimientos de la pieza seleccionada actualmente (de existir)    
    if (board.is_any_piece_selected()){
        std::tuple<int, int> selected_pos = board.get_selected_piece_position();
        // Se resalta la pieza seleccionada
        vector_board.push_back('h'); //(h)ighlight
        vector_board.push_back(std::get<0>(selected_pos));
        vector_board.push_back(std::get<1>(selected_pos));
        vector_board.push_back('s');// Pieza (s)eleccionada
        vector<tuple<int, int>> selected_piece_possible_movements = 
            board.get_piece_possible_movements(std::get<0>(selected_pos),std::get<1>(selected_pos));       
        for (const auto& position: selected_piece_possible_movements) {
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
    
    // Se recorren todas las piezas del tablero
    for (const auto& key_value_board: board.board) {
        for (const auto& key_value_row: key_value_board.second) {
            vector_board.push_back('p');      
            vector_board.push_back(key_value_board.first);
            vector_board.push_back(key_value_row.first);
            Piece * piece = key_value_row.second;
            vector_board.push_back((char)piece->name[0]);
            vector_board.push_back(piece->probability_fraction);
            //esta_pieza_esta_entrelazada_con_la_seleccionada
            vector_board.push_back(0);
            //esta_pieza_es_la_misma_que_seleccionada (split)
            vector_board.push_back(0);            
        }   
    }

    std::cout << "SEND BOARD" << std::endl;
    //Envío de longitud del vector
    uint16_t length = htons(vector_board.size());    
    socket.send((char *) &length, sizeof(length));
    //Envio del vector
    socket.send(vector_board.data(), length);
    std::cout << vector_board.data() << std::endl; 
}

void Protocol::request(Socket& socket,
                        const std::string& command, 
                        const std::string& queue_name){
    char command_id = this->command_id_map[command];
    uint16_t queue_name_length = htons(queue_name.length());    
    socket.send(&command_id, sizeof(command_id));
    socket.send((char *) &queue_name_length , sizeof(queue_name_length));
    socket.send(queue_name.c_str(), queue_name.length());
}

void Protocol::request(Socket& socket,
                        const std::string& command, 
                        const std::string& queue_name, 
                        const std::string& message){
    this->request(socket,command,queue_name);
    // if (!message.empty()){
    //     this->send_message(socket, message);
    // }
}



