#include <tuple>
#include <vector>

#ifndef PIECE_H
#define PIECE_H

class Piece {
    public:
        // 1 black, 0 white
        int color;

        int probability_fraction_den;

        int probability_fraction_num;

        Piece* parent;

        Piece* right_child;

        Piece* left_child;

        Piece* parent_left_merge;

        // Probabilidad recibidad de parent_left_merge
        int den_from_left_merge;
        int num_from_left_merge;

        Piece* parent_right_merge;

        // Probabilidad recibidad de parent_right_merge
        int den_from_right_merge;
        int num_from_right_merge;

        std::string name;           

        // Hojas del árbol
        std::vector<Piece*> leafs;

        virtual std::vector<Piece*> split() = 0;

        // devuelve true si tiene algun hijo
        bool has_childs();

        // invoca kill_child en el padre
        void parent_kill_me();
        
        // el padre mata al hijo y redistribuye su probabilidad
        void kill_child(Piece* piece, int prob_den, int prob_num);

        // recibe probabilidad, maneja fracciones
        void receive_probability(int probability_den, int probability_num);

        // crea un hijo merge de la pieza actual y la pasada por parámetro
        void create_merge_son(Piece* parent_left, Piece* parent_right);

        Piece(int color, int probability_fraction_den, int probability_fraction_num, std::string name);
                
        bool is_white();                    

        // todos los lugares a los que se puede mover una pieza en un tablero vacío
        virtual std::vector<std::tuple<int, int>> can_move(int origin_row, int origin_col) = 0;

        void get_piece_leafs(Piece* piece);

        //devuelve las instancias de la pieza
        std::vector<Piece*>  get_piece_instances();      

        // devuelve la raiz del árbol
        Piece* get_piece_root();

        // Devuelve el máximo común divisor entre dos enteros
        int gcd(int num_a, int num_b);

        bool exists();

        // pieza le indica al padre que existe (ahora la hija tiene probabilidad 1)
        std::vector<Piece*> parent_im_here();

        // elimina todo el arbol
        void delete_full_tree(Piece* node);

        // mergea pieza actual con la pasada por parámetro
        virtual Piece* merge(Piece* piece) = 0;
     
};

#endif

