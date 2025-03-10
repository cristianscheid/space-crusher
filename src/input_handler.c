#include "input_handler.h"
#include <stdbool.h>

void process_input(SDL_Event *event, GameControls *game_controls)
{
    while (SDL_PollEvent(event))
    {
        switch (event->type)
        {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym)
            {
            case SDLK_UP:
                game_controls->move_up = true;
                break;
            case SDLK_DOWN:
                game_controls->move_down = true;
                break;
            case SDLK_LEFT:
                game_controls->move_left = true;
                break;
            case SDLK_RIGHT:
                game_controls->move_right = true;
                break;
            case SDLK_SPACE:
                game_controls->shoot_laser = true;
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event->key.keysym.sym)
            {
            case SDLK_UP:
                game_controls->move_up = false;
                break;
            case SDLK_DOWN:
                game_controls->move_down = false;
                break;
            case SDLK_LEFT:
                game_controls->move_left = false;
                break;
            case SDLK_RIGHT:
                game_controls->move_right = false;
                break;
            case SDLK_SPACE:
                game_controls->shoot_laser = false;
                break;
            default:
                break;
            }
            break;
        case SDL_QUIT:
            game_controls->game_is_running = false;
            break;
        default:
            break;
        }
    }
}
