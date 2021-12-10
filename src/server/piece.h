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

        int probability_fraction_num;

        Piece* parent;

        Piece* right_child;

        Piece* left_child;

        Piece* parent_left_merge;

        Piece* parent_right_merge;

        std::string name;           

        std::vector<Piece*> leafs;

        virtual std::vector<Piece*> split() = 0;

        bool has_childs();

        void parent_kill_me();
        
        void kill_child(Piece* piece);

        void receive_probability(int probability_den, int probability_num);

        void create_merge_son(Piece* parent_left, Piece* parent_right);

        Piece(int color, int probability_fraction_den, int probability_fraction_num, std::string name);
                
        bool is_white();                
        
        void set_prob(int probability_fraction);        

        virtual std::vector<std::tuple<int, int>> can_move(int origin_row, int origin_col) = 0;

        void get_piece_leafs(Piece* piece);

        std::vector<Piece*>  get_piece_instances();      

        Piece* get_piece_root();

        int gcd(int num_a, int num_b);
     
};

#endif

