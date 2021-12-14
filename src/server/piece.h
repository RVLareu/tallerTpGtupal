#include <tuple>
#include <vector>

#ifndef PIECE_H
#define PIECE_H

class Piece {
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

        int den_from_left_merge;
        int num_from_left_merge;

        Piece* parent_right_merge;

        int den_from_right_merge;
        int num_from_right_merge;

        std::string name;           

        std::vector<Piece*> leafs;

        virtual std::vector<Piece*> split() = 0;

        bool has_childs();

        void parent_kill_me();
        
        void kill_child(Piece* piece, int prob_den, int prob_num);

        void receive_probability(int probability_den, int probability_num);

        void create_merge_son(Piece* parent_left, Piece* parent_right);

        Piece(int color, int probability_fraction_den, int probability_fraction_num, std::string name);
                
        bool is_white();                    

        virtual std::vector<std::tuple<int, int>> can_move(int origin_row, int origin_col) = 0;

        void get_piece_leafs(Piece* piece);

        std::vector<Piece*>  get_piece_instances();      

        Piece* get_piece_root();

        // Devuelve el máximo común divisor entre dos enteros
        int gcd(int num_a, int num_b);

        bool exists();

        std::vector<Piece*> parent_im_here();

        void delete_full_tree(Piece* node);

        virtual Piece* merge(Piece* piece) = 0;
     
};

#endif

