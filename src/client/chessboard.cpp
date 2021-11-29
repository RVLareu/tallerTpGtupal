#include "chessboard.h"
#include "renderpiece.h"
#include "spot.h"
#include <stdexcept>



ChessBoard::ChessBoard(SDL2pp::Renderer& renderer) : renderer(renderer) {
    map_pieces['e'] = "assets/Empty.png";

    // Black pieces
    map_pieces['p'] = "assets/PawnB.png";
    map_pieces['r'] = "assets/RookB.png";
    map_pieces['b'] = "assets/BishopB.png";
    map_pieces['k'] = "assets/KingB.png";
    map_pieces['q'] = "assets/QueenB.png";
    map_pieces['n'] = "assets/KnightB.png";

    // white pieces
    map_pieces['P'] = "assets/PawnW.png";
    map_pieces['R'] = "assets/RookW.png";
    map_pieces['B'] = "assets/BishopW.png";
    map_pieces['K'] = "assets/KingW.png";
    map_pieces['Q'] = "assets/QueenW.png";
    map_pieces['N'] = "assets/KnightW.png";

}

/*
    Returns 0-63 spot
*/

std::tuple<int, int> ChessBoard::mouse_position_to_square(SDL2pp::Point mousePos) {
    int size_spot = 100;
    int mouse_x = mousePos.GetX();
    int mouse_y = mousePos.GetY();
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (mouse_x >= (col * size_spot) and mouse_x <= ((col + 1)  * size_spot)) {
                if ( mouse_y >= (row * size_spot) and mouse_y <= ((row + 1)  * size_spot)) {
                    return std::tuple<int, int>{row, col}; 
                }
            }
            
        }
    }
    throw std::range_error("NO CLICK IN BOARD");
}


/*
    Creates 64 Spots and places them in spots list
*/
void ChessBoard::create_spots() {
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





void ChessBoard::render_from_vector(std::vector<char> board) {
    pieces.clear();
    spots_painted.clear();
    int size_spot = 100;
    int ptr = 0;
    while (ptr < board.size())
    {        
        char type = board[ptr];
        // Piezas
        if (type == 'p'){
            int x = (board[ptr+1]) * size_spot;
            int y = (board[ptr+2]) * size_spot;
            char name = board[ptr+3];
            int probability_fraction = board[ptr+4];
            int is_entangled = board[ptr+5];
            int is_same_as_selected = board[ptr+6];
            pieces.emplace_back(renderer, x, y, map_pieces.at(name), probability_fraction);            
            ptr += 7;        
        }
        // Resaltados
        else if (type == 'h'){
            int x = (board[ptr+1]) * size_spot;
            int y = (board[ptr+2]) * size_spot;
            char highlight_type = board[ptr+3];
            SDL2pp::Color color;
            std::cout << "type: " << type << std::endl;
            if (highlight_type == 'm'){ // Highlight por (m)ovimientos posibles
                color = SDL2pp::Color(30,80,100);                
            } else if (highlight_type == 's'){ // Highlight por ser la pieza (s)eleccionada
                color = SDL2pp::Color(0,80,0);
            }
            
            spots_painted.emplace_back(renderer,
                                        SDL2pp::Rect(y + size_spot / 4, x + size_spot / 4, size_spot/2 , size_spot/2), 
                                        color);
            ptr += 4;
        }
    }
    
    // for (int i = 0; i < board.size(); i += 5) {
    //     if (board[i] != 0) {
    //         int x = (board[i+2]) * size_spot;
    //         int y = (board[i+3]) * size_spot;
    //         int probability_fraction = board[i+1];
    //         pieces.emplace_back(renderer, x, y, map_pieces.at(board[i]), probability_fraction);
    //     }
    //     if (board[i+4] == 1) {
    //         spots_painted.emplace_back(renderer,SDL2pp::Rect(((board[i+3]) * size_spot) + size_spot / 4, (board[i+2] * size_spot) + size_spot / 4, size_spot/2 , size_spot/2), SDL2pp::Color(30,80,100));
    //     }
        
    // }
    render();
}


bool ChessBoard::move_piece_if_selected(int pos_x, int pos_y) {
    int x = pos_x - this->clickOffset.GetX();
    int y = pos_y - this->clickOffset.GetY();
    std::list<Spot>::iterator it_spot;
    std::list<RenderPiece>::iterator it_piece;
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

void ChessBoard::select_piece(SDL2pp::Point mousePos) {
    std::list<Spot>::iterator it_spot;
    std::list<RenderPiece>::iterator it_piece;
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

void ChessBoard::render() {
    
    std::list<Spot>::iterator spot;
    for(spot = spots.begin(); spot != spots.end(); ++spot) {
        spot->render();
    }

    std::list<Spot>::iterator spot_p;
    for(spot_p = spots_painted.begin(); spot_p != spots_painted.end(); ++spot_p) {
        spot_p->render();
    }
 
    std::list<RenderPiece>::iterator piece;
    for(piece = pieces.begin(); piece != pieces.end(); ++piece) {
        piece->copy();
    }
}

