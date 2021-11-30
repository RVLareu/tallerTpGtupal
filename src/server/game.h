#ifndef __GAME_H__
#define __GAME_H__

#include "board.h"

class Game {
    private:

        bool whites_turn;

    public:
        Board board;

        Game();

        void process_position(int row, int col);

        bool is_whites_turn();

        void change_turn();

        void print_game();

        std::vector<char> get_board();


};

#endif