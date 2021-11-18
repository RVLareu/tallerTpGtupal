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


Menu::Menu(SDL2pp::Renderer& renderer, SDL2pp::Window& window) : renderer(renderer), window(window) {
    SDL2pp::SDLTTF ttf;
    SDL2pp::Font font("assets/SIXTY.TTF", 50);

    textures.emplace_back(renderer,
                     font.RenderText_Solid("MAIN MENU", SDL_Color{255, 255, 255, 255})
                     );
    textures.emplace_back(renderer,
                     font.RenderText_Solid("PLAY GAME", SDL_Color{255, 255, 255, 255})
                     );
    textures.emplace_back(renderer,
                     font.RenderText_Solid("SEE GAME", SDL_Color{255, 255, 255, 255})
                     );
    renderer.Copy(textures[0], SDL2pp::NullOpt, SDL2pp::Rect(0, 0, 100, 100));

}

void Menu::render() {
    int h = window.GetHeight() / 4;
    for (auto& texture: textures) {
			renderer.Copy(texture, SDL2pp::NullOpt, SDL2pp::Rect(window.GetWidth() / 3, h, texture.GetWidth(), texture.GetHeight()));
			h += texture.GetHeight() + 30;
	}
}


void Menu::play_background_music() {
    SDL2pp::Wav wav("assets/menu_song.wav");
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

int Menu::show_menu() {

    bool running = true;
    SDL_Event event;

    SDL2pp::Point mousePos;

    /*
    
        HAY ALGO CON EL TEMA DEL THREADING QUE SI LA LLAMO NO SUENA; PREGUNTAR
        TIrar un make clean para vaciar el buffer
    
    */
   //////////////////7
    SDL2pp::Wav wav("assets/menu_song.wav");
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

    SDL2pp::Wav w("assets/play_game_sound.wav");
    /////////////////////

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
                        if (event.motion.x > window.GetWidth() / 3 and event.motion.x < ((window.GetWidth() / 3) + 100)) {
                            if (event.motion.y > window.GetHeight() / 3 and event.motion.y < (window.GetHeight() / 3 + 50)) {



                                return 0;
                            }
                        }
                    }

            }
        }
        try {
            renderer.Clear();
            this->render();
            renderer.Present();
            SDL_Delay(100);

        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            return 1;
        }
    }
    return 0;
}
