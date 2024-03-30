#include "sandbox.h"
#include <stdlib.h>
#include <SDL2/SDL.h>

bool first_call = true;

void sandbox_init(GameObjects *go, Textures *t) {
    // Background
    int background_width, background_height;
    SDL_QueryTexture(t->background_tex, NULL, NULL, &background_width, &background_height);
    go->background[0].tex = go->background[1].tex = t->background_tex;
    go->background[0].x = go->background[1].x = 0;
    go->background[0].y = WINDOW_HEIGHT - background_height;
    go->background[1].y = -background_height;
    go->background[0].rect.w = go->background[1].rect.w = background_width;
    go->background[0].rect.h = go->background[1].rect.h = background_height;
    go->background[0].vel_y = go->background[1].vel_y = 700;
    go->background[0].is_visible = true;
    go->background[1].is_visible = false;

    // Player
    go->player.tex = t->player_tex;
    SDL_QueryTexture(go->player.tex, NULL, NULL, &go->player.rect.w, &go->player.rect.h);
    go->player.x = (WINDOW_WIDTH / 2) - (go->player.rect.w / 2);
    go->player.y = 500;
    go->player.vel_x = 300;
    go->player.vel_y = 300;
    go->player.health = 5;

    // Enemies
    for (int i = 0; i < sizeof(go->enemies) / sizeof(go->enemies[0]); i++) {
        // Generate random index (j) to choose random sprite
        int j = rand() % (sizeof(t->enemy_texs) / sizeof(t->enemy_texs[0]));
        go->enemies[i].tex = t->enemy_texs[j];
        SDL_QueryTexture(go->enemies[i].tex, NULL, NULL, &go->enemies[i].rect.w, &go->enemies[i].rect.h);
        go->enemies[i].x = i * 100;
        go->enemies[i].y = 150;
        go->enemies[i].is_visible = false;
    }

    // Asteroids
    for (int i = 0; i < sizeof(go->asteroids) / sizeof(go->asteroids[0]); i++) {
        // Generate random index (j) to choose random sprite
        int j = rand() % ((sizeof(t->asteroid_texs) / sizeof(t->asteroid_texs[0])));
        go->asteroids[i].tex = t->asteroid_texs[j];
        SDL_QueryTexture(go->asteroids[i].tex, NULL, NULL, &go->asteroids[i].rect.w, &go->asteroids[i].rect.h);
        go->asteroids[i].x = i * 100;
        go->asteroids[i].y = 0;
        go->asteroids[i].is_visible = false;
    }

    // Player laser
    int player_laser_width, player_laser_height;
    SDL_QueryTexture(t->player_laser_tex, NULL, NULL, &player_laser_width, &player_laser_height);
    for (int i = 0; i < sizeof(go->player_lasers) / sizeof(go->player_lasers[0]); i++) {
        go->player_lasers[i].tex = t->player_laser_tex;
        go->player_lasers[i].rect.w = player_laser_width;
        go->player_lasers[i].rect.h = player_laser_height;
        go->player_lasers[i].vel_y = 800;
        go->player_lasers[i].is_visible = false;
    }

    // Enemy laser
    int enemy_laser_width, enemy_laser_height;
    SDL_QueryTexture(t->enemy_laser_tex, NULL, NULL, &enemy_laser_width, &enemy_laser_height);
    for (int i = 0; i < sizeof(go->enemy_lasers) / sizeof(go->enemy_lasers[0]); i++) {
        go->enemy_lasers[i].tex = t->enemy_laser_tex;
        go->enemy_lasers[i].rect.w = enemy_laser_width;
        go->enemy_lasers[i].rect.h = enemy_laser_height;
        go->enemy_lasers[i].vel_y = 100;
        go->enemy_lasers[i].is_visible = false;
    }

    // Explosion
    int explosion_img_width, explosion_img_height;
    SDL_QueryTexture(t->explosion_tex, NULL, NULL, &explosion_img_width, &explosion_img_height);
    for (int i = 0; i < sizeof(go->explosions) / sizeof(go->explosions[0]); i++) {
        go->explosions[i].tex = t->explosion_tex;
        go->explosions[i].rect.w = explosion_img_width / 1.5;
        go->explosions[i].rect.h = explosion_img_height / 1.5;
        go->explosions[i].is_visible = false;
    }
}

