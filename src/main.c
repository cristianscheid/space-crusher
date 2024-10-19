#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "main.h"

int main(int argc, char *args[])
{
    if (!initialize_sdl())
    {
        return EXIT_FAILURE;
    }

    SDL_Window *window = create_window();
    if (!window)
    {
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = create_renderer(window);
    if (!renderer)
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    Surfaces *surfaces = create_surfaces();
    if (!surfaces)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    Textures *textures = create_textures(renderer, surfaces);
    if (!textures)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    GameObjects game_objects;
    GameControls game_controls = {0};
    game_controls.game_is_running = true;

    while (game_controls.game_is_running)
    {
        process_input(&game_controls);
        update_game_objects(&game_objects, textures, &game_controls);
        detect_collision(&game_objects, &game_controls);
        render(renderer, &game_objects);
    }

    destroy_textures(textures);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
