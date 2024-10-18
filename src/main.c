#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "main.h"
#include "setup.h"
#include "sandbox.h"
#include "render.h"
#include "update.h"
#include "input_handler.h"
#include "collision_detection.h"

int main(int argc, char *args[]) {

    if (!initialize_sdl()) {
        return EXIT_FAILURE;
    }
    SDL_Window *window = create_window();
    if (!window) {
        SDL_Quit();
        return EXIT_FAILURE;
    }
    SDL_Renderer *renderer = create_renderer(window);
    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }
    Textures textures = create_textures(renderer);

    GameObjects game_objects;

    GameControls game_controls;
    game_controls.move_up = false;
    game_controls.move_down = false;
    game_controls.move_left = false;
    game_controls.move_right = false;
    game_controls.shoot_laser = false;
    game_controls.player_laser_count = 0;
    game_controls.enemy_laser_count = 0;
    game_controls.explosion_count = 0;
    game_controls.delta_time = 0;
    game_controls.last_frame_time = 0;
    game_controls.game_is_running = true;
    game_controls.float_main_count = 0;
    game_controls.int_main_count = 0;
    game_controls.flag = 0;

    while (game_controls.game_is_running) {
        process_input(&game_controls);
        update_game_objects(&game_objects, &textures, &game_controls);
        detect_collision(&game_objects, &game_controls);
        render(renderer, &game_objects);
    }

    // // Clean up
    // destroy_window(window, renderer);
    // return EXIT_SUCCESS;
}
