#include "board.h"
#include <iostream>






int main(int argc, char* argv[]) {

 
    Board board;
    board.piece_can_move(0,0);
    board.piece_can_move(1,0);
    board.piece_can_move(2,0);
    board.piece_can_move(3,0);
    board.piece_can_move(4,0);
    board.piece_can_move(5,0);
    board.piece_can_move(5,1);
    board.move_piece(4,0,4,4);
    board.piece_can_move(4,4);
    board.print_board();

    return 0;
}
