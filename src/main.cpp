#include <SDL2/SDL_mixer.h>

#include <iostream>

#include "Constants.h"
#include "Game.h"
#include "SDL_Plotter.h"

int main(int argc, char** argv) {
    // Initialize SDL_mixer for audio
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "SDL_mixer Error: " << Mix_GetError() << std::endl;
    }

    // Initialize the font
    initializeFont();

    // Create the plotter and game
    SDL_Plotter g(SCREEN_HEIGHT, SCREEN_WIDTH);
    SubwaySurferGame game(g);

    // Main game loop
    while (!g.getQuit()) {
        char key = '\0';
        if (g.kbhit()) {
            key = g.getKey();
        }

        game.update(key);
        game.render();
        g.update();
        g.Sleep(16);
    }

    // Cleanup
    Mix_CloseAudio();
    return 0;
}