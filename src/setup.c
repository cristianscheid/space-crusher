#include "setup.h"
#include <stdio.h>
#include <SDL2/SDL_image.h>

bool initialize_sdl(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

SDL_Window *create_window(void) {
    SDL_Window *window = SDL_CreateWindow(
            "Space Crusher",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            0
    );
    if (!window) {
        fprintf(stderr, "Error creating SDL Window: %s\n", SDL_GetError());
    }
    return window;
}

SDL_Renderer *create_renderer(SDL_Window *window) {
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL Renderer: %s\n", SDL_GetError());
    }
    return renderer;
}

Textures create_textures(SDL_Renderer *renderer) {

    SDL_Surface *background_sfc = IMG_Load("assets/background.png");
    SDL_Surface *player_sfc = IMG_Load("assets/player.png");
    SDL_Surface *enemy_sfcs[14];
    enemy_sfcs[0] = IMG_Load("assets/enemy-blue-01.png");
    enemy_sfcs[1] = IMG_Load("assets/enemy-blue-02.png");
    enemy_sfcs[2] = IMG_Load("assets/enemy-brown-01.png");
    enemy_sfcs[3] = IMG_Load("assets/enemy-brown-02.png");
    enemy_sfcs[4] = IMG_Load("assets/enemy-green-01.png");
    enemy_sfcs[5] = IMG_Load("assets/enemy-green-02.png");
    enemy_sfcs[6] = IMG_Load("assets/enemy-orange-01.png");
    enemy_sfcs[7] = IMG_Load("assets/enemy-orange-02.png");
    enemy_sfcs[8] = IMG_Load("assets/enemy-purple-01.png");
    enemy_sfcs[9] = IMG_Load("assets/enemy-purple-02.png");
    enemy_sfcs[10] = IMG_Load("assets/enemy-red-01.png");
    enemy_sfcs[11] = IMG_Load("assets/enemy-red-02.png");
    enemy_sfcs[12] = IMG_Load("assets/enemy-yellow-01.png");
    enemy_sfcs[13] = IMG_Load("assets/enemy-yellow-02.png");
    SDL_Surface *asteroid_sfcs[2];
    asteroid_sfcs[0] = IMG_Load("assets/asteroid-01.png");
    asteroid_sfcs[1] = IMG_Load("assets/asteroid-02.png");
    SDL_Surface *player_laser_sfc = IMG_Load("assets/laser-01.png");
    SDL_Surface *enemy_laser_sfc = IMG_Load("assets/laser-02.png");
    SDL_Surface *explosion_sfc = IMG_Load("assets/explosion.png");

    Textures textures = {0};

    textures.background_tex = SDL_CreateTextureFromSurface(renderer, background_sfc);
    SDL_FreeSurface(background_sfc);
    textures.player_tex = SDL_CreateTextureFromSurface(renderer, player_sfc);
    SDL_FreeSurface(player_sfc);
    for (int i = 0; i < sizeof(textures.enemy_texs) / sizeof(textures.enemy_texs[0]); i++) {
        textures.enemy_texs[i] = SDL_CreateTextureFromSurface(renderer, enemy_sfcs[i]);
        SDL_FreeSurface(enemy_sfcs[i]);
    }
    for (int i = 0; i < sizeof(textures.asteroid_texs) / sizeof(textures.asteroid_texs[0]); i++) {
        textures.asteroid_texs[i] = SDL_CreateTextureFromSurface(renderer, asteroid_sfcs[i]);
        SDL_FreeSurface(asteroid_sfcs[i]);
    }
    textures.player_laser_tex = SDL_CreateTextureFromSurface(renderer, player_laser_sfc);
    SDL_FreeSurface(player_laser_sfc);
    textures.enemy_laser_tex = SDL_CreateTextureFromSurface(renderer, enemy_laser_sfc);
    SDL_FreeSurface(enemy_laser_sfc);
    textures.explosion_tex = SDL_CreateTextureFromSurface(renderer, explosion_sfc);
    SDL_FreeSurface(explosion_sfc);

    return textures;
}
