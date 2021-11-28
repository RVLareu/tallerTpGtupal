#include "game.h"
#include <iostream>
#include <functional>






int main(int argc, char* argv[]) {

    Board board;

    Game game(std::ref(board));

    game.process_position(6,1);
    game.process_position(5,1);


    game.print_game();

    game.process_position(1,2);
    game.process_position(2,2);

    game.print_game();
    /*
    Board board;
    board.piece_can_move(0,0);
    board.piece_can_move(0,1);
    board.piece_can_move(0,2);
    board.piece_can_move(0,3);
    board.piece_can_move(0,4);
    board.piece_can_move(0,5);
    board.piece_can_move(1,5);
    board.move_piece(0,4,4,4);
    board.piece_can_move(4,4);
    
    board.print_board();
    */
    return 0;
}
