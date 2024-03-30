#include "update.h"

bool run_first_time = true;

void update_game_objects(GameObjects *game_objects, Textures *textures, GameControls *game_controls) {

    // Get delta_time factor converted to seconds to be used to update objects
    game_controls->delta_time = (SDL_GetTicks() - game_controls->last_frame_time) / 1000.0;
    // Store the milliseconds of the current frame to be used in the next one
    game_controls->last_frame_time = SDL_GetTicks();
    game_controls->float_main_count += game_controls->delta_time;
    game_controls->int_main_count = game_controls->float_main_count;
    printf("%d - %.6f\n", game_controls->int_main_count, game_controls->float_main_count);

    if(run_first_time){
        sandbox_init(game_objects, textures);
        run_first_time = false;
    }
    sandbox_move(game_objects, textures, game_controls);
}
