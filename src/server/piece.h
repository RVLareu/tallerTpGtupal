#include <tuple>
#include <vector>

#ifndef PIECE_H
#define PIECE_H

class Piece {
    private:

    public:
        // 1 black, 0 white
        int color;

        bool alive;

        int probability_fraction_den;

        //int probability_fraction_den;

        Piece* parent;

        Piece* right_child;

        Piece* left_child;

        Piece* parent_left_merge;

        Piece* parent_right_merge;

        std::string name;           

        virtual std::vector<Piece*> split() = 0;

        bool has_childs();

        void parent_kill_me();
        
        void kill_child(Piece* piece);

        void receive_probability(int probability);

        void create_merge_son(Piece* parent_left, Piece* parent_right);

        void _print_tree(const std::string& prefix, Piece* node, bool isLeft);

        void print_tree(Piece* piece);

        Piece(int color, int probability_fraction, std::string name);
                
        bool is_white();                
        
        void set_prob(int probability_fraction);        

        virtual std::vector<std::tuple<int, int>> can_move(int origin_row, int origin_col) = 0;

        std::vector<Piece*> get_piece_leafs();



        Piece* get_piece_root();
     
};

#endif

