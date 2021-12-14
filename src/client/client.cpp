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
extern std::string ASSETS_PATH;

Client::Client(char* host, char* port) : sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO),
                    window("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_RESIZABLE),
                    renderer(this->window, -1, SDL_RENDERER_ACCELERATED),
                    board(std::ref(this->renderer)),
                    winner('b'),
                    running(true),
                    is_merge(false) {
    board.create_spots();
    this->socket.connect(host, port);
}

int Client::receive_board_state_and_render() {
    std::vector<char> status;
    if (!this->status_queue.empty()) {
        renderer.Clear();
        status = this->status_queue.front();
        this->status_queue.pop();
    }
    if (status.size() > 0){
        if (status[0] == 'f'){
            this->winner = status[1];
            return 1;
        } else{
            this->board.render_from_vector(status);
            this->renderer.Present();
        }
    }
    return 0;
}


int Client::receive_client_input_and_send() {
    SDL2pp::Point mousePos;
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return 1;                  
                break;
            case SDL_MOUSEBUTTONDOWN: 
                mousePos.SetX(event.motion.x);
                mousePos.SetY(event.motion.y);
                if (event.button.button == SDL_BUTTON_LEFT) {
                    try {
                        is_merge = false;
                        this->selection_queue.push(board.mouse_position_to_square(mousePos));
                    } catch (std::range_error) {
                        std::cout << "Out of range click";
                    }
                } else if (event.button.button == SDL_BUTTON_RIGHT) {
                    is_merge = true;
                    this->selection_queue.push(board.mouse_position_to_square(mousePos));
                }
                break;
                
        }
    }
    return 0;
}


void Client::in_game_loop() {

    /*
        Send And Receive Queues
    */
    std::thread receive (&Client::receive_status,this);
    std::thread send (&Client::send_selection,this);


    /*
        In Game Music
    */
    
    SDL2pp::Wav wav(ASSETS_PATH + "assets/in_game_music.wav");
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
    
    renderer.Clear();
    while (this->running) {
        if (receive_client_input_and_send()) {
            this->running = false;
            break;
        }
        if (receive_board_state_and_render()) {
            this->running = false;
            break;
        }
        SDL_Delay(1000 * (1/60));
    }

    receive.join();
    send.join();

    dev.Pause(true);
}


int Client::run(){
    /*
        Menu
    */
    Menu menu(std::ref(renderer), std::ref(window));
    this->nickname = menu.show_menu();


    this->in_game_loop();

    EndScreen endScreen(std::ref(renderer), std::ref(window), this->winner, this->nickname);
    endScreen.show_end_screen();
    return 0;
}

void Client::receive_status() {
    std::vector<char> status;
    while (this->running) {
        if (status.size() > 0) {
            if (status[0] == 'f') {
                break;
            }
        }
        status = this->protocol.recv_board_status(this->socket);
        this->status_queue.push(status);
    }
}

void Client::send_selection() {
    while (this->running) {
        if (!this->selection_queue.empty()) {
            std::tuple<int, int> selection = this->selection_queue.front();
            this->selection_queue.pop();
            if (is_merge) { // right_click
                protocol.send_selection(socket, std::get<0>(selection), std::get<1>(selection), 'm');
            } else {
                protocol.send_selection(socket, std::get<0>(selection), std::get<1>(selection), 'c');
            }
        }
    }
}
