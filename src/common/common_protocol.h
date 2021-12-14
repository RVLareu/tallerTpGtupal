#ifndef __COMMON_PROTOCOL_H__
#define __COMMON_PROTOCOL_H__

#include "common_socket.h"
#include "../server/board.h"
#include "../server/blocking_queue.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <tuple>


class Protocol{    
    public:
        // Para recibir un mensaje de un socket, siguiendo el
        // formato de 2 bytes con el largo del msg, y luego el msg.        
        std::vector<char> recv_board_status(Socket& socket);
        // Para enviar el estado del tablero a un socket.      
        void send_board_status(Socket& socket,
                               Board& board);
        // Para si el juego terminó a un socket.      
        void send_finished_game(Socket& socket, 
                                bool white_wins);
        
        void recv_client_events(Socket& socket, 
                                BlockingQueue& blocking_queue,
                                int client_id);

        void send_selection(Socket& socket,
                            int row,
                            int col,
                            char selection); 
};

#endif
