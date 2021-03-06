#include "chessboard.h"
#include "renderpiece.h"
#include "spot.h"
#include <stdexcept>
extern std::string ASSETS_PATH;
extern int RES_HEIGHT;
extern int RES_WIDTH;

ChessBoard::ChessBoard(SDL2pp::Renderer& renderer) : renderer(renderer) {
    map_pieces['e'] = ASSETS_PATH + "assets/Empty.png";

    // Black pieces
    map_pieces['p'] = ASSETS_PATH + "assets/PawnB.png";
    map_pieces['r'] = ASSETS_PATH + "assets/RookB.png";
    map_pieces['b'] = ASSETS_PATH + "assets/BishopB.png";
    map_pieces['k'] = ASSETS_PATH + "assets/KingB.png";
    map_pieces['q'] = ASSETS_PATH + "assets/QueenB.png";
    map_pieces['n'] = ASSETS_PATH + "assets/KnightB.png";

    // white pieces
    map_pieces['P'] = ASSETS_PATH + "assets/PawnW.png";
    map_pieces['R'] = ASSETS_PATH + "assets/RookW.png";
    map_pieces['B'] = ASSETS_PATH + "assets/BishopW.png";
    map_pieces['K'] = ASSETS_PATH + "assets/KingW.png";
    map_pieces['Q'] = ASSETS_PATH + "assets/QueenW.png";
    map_pieces['N'] = ASSETS_PATH + "assets/KnightW.png";

}

/*
    Returns 0-63 spot
*/
 
std::tuple<int, int> ChessBoard::mouse_position_to_square(SDL2pp::Point mousePos) {
    int width = RES_WIDTH / 8;
    int height = RES_HEIGHT / 8;
    int mouse_x = mousePos.GetX();
    int mouse_y = mousePos.GetY();
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (mouse_x >= (col * width) and mouse_x <= ((col + 1)  * width)) {
                if ( mouse_y >= (row * height) and mouse_y <= ((row + 1)  * height)) {
                    return std::tuple<int, int>{row, col}; 
                }
            }
            
        }
    }
    throw std::range_error("NO CLICK IN BOARD");
}


/*
    Crea 64 casilleros y los pone en al lista de casilleros
*/
void ChessBoard::create_spots() {
    std::list<Spot> spots;
    SDL2pp::Color color;
    int width = RES_WIDTH / 8;
    int height = RES_HEIGHT / 8;

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
            Spot spot(renderer, SDL2pp::Rect(col * width, fila * height, width , height), std::move(color));
            spots.push_back(std::move(spot));
        }
    }
    this->spots = std::move(spots);
}





void ChessBoard::render_from_vector(std::vector<char> board) {
    pieces.clear();
    spots_painted.clear();
    int width = RES_WIDTH / 8;
    int height = RES_HEIGHT / 8;
    int ptr = 0;
    while (ptr < board.size())
    {        
        char type = board[ptr];
        // Piezas
        if (type == 'p'){
            int x = (board[ptr+1]) * height;
            int y = (board[ptr+2]) * width;
            char name = board[ptr+3];
            int probability_fraction_den = board[ptr+4];
            int probability_fraction_num = board[ptr+5];
            int is_entangled = board[ptr+6];
            int is_same_as_selected = board[ptr+7];
            pieces.emplace_back(renderer, x, y, map_pieces.at(name), probability_fraction_den, probability_fraction_num);            
            ptr += 8;        
        }
        // Resaltados
        else if (type == 'h'){
            int x = (board[ptr+2]) * width;
            int y = (board[ptr+1]) * height;
            char highlight_type = board[ptr+3];
            SDL2pp::Color color;
            if (highlight_type == 'm'){ // Highlight por (m)ovimiento posible
                color = SDL2pp::Color(30,80,100);                
            } else if (highlight_type == 'e'){ // Highlight por (e)nemigo para comer
                color = SDL2pp::Color(150,0,0);            
            } else if (highlight_type == 's'){ // Highlight por ser la pieza (s)eleccionada
                color = SDL2pp::Color(0,150,0);
            } else if (highlight_type == 'i') {// Highlight por ser (i)nstancia de la misma pieza
                color = SDL2pp::Color(0,30,255);
            } else if (highlight_type == 't') {// Highlight por ser pieza marcada para hacer spli(t)
                color = SDL2pp::Color(239,0,255);
            } else if (highlight_type == 'g') {// Highlight por ser pieza marcada para hacer mer(g)e
                color = SDL2pp::Color(153, 0, 255);
            }
            spots_painted.emplace_back(renderer,
                                        SDL2pp::Rect(x + width / 4, y + height / 4,  width/2 , height/2), 
                                        color);
            ptr += 4;
        }
    }
    render();
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

