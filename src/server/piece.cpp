#include "piece.h"
#include <iostream>
#include <cstdlib>

Piece::Piece(int color, int probability_fraction_den, int probability_fraction_num, std::string name) :
                                        alive(true),                                                 
                                        color(color),
                                        probability_fraction_den(probability_fraction_den), 
                                        probability_fraction_num(probability_fraction_num),
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
    if (this->parent) {
        this->parent->kill_child(this);
    }
}

void Piece::create_merge_son(Piece* parent_left, Piece* parent_right) {
    parent_left->right_child; 
}

void Piece::kill_child(Piece* piece) {
    if (piece == right_child) {
        if (left_child) {
            left_child->receive_probability(right_child->probability_fraction_den,right_child->probability_fraction_num);
        } else if (parent) {
            parent->kill_child(this);
        }
        //free right_child
        right_child = nullptr;
    } else if (piece == left_child) {
        if (right_child) {
            right_child->receive_probability(left_child->probability_fraction_den, left_child->probability_fraction_num);
        } else if (parent) {
            parent->kill_child(this);
        }
        //free right_child
        left_child = nullptr;
    }
}


int Piece::gcd(int num_a, int num_b) {
    if (num_a == 0) {
        return num_b;
    }
    int min = num_b % num_a;
    return gcd(min, num_a);
}


void Piece::receive_probability(int probability_den, int probability_num) {
    int result_den = gcd(probability_den, this->probability_fraction_den);
    result_den = (probability_den * probability_fraction_den) / result_den;
    int result_num = probability_num * (result_den / probability_den) + this->probability_fraction_num * (result_den/this->probability_fraction_den);
    int common = gcd(result_den, result_num);
    result_den = result_den / common;
    result_num = result_num / common;
    if (!has_childs()) {
        this->probability_fraction_den = result_den;
        this->probability_fraction_num = result_num;
    } else if (right_child != nullptr and left_child == nullptr) {
        right_child->receive_probability(probability_den, probability_num);
    } else if (right_child == nullptr and left_child != nullptr) {
        left_child->receive_probability(probability_den, probability_num);
    } else {
        right_child->receive_probability(probability_den * 2, probability_num);
        left_child->receive_probability(probability_den * 2, probability_num);
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

bool Piece::exists() {
    int random = rand() % 100;
    std::cout << random << std::endl;
    if (random <= (this->probability_fraction_num / this->probability_fraction_den) * 100){
        return true;
    }
    return false;
}
