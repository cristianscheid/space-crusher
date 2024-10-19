#include "setup.h"
#include <stdio.h>
#include <SDL2/SDL_image.h>

bool initialize_sdl(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

SDL_Window *create_window(void)
{
    SDL_Window *window = SDL_CreateWindow(
        "Space Crusher",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0);
    if (!window)
    {
        fprintf(stderr, "Error creating SDL Window: %s\n", SDL_GetError());
    }
    return window;
}

SDL_Renderer *create_renderer(SDL_Window *window)
{
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        fprintf(stderr, "Error creating SDL Renderer: %s\n", SDL_GetError());
    }
    return renderer;
}

Surfaces *create_surfaces()
{
    Surfaces *surfaces = malloc(sizeof(Surfaces));
    if (!surfaces)
        return NULL;

    surfaces->background_sfc = IMG_Load("assets/background.png");
    surfaces->player_sfc = IMG_Load("assets/player.png");
    surfaces->enemy_sfcs[0] = IMG_Load("assets/enemy-blue-01.png");
    surfaces->enemy_sfcs[1] = IMG_Load("assets/enemy-blue-02.png");
    surfaces->enemy_sfcs[2] = IMG_Load("assets/enemy-brown-01.png");
    surfaces->enemy_sfcs[3] = IMG_Load("assets/enemy-brown-02.png");
    surfaces->enemy_sfcs[4] = IMG_Load("assets/enemy-green-01.png");
    surfaces->enemy_sfcs[5] = IMG_Load("assets/enemy-green-02.png");
    surfaces->enemy_sfcs[6] = IMG_Load("assets/enemy-orange-01.png");
    surfaces->enemy_sfcs[7] = IMG_Load("assets/enemy-orange-02.png");
    surfaces->enemy_sfcs[8] = IMG_Load("assets/enemy-purple-01.png");
    surfaces->enemy_sfcs[9] = IMG_Load("assets/enemy-purple-02.png");
    surfaces->enemy_sfcs[10] = IMG_Load("assets/enemy-red-01.png");
    surfaces->enemy_sfcs[11] = IMG_Load("assets/enemy-red-02.png");
    surfaces->enemy_sfcs[12] = IMG_Load("assets/enemy-yellow-01.png");
    surfaces->enemy_sfcs[13] = IMG_Load("assets/enemy-yellow-02.png");
    surfaces->asteroid_sfcs[0] = IMG_Load("assets/asteroid-01.png");
    surfaces->asteroid_sfcs[1] = IMG_Load("assets/asteroid-02.png");
    surfaces->player_laser_sfc = IMG_Load("assets/laser-01.png");
    surfaces->enemy_laser_sfc = IMG_Load("assets/laser-02.png");
    surfaces->explosion_sfc = IMG_Load("assets/explosion.png");

    return surfaces;
}

Textures *create_textures(SDL_Renderer *renderer, Surfaces *surfaces)
{
    Textures *textures = malloc(sizeof(Textures));
    if (!textures)
        return NULL;

    textures->background_tex = SDL_CreateTextureFromSurface(renderer, surfaces->background_sfc);
    textures->player_tex = SDL_CreateTextureFromSurface(renderer, surfaces->player_sfc);
    for (int i = 0; i < 14; i++)
    {
        textures->enemy_texs[i] = SDL_CreateTextureFromSurface(renderer, surfaces->enemy_sfcs[i]);
    }
    for (int i = 0; i < 2; i++)
    {
        textures->asteroid_texs[i] = SDL_CreateTextureFromSurface(renderer, surfaces->asteroid_sfcs[i]);
    }
    textures->player_laser_tex = SDL_CreateTextureFromSurface(renderer, surfaces->player_laser_sfc);
    textures->enemy_laser_tex = SDL_CreateTextureFromSurface(renderer, surfaces->enemy_laser_sfc);
    textures->explosion_tex = SDL_CreateTextureFromSurface(renderer, surfaces->explosion_sfc);

    free_surfaces(surfaces);

    return textures;
}

void free_surfaces(Surfaces *surfaces)
{
    SDL_FreeSurface(surfaces->background_sfc);
    SDL_FreeSurface(surfaces->player_sfc);
    for (int i = 0; i < 14; i++)
    {
        SDL_FreeSurface(surfaces->enemy_sfcs[i]);
    }
    for (int i = 0; i < 2; i++)
    {
        SDL_FreeSurface(surfaces->asteroid_sfcs[i]);
    }
    SDL_FreeSurface(surfaces->player_laser_sfc);
    SDL_FreeSurface(surfaces->enemy_laser_sfc);
    SDL_FreeSurface(surfaces->explosion_sfc);
    free(surfaces);
}

void destroy_textures(Textures *textures)
{
    SDL_DestroyTexture(textures->background_tex);
    SDL_DestroyTexture(textures->player_tex);
    for (int i = 0; i < 14; i++)
    {
        SDL_DestroyTexture(textures->enemy_texs[i]);
    }
    for (int i = 0; i < 2; i++)
    {
        SDL_DestroyTexture(textures->asteroid_texs[i]);
    }
    SDL_DestroyTexture(textures->player_laser_tex);
    SDL_DestroyTexture(textures->enemy_laser_tex);
    SDL_DestroyTexture(textures->explosion_tex);
    free(textures);
}
