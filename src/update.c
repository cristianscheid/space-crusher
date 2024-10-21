#include "update.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include "sandbox.h"

void update_game_objects(GameObjects *game_objects, Textures *textures, GameControls *game_controls)
{

    // Get delta_time factor converted to seconds to be used to update objects
    game_controls->delta_time = (SDL_GetTicks() - game_controls->last_frame_time) / 1000.0;
    // Store the milliseconds of the current frame to be used in the next one
    game_controls->last_frame_time = SDL_GetTicks();
    game_controls->float_main_count += game_controls->delta_time;
    game_controls->int_main_count = game_controls->float_main_count;
    printf("%d - %.6f\n", game_controls->int_main_count, game_controls->float_main_count);

    sandbox_update(game_objects, textures, game_controls);
}
