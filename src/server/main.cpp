#include "board.h"
#include <iostream>






int main(int argc, char* argv[]) {

 
    Board board;
    board.create_board();
    board.print_board();

    board.piece_can_move(0,0);
    return 0;
}
