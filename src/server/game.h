#include "board.h"

class Game {
    private:
        Board& board;

        bool whites_turn;

    public:

        Game(Board& board);

        void process_position(int row, int col);

        bool is_whites_turn();

        void change_turn();


        void print_game();


};
