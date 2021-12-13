#include "piece.h"
#include <iostream>
#include <random>

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
                                        parent_right_merge(nullptr),
                                        den_from_left_merge(1),
                                        num_from_left_merge(1),
                                        den_from_right_merge(1),
                                        num_from_right_merge(1){

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
        std::cout << "Killing parent"<< std::endl;
        this->parent->kill_child(this, this->probability_fraction_den, this->probability_fraction_num);
    } if (parent_left_merge) {
        std::cout << "Killing parent left"<< std::endl;
        this->parent_left_merge->kill_child(this, this->den_from_left_merge, this->num_from_left_merge);
    } if (parent_right_merge) {
        std::cout << "Killing parent right"<< std::endl;
        this->parent_right_merge->kill_child(this, this->den_from_right_merge, this->num_from_right_merge);
    }
}

void Piece::create_merge_son(Piece* parent_left, Piece* parent_right) {
    parent_left->right_child; 
}

void Piece::kill_child(Piece* piece, int prob_den, int prob_num) {
    std::cout << "piece" << piece;
    std::cout << "right child" << this->right_child;
    if (piece == this->right_child) {
        std::cout << "Right child invoque me"<< std::endl;
        if (left_child) {
            std::cout << "Giving left"<< std::endl;
            left_child->receive_probability(prob_den,prob_num);
        } else if (parent) {
            std::cout << "sending to parent"<< std::endl;
            parent->kill_child(this, this->probability_fraction_den, this->probability_fraction_num);
        }
        //free right_child
        
        right_child = nullptr;
    }else if (piece == this->left_child) {
        std::cout << "Left child invoque me"<< std::endl;
        if (right_child) {
            std::cout << "Giving right"<< std::endl;
            right_child->receive_probability(prob_den, prob_num);
        } else if (parent) {

            std::cout << "sending to parent"<< std::endl;
            parent->kill_child(this, this->probability_fraction_den, this->probability_fraction_num);
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
    if (!this->parent && !this->parent_right_merge && !this->parent_left_merge) {
        return this;
    } else if (parent_left_merge) {
        return this->parent_left_merge->get_piece_root();
    } else if (parent_right_merge) {
        return this->parent_right_merge->get_piece_root();
    } else if (parent) {
        return this->parent->get_piece_root();
    }
}

bool Piece::exists() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,100);
    int random = dist(rng);
    // std::cout << "EL NUMERO RANDOM ES : " << random << std::endl;
    // std::cout << "LA PROB DE LA PIEZA ES : " << ((float)this->probability_fraction_num / (float)this->probability_fraction_den) * 100 << std::endl;
    // std::cout << "NUMERADOR : " << this->probability_fraction_num << std::endl;
    // std::cout << "DENOMINADOR : " << this->probability_fraction_den << std::endl;
    if (random <= ((float)this->probability_fraction_num / (float)this->probability_fraction_den) * 100){
        return true;
    }
    return false;
}



void Piece::delete_full_tree(Piece* node) {
    if (node == nullptr) {
        return;
    }
    if (node->right_child) {
        delete_full_tree(node->right_child);
    }
    if (node->left_child) {
        delete_full_tree(node->left_child);
    }
    delete node;
    node = nullptr;
}

std::vector<Piece*> Piece::parent_im_here() {
    std::vector<Piece*> dead_childs;
    this->get_piece_leafs(this->get_piece_root());
    for (auto piece : this->leafs) {
        if (piece != this) {
            
            dead_childs.push_back(piece);
        }
    }
    return dead_childs;

}



