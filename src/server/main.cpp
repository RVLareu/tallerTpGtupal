#include "game.h"
#include <iostream>
#include <functional>

#include <thread>

#include "../common/common_protocol.h"
#include "../common/common_socket.h"


int main(int argc, char* argv[]) {

    
    Board board;

    Game game(std::ref(board));
    
    /*game.process_position(6,1);
    game.process_position(5,1);

    game.print_game();

    std::cout<<game.get_board().data();

    */

    



    return 0;
}
