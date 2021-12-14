
#include "piece.h"

#include <vector>
#include <tuple>
#include <map>

using namespace std;

#ifndef BOARD_H
#define BOARD_H


class Board;

typedef map<int, map<int,Piece*>> board_map;

class Board {
    private:        

        bool in_bounds(int col, int row);

        int sign(int n);
        
        tuple<int, int> selected_piece_position;


        // La posicion de la pieza que va a realizar un split
        tuple<int, int> marked_for_split_position;

    public:
        board_map board;                
        
        vector<tuple<int, int>> piece_moves;        
        
        // Las posiciones de los casilleros en los que se va a hacer el split
        tuple<int, int> first_split_position;
        tuple<int, int> second_split_position;

        Board();
        ~Board();

        void create_board();
        
        // Check if square has piece or not
        bool square_is_empty(int row, int col);

        vector<tuple<int, int>> get_piece_possible_movements(int row, int col, bool include_enemies_and_superpositions = true);
        
        int move_piece(int start_row, int start_col, int end_row, int end_col);

        void print_board();

        // Dado un vector con movimientos posibles de una pieza en un tablero vacío, 
        // devuelve los movimientos filtrados teniendo en cuenta los obstaculos que pueden haber en el tablero real.
        vector<tuple<int, int>> filter_possible_movements(vector<tuple<int, int>> positions_available, 
                                                          int row, 
                                                          int col, 
                                                          Piece * piece,
                                                          bool include_enemies_and_superpositions);

        tuple<int, int> get_selected_piece_position();

        void select_piece(int row, int col);

        void unselect_piece();

        bool is_piece_white(int row, int col);
        
        bool is_any_piece_selected();

        std::vector<char> get_vector_board();
        
        int split_piece(int piece_row,
                int piece_col,
                int first_splited_piece_row,
                int first_splited_piece_col,
                int second_splited_piece_row,
                int second_splited_piece_col);

        // Marca una posicion como seleccionada para hacer un split
        void mark_for_split(int row, int col);
        void unmark_for_split();
        tuple<int, int> get_marked_for_split_position();

        std::vector<std::tuple<int, int>> get_piece_instances_positions(int row, int col);  
        

        void remove_pieces(std::vector<Piece*>  pieces);

        // Intenta realizar un merge en la posicion indicada con las piezas marcadas para mergear
        int merge_pieces(int dst_row, int dst_col); 

        std::vector<std::tuple<int, int>> selected_pieces_for_merge;
        void select_piece_for_merge(int row, int col);

        // Devuelve los casilleros en los que con las piezas seleccionadas actualmente 
        // para hacer un merge se puede realizar el merge.
        std::vector<tuple<int, int>> get_possible_merge_positions();
};

#endif
