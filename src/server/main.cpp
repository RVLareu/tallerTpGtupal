#include "board.h"
#include <iostream>






int main(int argc, char* argv[]) {

 
    Board board;
    // board.piece_can_move(0,0);
    // board.piece_can_move(0,1);
    // board.piece_can_move(0,2);
    // board.piece_can_move(0,3);
    // board.piece_can_move(0,4);
    // board.piece_can_move(0,5);
    // board.piece_can_move(1,5);
    board.move_piece(0,4,4,4);
    board.piece_can_move(4,4);
    board.print_board();

    return 0;
}
