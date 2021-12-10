#include "knight.h"
#include <iostream>
Knight::Knight(int color, int probability_fraction_den, int probability_fraction_num) : Piece(color, probability_fraction_den, probability_fraction_num, color == 1 ? "n" : "N") {

}

std::vector<std::tuple<int, int>> Knight::can_move(int origin_row, int origin_col) {
    std::vector<std::tuple<int, int>> possible_moves;
    const std::vector<int> col_offset = {-2, -1, 1, 2, 2, 1, -1, -2};
    const std::vector<int> row_offset = {1, 2, 2, 1, -1, -2, -2, -1};
    
    for (int off = 0; off < 8; off++) {
        int dst_row = origin_row + row_offset[off];
        int dst_col = origin_col + col_offset[off];

        if (dst_row >= 0 and dst_row < 8 and dst_col >= 0 and dst_col < 8) {
            possible_moves.emplace_back(dst_row, dst_col);
        }
    }

//print 
    std::cout << "Knight\n";
    std::vector<std::tuple<int, int>>::iterator it;
    for (int i = 0; i < 8; i ++) {
        for (int j = 0; j < 8; j++) {
            int found = 0;
            for (auto t: possible_moves) {
                
                if (std::get<0>(t) == i and std::get<1>(t) == j) {
                    std::cout << " x ";
                    found = 1;
                    break;
                }

            }
            if (found == 0) {
                std::cout << " . ";
            }
        }
        std::cout << "\n";
    }
    return std::move(possible_moves);
}


std::vector<Piece*> Knight::split() {
    this->right_child = new Knight(this->color, this->probability_fraction_den * 2, probability_fraction_num);
    this->left_child = new Knight(this->color, this->probability_fraction_den * 2, probability_fraction_num);

    right_child->parent = this;
    left_child->parent = this;

    std::vector<Piece*> childs;
    childs.push_back(right_child);
    childs[0]->parent = this;
    childs.push_back(left_child);
    childs[1]->parent = this;

    return childs; 
}
