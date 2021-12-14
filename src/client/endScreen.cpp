#include <SDL_stdinc.h>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/SDLTTF.hh>
#include <SDL2pp/Font.hh>

#include <SDL2pp/AudioDevice.hh>
#include <SDL2pp/AudioSpec.hh>
#include <SDL2pp/Wav.hh>
#include <vector>


#include "endScreen.h"

extern std::string ASSETS_PATH;

EndScreen::EndScreen(SDL2pp::Renderer& renderer, SDL2pp::Window& window, char winner, std::string nickname) : renderer(renderer), window(window), nickname(nickname) {
    SDL2pp::SDLTTF ttf;
    SDL2pp::Font font(ASSETS_PATH + "assets/Roboto-Regular.ttf", 50);

    textures.emplace_back(renderer,
                     font.RenderText_Solid("END OF GAME", SDL_Color{255, 255, 255, 255})
                     );
    textures.emplace_back(renderer,
                     font.RenderText_Solid("THE WINNER WAS", SDL_Color{255, 255, 255, 255})
                     );
    if (winner == 'b') {
        textures.emplace_back(renderer,
                         font.RenderText_Solid("BLACK", SDL_Color{255, 255, 255, 255})
                         );
    } else {
        textures.emplace_back(renderer,
                    font.RenderText_Solid("WHITE", SDL_Color{255, 255, 255, 255})
                    );    
    }
        textures.emplace_back(renderer,
                     font.RenderText_Solid("WELL PLAYED   " + nickname + " !!", SDL_Color{255, 255, 255, 255})
                     );

}

void EndScreen::render() {
    renderer.SetDrawColor(SDL2pp::Color(0,0,0));
    int h = window.GetHeight() / 4;
    for (auto& texture: textures) {
			renderer.Copy(texture, SDL2pp::NullOpt, SDL2pp::Rect(window.GetWidth() / 3, h, texture.GetWidth(), texture.GetHeight()));
            renderer.SetDrawColor(SDL2pp::Color(255,255,255));
            renderer.DrawRect(SDL2pp::Rect(window.GetWidth() / 3, h, texture.GetWidth(), texture.GetHeight()));
    renderer.SetDrawColor(SDL2pp::Color(0,0,0));
			h += texture.GetHeight() + 30;
	}
}


void EndScreen::play_background_music() {
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



int EndScreen::show_end_screen() {

    bool running = true;
    SDL_Event event;

    SDL2pp::Point mousePos;

    /*
    
        HAY ALGO CON EL TEMA DEL THREADING QUE SI LA LLAMO NO SUENA; PREGUNTAR
        Tirar un make clean para vaciar el buffer
    
    */
   //////////////////
    SDL2pp::Wav wav(ASSETS_PATH + "assets/end_game.wav");
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

    while (running) {
        
        while(SDL_PollEvent(&event)) {
        
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
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
