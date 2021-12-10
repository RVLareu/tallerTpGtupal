#include "piece.h"
#include <iostream>

Piece::Piece(int color, int probability_fraction, std::string name) :
                                        alive(true),                                                 
                                        color(color),
                                        probability_fraction_den(probability_fraction), 
                                        name(name),
                                        parent(nullptr),
                                        right_child(nullptr),
                                        left_child(nullptr),
                                        parent_left_merge(nullptr),
                                        parent_right_merge(nullptr) {

}

bool Piece::is_white() {
    return this->color == 0;
}

void Piece::set_prob(int probability_fraction) {
    this->probability_fraction_den = probability_fraction;
}


bool Piece::has_childs() {
    return ((right_child != nullptr) || (left_child != nullptr));
}


void Piece::parent_kill_me() {
    this->parent->kill_child(this);
}

void Piece::create_merge_son(Piece* parent_left, Piece* parent_right) {
    parent_left->right_child; 
}

void Piece::kill_child(Piece* piece) {
    if (piece == right_child) {
        if (left_child) {
            left_child->receive_probability(right_child->probability_fraction_den);
        } else if (parent) {
            
        }
        //free right_child
        right_child = nullptr;
    } else if (piece == left_child) {
        if (right_child) {
            right_child->receive_probability(left_child->probability_fraction_den);
        }
        //free right_child
        left_child = nullptr;
    }
}



void Piece::_print_tree(const std::string& prefix, Piece* node, bool isLeft) {
    if( node != nullptr ) {   
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << 1 << '/' << node->probability_fraction_den << std::endl;

        // enter the next tree level - left and right branch
        _print_tree( prefix + (isLeft ? "│   " : "    "), node->left_child, true);
        _print_tree( prefix + (isLeft ? "│   " : "    "), node->right_child, false);
    }
}

void Piece::print_tree(Piece* node) {
    _print_tree("", node, false);    
}



void Piece::receive_probability(int probability) {
    if (!has_childs()) {
        this->probability_fraction_den += probability;
    } else if (right_child != nullptr and left_child == nullptr) {
        right_child->receive_probability(probability);
    } else if (right_child == nullptr and left_child != nullptr) {
        left_child->receive_probability(probability);
    } else {
        right_child->receive_probability(probability * 2);
        left_child->receive_probability(probability * 2);
    }
}

std::vector<Piece*>  Piece::get_piece_instances() {
    this->get_piece_leafs(this->get_piece_root());
    return this->leafs;
}

void Piece::get_piece_leafs(Piece* piece) {
    if(!piece->has_childs()) {
        leafs.push_back(piece);
    } if (piece->right_child != NULL) {
        get_piece_leafs(piece->right_child);
    } if (piece->left_child != NULL) {
        get_piece_leafs(piece->left_child);
    }

}

Piece* Piece::get_piece_root() {
    if (!this->parent) {
        return this;
    } else {
        this->parent->get_piece_root();
    }
}