void sandbox_update(GameObjects *go, Textures *t, GameControls *gc) {

    if (first_call) {
        sandbox_init(go, t);
        first_call = false;
    }

    // Move Background
    for (int i = 0; i < sizeof(go->background) / sizeof(go->background[0]); i++) {
        bool j = !i;
        if (go->background[i].is_visible && go->background[i].y < WINDOW_HEIGHT) {
            go->background[i].y += go->background[i].vel_y * gc->delta_time;
            // Set SDL_Rect coordinates
            go->background[i].rect.x = go->background[i].x;
            go->background[i].rect.y = go->background[i].y;
            if (go->background[i].y > 0) {
                go->background[j].is_visible = true;
            }
        } else {
            go->background[i].is_visible = false;
            go->background[i].y = -go->background[i].rect.h;
        }
    }

    // Move player
    if (gc->move_up && !(gc->move_down) && go->player.y > 0) {
        go->player.y -= go->player.vel_y * gc->delta_time;
    }
    if (gc->move_down && !(gc->move_up) && go->player.y < WINDOW_HEIGHT - go->player.rect.h) {
        go->player.y += go->player.vel_y * gc->delta_time;
    }
    if (gc->move_left && !(gc->move_right) && go->player.x > 0) {
        go->player.x -= go->player.vel_x * gc->delta_time;
    }
    if (gc->move_right && !(gc->move_left) && go->player.x < WINDOW_WIDTH - go->player.rect.w) {
        go->player.x += go->player.vel_x * gc->delta_time;
    }
    // Set SDL_Rect coordinates
    go->player.rect.x = go->player.x;
    go->player.rect.y = go->player.y;

    // Move enemies
    for (int i = 0; i < sizeof(go->enemies) / sizeof(go->enemies[0]); i++) {
        go->enemies[i].y += go->enemies[i].vel_y * gc->delta_time;
        if (go->enemies[i].y >= 0 - go->enemies[i].rect.h && go->enemies[i].y < WINDOW_HEIGHT) {
            go->enemies[i].is_visible = true;
            // Set SDL_Rect coordinates
            go->enemies[i].rect.x = go->enemies[i].x;
            go->enemies[i].rect.y = go->enemies[i].y;
        } else {
            go->enemies[i].is_visible = false;
        }
    }

    // Move asteroids
    for (int i = 0; i < sizeof(go->asteroids) / sizeof(go->asteroids[0]); i++) {
        go->asteroids[i].y += go->asteroids[i].vel_y * gc->delta_time;
        if (go->asteroids[i].y >= 0 - go->asteroids[i].rect.h && go->asteroids[i].y < WINDOW_HEIGHT) {
            go->asteroids[i].is_visible = true;
            // Set SDL_Rect coordinates
            go->asteroids[i].rect.x = go->asteroids[i].x;
            go->asteroids[i].rect.y = go->asteroids[i].y;
        } else {
            go->asteroids[i].is_visible = false;
        }
    }

    // Start player laser (if space was pressed)
    if (gc->shoot_laser) {
        go->player_lasers[gc->player_laser_count].x = go->player.x + (go->player.rect.w / 2) - (go->player_lasers[gc->player_laser_count].rect.w / 2);
        go->player_lasers[gc->player_laser_count].y = go->player.y;
        go->player_lasers[gc->player_laser_count].is_visible = true;
        if (gc->player_laser_count < (sizeof(go->player_lasers) / sizeof(go->player_lasers[0])) - 1) {
            gc->player_laser_count++;
        } else {
            gc->player_laser_count = 0;
        }
        gc->shoot_laser = false;
    }

    // Move player lasers
    for (int i = 0; i < sizeof(go->player_lasers) / sizeof(go->player_lasers[0]); i++) {
        if (go->player_lasers[i].is_visible) {
            if (go->player_lasers[i].y > 0 - go->player_lasers[i].rect.h && go->player_lasers[i].y < WINDOW_HEIGHT) {
                go->player_lasers[i].y -= go->player_lasers[i].vel_y * gc->delta_time;
                // Set SDL_Rect coordinates
                go->player_lasers[i].rect.x = go->player_lasers[i].x;
                go->player_lasers[i].rect.y = go->player_lasers[i].y;
            } else {
                go->player_lasers[i].is_visible = false;
            }
        }
    }
// --------------------------------- T E S T I N G --------------------------------- //
    // Move enemy lasers
    for (int i = 0; i < sizeof(go->enemies) / sizeof(go->enemies[0]); i++) {
        if (gc->int_main_count == 1 + i && gc->flag == i) {
            go->enemy_lasers[i].x = go->enemies[i].x + (go->enemies[i].rect.w / 2) - (go->enemy_lasers[i].rect.w / 2);
            go->enemy_lasers[i].y = go->enemies[i].y + go->enemies[i].rect.h - go->enemy_lasers[i].rect.h;
            go->enemy_lasers[i].is_visible = true;
            gc->flag++;
        }
    }
    for (int i = 0; i < sizeof(go->enemy_lasers) / sizeof(go->enemy_lasers[0]); i++) {
        if (go->enemy_lasers[i].is_visible) {
            if (go->enemy_lasers[i].y > 0 - go->enemy_lasers[i].rect.h && go->enemy_lasers[i].y < WINDOW_HEIGHT) {
                go->enemy_lasers[i].y += go->enemy_lasers[i].vel_y * gc->delta_time;
                // Set SDL_Rect coordinates
                go->enemy_lasers[i].rect.x = go->enemy_lasers[i].x;
                go->enemy_lasers[i].rect.y = go->enemy_lasers[i].y;
            } else {
                go->enemy_lasers[i].is_visible = false;
            }
        }
    }
// --------------------------------- T E S T I N G --------------------------------- //
}
