#include "render.h"

void render(SDL_Renderer *renderer, GameObjects *game_objects)
{
    // Clear the renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw background
    for (int i = 0; i < sizeof(game_objects->background) / sizeof(game_objects->background[0]); i++)
    {
        if (game_objects->background[i].is_visible)
        {
            SDL_RenderCopy(renderer, game_objects->background[i].tex, NULL, &game_objects->background[i].rect);
        }
    }

    // Draw player lasers
    for (int i = 0; i < sizeof(game_objects->player_lasers) / sizeof(game_objects->player_lasers[0]); i++)
    {
        if (game_objects->player_lasers[i].is_visible)
        {
            SDL_RenderCopy(renderer, game_objects->player_lasers[i].tex, NULL, &game_objects->player_lasers[i].rect);
        }
    }

    // Draw player
    SDL_RenderCopy(renderer, game_objects->player.tex, NULL, &game_objects->player.rect);

    // Draw enemy lasers
    for (int i = 0; i < sizeof(game_objects->enemy_lasers) / sizeof(game_objects->enemy_lasers[0]); i++)
    {
        if (game_objects->enemy_lasers[i].is_visible)
        {
            SDL_RenderCopy(renderer, game_objects->enemy_lasers[i].tex, NULL, &game_objects->enemy_lasers[i].rect);
        }
    }

    // Draw enemies
    for (int i = 0; i < sizeof(game_objects->enemies) / sizeof(game_objects->enemies[0]); i++)
    {
        if (game_objects->enemies[i].is_visible)
        {
            SDL_RenderCopy(renderer, game_objects->enemies[i].tex, NULL, &game_objects->enemies[i].rect);
        }
    }

    // Draw asteroids
    for (int i = 0; i < sizeof(game_objects->asteroids) / sizeof(game_objects->asteroids[0]); i++)
    {
        if (game_objects->asteroids[i].is_visible)
        {
            SDL_RenderCopy(renderer, game_objects->asteroids[i].tex, NULL, &game_objects->asteroids[i].rect);
        }
    }

    // Draw explosions
    for (int i = 0; i < sizeof(game_objects->explosions) / sizeof(game_objects->explosions[0]); i++)
    {
        if (game_objects->explosions[i].is_visible)
        {
            SDL_RenderCopy(renderer, game_objects->explosions[i].tex, NULL, &game_objects->explosions[i].rect);
        }
    }

    SDL_Rect rect;
    rect.w = 25;
    rect.h = 25;

    // Draw player health bar
    for (int i = 0; i < game_objects->player.health; i++)
    {
        rect.x = WINDOW_WIDTH - 30;
        rect.y = WINDOW_HEIGHT - 30 - (30 * i);
        SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
    }

    // Present the renderer
    SDL_RenderPresent(renderer);
}
