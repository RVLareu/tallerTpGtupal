#ifndef __GAME_H__
#define __GAME_H__

#include "../common/common_protocol.h"

#include "board.h"
#include "blocking_queue.h"
#include "./client.h"
#include <vector>
#include <list>
#include <thread>
class Game {
    private:
        bool whites_turn;
        
        std::list<Client *>& clients;
        
        Protocol protocol;
        
    public:
        bool is_running;
        
        Board board;

        BlockingQueue& blocking_queue;

        Game(BlockingQueue& blocking_queue, std::list<Client *>& clients);

        void process_position(int row, int col);

        bool is_whites_turn();

        void change_turn();

        void process_events(BlockingQueue& blocking_queue);
        
        void print_game();

        std::vector<char> get_board();

};

#endif