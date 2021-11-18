#include "board.h"
#include "piece.h"
#include "spot.h"

Board::Board(SDL2pp::Renderer& renderer) : renderer(renderer) {

}

void Board::add_piece(std::string path) {

}


/*
    Creates 64 Spots and places them in spots list
*/
void Board::create_spots() {
    std::list<Spot> spots;
    SDL2pp::Color color;
    for (int fila = 0; fila < 8; fila++) {
        for (int col = 0; col < 8; col++) {
            if ((fila + col) % 2 == 0) {
                color.SetRed(0);
                color.SetBlue(0);
                color.SetGreen(0);
            } else {
                color.SetRed(255);
                color.SetBlue(255);
                color.SetGreen(255);
            }
            Spot spot(renderer, SDL2pp::Rect(col * 100, fila * 100, 100 , 100), std::move(color));
            spots.push_back(std::move(spot));
        }
    }
    this->spots = std::move(spots);
}


void Board::create_pieces() {
    int size_spot = 100;

    Piece rook1(renderer, 0, 0, "assets/RookB.png");
    Piece rook2(renderer, 7 * size_spot, 0, "assets/RookB.png");
    Piece rook3(renderer, 0, 7 * size_spot, "assets/RookW.png");
    Piece rook4(renderer, 7 * size_spot, 7 * size_spot, "assets/RookW.png");
    this->pieces.push_back(std::move(rook1));
    this->pieces.push_back(std::move(rook2));
    this->pieces.push_back(std::move(rook3));
    this->pieces.push_back(std::move(rook4));

    for (int col = 0; col < 8; col ++) {
        Piece pawnB(renderer, size_spot * col, size_spot, "assets/PawnB.png");
        this->pieces.push_back(std::move(pawnB));
        Piece pawnW(renderer, size_spot * col, 6 * size_spot, "assets/PawnW.png");
        this->pieces.push_back(std::move(pawnW));
    }
    

}


bool Board::move_piece_if_selected(int pos_x, int pos_y) {
    int x = pos_x - this->clickOffset.GetX();
    int y = pos_y - this->clickOffset.GetY();
    std::list<Spot>::iterator it_spot;
    std::list<Piece>::iterator it_piece;
    for (it_piece = pieces.begin(); it_piece != pieces.end(); ++it_piece) {
        if (it_piece->selected) {
            it_piece->set_position(x, y);
            it_piece->selected = false;
            for(it_spot = spots.begin(); it_spot != spots.end(); ++it_spot) {
                if (it_spot->selected) {
                    it_spot->selected = false;
                    it_spot->setOriginalColor();
                    return true;
                }       
            }
        }

    }
    return false;
}

void Board::select_piece(SDL2pp::Point mousePos) {
    std::list<Spot>::iterator it_spot;
    std::list<Piece>::iterator it_piece;
    for (it_piece = pieces.begin(); it_piece != pieces.end(); ++it_piece) {
        if (it_piece->clicked(mousePos)) {
            it_piece->selected = true;
            clickOffset.SetX(mousePos.GetX() - it_piece->x_top);
            clickOffset.SetY(mousePos.GetY() - it_piece->y_top);
            for (it_spot = spots.begin(); it_spot != spots.end(); ++it_spot) {
                if (it_spot->clicked(mousePos)) {
                    it_spot->selected = true;
                    it_spot->set_color(SDL2pp::Color(87,35,100));
                    break;
                }
            }
        }
    }
}

void Board::render() {
    std::list<Spot>::iterator spot;
    for(spot = spots.begin(); spot != spots.end(); ++spot) {
        spot->render();
    }
 
    std::list<Piece>::iterator piece;
    for(piece = pieces.begin(); piece != pieces.end(); ++piece) {
        piece->copy();
    }

}

