#ifndef __COMMON_PROTOCOL_H__
#define __COMMON_PROTOCOL_H__

#include "common_socket.h"
#include "../server/board.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <tuple>


class Protocol{    
    private:
        //Traduce un comando a su char identificador        
        std::unordered_map<std::string,char> command_id_map = {
            {"define",'d'},
            {"push",'u'},
            {"pop",'o'},
        };

    public:
        // Para recibir un mensaje de un socket, siguiendo el
        // formato de 2 bytes con el largo del msg, y luego el msg.        
        std::vector<char> recv_board_status(Socket& socket);
        // Para enviar el estado del tablero a un socket.      
        void send_board_status(Socket& socket,
                               Board& board);
        // Envía un comando al servidor
        void request(Socket& socket,
                    const std::string& command, 
                    const std::string& queue_name);
        // Envía un comando con mensaje al servidor
        void request(Socket& socket,
                    const std::string& command, 
                    const std::string& queue_name, 
                    const std::string& message); 
};

#endif
