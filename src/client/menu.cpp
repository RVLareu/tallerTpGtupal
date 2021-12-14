#include <SDL_stdinc.h>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/SDLTTF.hh>
#include <SDL2pp/Font.hh>

#include <SDL2pp/AudioDevice.hh>
#include <SDL2pp/AudioSpec.hh>
#include <SDL2pp/Wav.hh>
#include <vector>

#include "menu.h"

extern std::string ASSETS_PATH;

Menu::Menu(SDL2pp::Renderer& renderer, SDL2pp::Window& window) : renderer(renderer), window(window) {
    SDL2pp::SDLTTF ttf;
    SDL2pp::Font font(ASSETS_PATH + "assets/SIXTY.TTF", 50);

    textures.emplace_back(renderer,
                     font.RenderText_Solid("MAIN MENU", SDL_Color{255, 255, 255, 255})
                     );
    textures.emplace_back(renderer,
                     font.RenderText_Solid("PLAY GAME", SDL_Color{255, 255, 255, 255})
                     );
    textures.emplace_back(renderer,
                     font.RenderText_Solid("SEE GAME", SDL_Color{255, 255, 255, 255})
                     );
}

void Menu::render() {
    renderer.SetDrawColor(SDL2pp::Color(0,0,0));
    int h = window.GetHeight() / 4;
    for (auto& texture: textures) {
			renderer.Copy(texture, SDL2pp::NullOpt, SDL2pp::Rect(window.GetWidth() / 3, h, texture.GetWidth(), texture.GetHeight()));
            renderer.SetDrawColor(SDL2pp::Color(255,255,255));
            renderer.DrawRect(SDL2pp::Rect(window.GetWidth() / 3, h, texture.GetWidth(), texture.GetHeight()));
    renderer.SetDrawColor(SDL2pp::Color(0,0,0));
			h += texture.GetHeight() + 30;
	}
    int w = 0;
    for (auto& letter: code_text_box) {
			renderer.Copy(letter, SDL2pp::NullOpt, SDL2pp::Rect(window.GetWidth() / 3 + w, (window.GetHeight()) * 5 / 6, letter.GetWidth(), letter.GetHeight()));
			w += letter.GetWidth();
	}
    w = 0;
    for (auto& letter: nickname_text_box) {
			renderer.Copy(letter, SDL2pp::NullOpt, SDL2pp::Rect(window.GetWidth() / 3 + w, (window.GetHeight()) * 8 / 9, letter.GetWidth(), letter.GetHeight()));
			w += letter.GetWidth();
	}
}


void Menu::play_background_music() {
    SDL2pp::Wav wav(ASSETS_PATH + "assets/menu_song.wav");
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
}

void Menu::code_text_box_bg() {
    renderer.SetDrawColor(SDL2pp::Color(100,80,37));
    renderer.FillRect(SDL2pp::Rect(window.GetWidth() / 3 , (window.GetHeight()) * 5 / 6, 230, 30));
}

void Menu::nickname_text_box_bg() {
    renderer.SetDrawColor(SDL2pp::Color(100,80,37));
    renderer.FillRect(SDL2pp::Rect(window.GetWidth() / 3 , (window.GetHeight()) * 8 / 9, 230, 30));
}

std::string Menu::show_menu() {

    bool running = true;
    SDL_Event event;

    SDL2pp::Point mousePos;

    /*
    
        HAY ALGO CON EL TEMA DEL THREADING QUE SI LA LLAMO NO SUENA; PREGUNTAR
        Tirar un make clean para vaciar el buffer
    
    */
   //////////////////
    SDL2pp::Wav wav(ASSETS_PATH + "assets/menu_song.wav");
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

    /////////////////////


    /////////////////////
    SDL2pp::Wav w(ASSETS_PATH + "assets/play_game_sound.wav");
    /////////////////////
    bool code_input = true;
    while (running) {
        
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
                        if (event.motion.x > window.GetWidth() / 3 and event.motion.x < ((window.GetWidth() / 3) + 300)) {
                            if (event.motion.y > window.GetHeight() / 3 and event.motion.y < (window.GetHeight() / 3 + 100)) {
                                // tocó play game
                                dev.Pause(true);
                                return std::move(nickname);
                            }
                        }
                    } else if (event.button.button == SDL_BUTTON_RIGHT) {
                        code_input = !code_input;
                    }
                    break;
                case SDL_KEYDOWN:
                    if (code_input) {
                        if (event.key.keysym.sym == SDLK_LEFT and code_text_box.size() > 0) {
                            code_text_box.pop_back();
                            code.pop_back();
                        }  
                    } else if (event.key.keysym.sym == SDLK_LEFT and nickname_text_box.size() > 0) {
                            nickname_text_box.pop_back();
                            nickname.pop_back();
                        } 
                    break;
                case SDL_TEXTINPUT: 
                    SDL2pp::SDLTTF ttf;
                    SDL2pp::Font font(ASSETS_PATH + "assets/SIXTY.TTF", 20);
                    if (code_input) {
                        code_text_box.emplace_back(renderer,
                            font.RenderText_Solid(event.text.text, SDL_Color{255, 255, 255, 255})
                        );
                        code.append(event.text.text);
                    } else {
                        nickname_text_box.emplace_back(renderer,
                            font.RenderText_Solid(event.text.text, SDL_Color{255, 255, 255, 255})
                        );
                        nickname.append(event.text.text);
                    }
                    break;
            }
        }
        try {

            renderer.Clear();
            this->code_text_box_bg();
            this->nickname_text_box_bg();
            this->render();
            renderer.Present();
            SDL_Delay(100);

        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
    return std::move(nickname);
}
