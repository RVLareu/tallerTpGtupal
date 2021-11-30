#include "client.h"


#include "client.h"

#include <iostream>
#include <exception>
#include <SDL2pp/SDL2pp.hh>
#include <list>
#include <SDL.h>
#include <iostream>
#include <thread>


#include "client.h"
#include "spot.h"
#include "renderpiece.h"
#include "menu.h"
#include "endScreen.h"


Client::Client() : sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO),
                    window("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_RESIZABLE),
                    renderer(this->window, -1, SDL_RENDERER_ACCELERATED),
                    board(std::ref(this->renderer)),
                    winner('b') {
    board.create_spots();
    this->socket.connect("localhost", "7777");
}

void Client::receive_board_state_and_render(bool& running) {
        std::vector<char> status;
        while (running) {
            renderer.Clear();
            status = this->protocol.recv_board_status(this->socket);
            std::cout << status.size() << std::endl;
            if (status.size() > 0){
                if (status[0] == 'f'){
                    running = false;
                    this->winner = status[1];
                } else{
                    this->board.render_from_vector(status);
                    this->renderer.Present();
                }
            }
        }
}


void Client::receive_client_input_and_send(SDL_Event event, SDL2pp::Point mousePos, bool& running) {
    while(running) {
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;                    
                    break;
                case SDL_MOUSEMOTION:
                    mousePos.SetX(event.motion.x);
                    mousePos.SetY(event.motion.y);
                    break;
                case SDL_MOUSEBUTTONDOWN: 
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        protocol.send_selection(socket, std::get<0>(board.mouse_position_to_square(mousePos)), std::get<1>(board.mouse_position_to_square(mousePos)));
                    break;
                    }
            SDL_Delay(100);
            }
        }
    }
}


void Client::in_game_loop() {
    /*
        In Game Music
    */
    
    SDL2pp::Wav wav("assets/in_game_music.wav");
        uint8_t* wav_pos = wav.GetBuffer();
        SDL2pp::AudioDevice dev(SDL2pp::NullOpt, 0, wav.GetSpec(), [&wav, &wav_pos](Uint8* stream, int len) {
                    // Fill provided buffer with wave contents
                    Uint8* stream_pos = stream;
                    Uint8* stream_end = stream + len;

                    while (stream_pos < stream_end) {
                        Uint8* wav_end = wav.GetBuffer() + wav.GetLength();

                        size_t copylen = std::min(wav_end - wav_pos, stream_end - stream_pos);

                        std::copy(wav_pos, wav_pos + copylen, stream_pos);
                        stream_pos += copylen;
                        wav_pos += copylen;
                        if (wav_pos >= wav_end)
                            wav_pos = wav.GetBuffer();
                    }
                }
            );
        
    dev.Pause(false);

    SDL2pp::Point mousePos;
    SDL_Event event;
    bool running = true;
    std::thread client_input (&Client::receive_client_input_and_send,this, event, mousePos, std::ref(running));

    std::thread render_board (&Client::receive_board_state_and_render,this, std::ref(running));

    client_input.join();
    render_board.join();
    dev.Pause(true);
}


int Client::run(){

    Menu menu(std::ref(renderer), std::ref(window));

    this->nickname = menu.show_menu();
    
    this->in_game_loop();
  
    EndScreen endScreen(std::ref(renderer), std::ref(window), this->winner, this->nickname);
    endScreen.show_end_screen();
    return 0;
}

