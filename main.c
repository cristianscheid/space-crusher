#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 720

///////////////////////////////////////////////////////////////////////////////
// Global variables
///////////////////////////////////////////////////////////////////////////////
int game_is_running = false;
int last_frame_time = 0;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

SDL_Texture *background_tex = NULL;
SDL_Texture *player_tex = NULL;
SDL_Texture *player_laser_tex = NULL;
SDL_Texture *enemy_laser_tex = NULL;
SDL_Texture *enemy_texs[14];
SDL_Texture *asteroid_texs[2];
SDL_Texture *explosion_tex = NULL;

bool move_up = false;
bool move_down = false;
bool move_left = false;
bool move_right = false;
bool shoot_laser = false;

float float_main_count = 0;
int int_main_count = 0;
int flag = 0;
int player_laser_count = 0;
int enemy_laser_count = 0;

///////////////////////////////////////////////////////////////////////////////
// Declare game objects
///////////////////////////////////////////////////////////////////////////////
struct game_object {
    SDL_Rect rect;
    SDL_Texture *tex;
    float x;
    float y;
    float vel_x;
    float vel_y;
    float count;
    bool is_visible;
} background[2], player, enemies[8], asteroids[8], player_lasers[14], enemy_lasers[14], explosions[8];

///////////////////////////////////////////////////////////////////////////////
// Initialize SDL window
///////////////////////////////////////////////////////////////////////////////
int initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }
    window = SDL_CreateWindow(
            "Space Crusher",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            0
    );
    if (!window) {
        fprintf(stderr, "Error creating SDL Window.\n");
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL Renderer.\n");
        return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////////
// Initial setup
///////////////////////////////////////////////////////////////////////////////
void initial_setup(void) {

    // Initialize srand to generate random numbers with rand()
    srand(time(NULL));

    // Create SDL surfaces
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

    // Create SDL textures
    background_tex = SDL_CreateTextureFromSurface(renderer, background_sfc);
    SDL_FreeSurface(background_sfc);
    player_tex = SDL_CreateTextureFromSurface(renderer, player_sfc);
    SDL_FreeSurface(player_sfc);
    for (int i = 0; i < sizeof(enemy_texs) / sizeof(enemy_texs[0]); i++) {
        enemy_texs[i] = SDL_CreateTextureFromSurface(renderer, enemy_sfcs[i]);
        SDL_FreeSurface(enemy_sfcs[i]);
    }
    for (int i = 0; i < sizeof(asteroid_texs) / sizeof(asteroid_texs[0]); i++) {
        asteroid_texs[i] = SDL_CreateTextureFromSurface(renderer, asteroid_sfcs[i]);
        SDL_FreeSurface(asteroid_sfcs[i]);
    }
    player_laser_tex = SDL_CreateTextureFromSurface(renderer, player_laser_sfc);
    SDL_FreeSurface(player_laser_sfc);
    enemy_laser_tex = SDL_CreateTextureFromSurface(renderer, enemy_laser_sfc);
    SDL_FreeSurface(enemy_laser_sfc);
    explosion_tex = SDL_CreateTextureFromSurface(renderer, explosion_sfc);
    SDL_FreeSurface(explosion_sfc);

    ///////////////////////////////////////////////////////////////////////////////
    // Define texture (sprite) for each game object and gather its dimensions
    // 'SDL_QueryTexture' returns width and height to the last two parameters
    // /////////////////////////////////////////////////////////////////////////////
    // Background
    int background_width, background_height;
    background[0].tex = background[1].tex = background_tex;
    SDL_QueryTexture(background_tex, NULL, NULL, &background_width, &background_height);
    background[0].x = background[1].x = 0;
    background[0].y = WINDOW_HEIGHT - background_height;
    background[1].y = -background_height;
    background[0].rect.w = background[1].rect.w = background_width;
    background[0].rect.h = background[1].rect.h = background_height;
    background[0].vel_y = background[1].vel_y = 700;
    background[0].is_visible = true;
    background[1].is_visible = false;

    // Player
    player.tex = player_tex;
    SDL_QueryTexture(player.tex, NULL, NULL, &player.rect.w, &player.rect.h);
    player.x = (WINDOW_WIDTH / 2) - (player.rect.w / 2);
    player.y = 500;
    player.vel_x = 300;
    player.vel_y = 300;

    // Enemies
    for (int i = 0; i < sizeof(enemies) / sizeof(enemies[0]); i++) {
        // Generate random index (j) to choose random sprite
        int j = rand() % (sizeof(enemy_texs) / sizeof(enemy_texs[0]));
        enemies[i].tex = enemy_texs[j];
        SDL_QueryTexture(enemies[i].tex, NULL, NULL, &enemies[i].rect.w, &enemies[i].rect.h);
        enemies[i].x = i * 100;
        enemies[i].y = 150;
        enemies[i].is_visible = false;
    }

    // Asteroids
    for (int i = 0; i < sizeof(asteroids) / sizeof(asteroids[0]); i++) {
        // Generate random index (j) to choose random sprite
        int j = rand() % ((sizeof(asteroid_texs) / sizeof(asteroid_texs[0])));
        asteroids[i].tex = asteroid_texs[j];
        SDL_QueryTexture(asteroids[i].tex, NULL, NULL, &asteroids[i].rect.w, &asteroids[i].rect.h);
        asteroids[i].x = i * 100;
        asteroids[i].y = 0;
        asteroids[i].is_visible = false;
    }

    // Player laser
    int player_laser_width, player_laser_height;
    SDL_QueryTexture(player_laser_tex, NULL, NULL, &player_laser_width, &player_laser_height);
    for (int i = 0; i < sizeof(player_lasers) / sizeof(player_lasers[0]); i++) {
        player_lasers[i].tex = player_laser_tex;
        player_lasers[i].rect.w = player_laser_width;
        player_lasers[i].rect.h = player_laser_height;
        player_lasers[i].vel_y = 800;
        player_lasers[i].is_visible = false;
    }

    // Enemy laser
    int enemy_laser_width, enemy_laser_height;
    SDL_QueryTexture(enemy_laser_tex, NULL, NULL, &enemy_laser_width, &enemy_laser_height);
    for (int i = 0; i < sizeof(enemy_lasers) / sizeof(enemy_lasers[0]); i++) {
        enemy_lasers[i].tex = enemy_laser_tex;
        enemy_lasers[i].rect.w = enemy_laser_width;
        enemy_lasers[i].rect.h = enemy_laser_height;
        enemy_lasers[i].vel_y = 800;
        enemy_lasers[i].is_visible = false;
    }

    // Explosion
    int explosion_img_width, explosion_img_height;
    SDL_QueryTexture(explosion_tex, NULL, NULL, &explosion_img_width, &explosion_img_height);
    for (int i = 0; i < sizeof(explosions) / sizeof(explosions[0]); i++) {
        explosions[i].tex = explosion_tex;
        explosions[i].rect.w = explosion_img_width / 1.5;
        explosions[i].rect.h = explosion_img_height / 1.5;
        explosions[i].is_visible = false;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Process input
///////////////////////////////////////////////////////////////////////////////
void process_input(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        move_up = true;
                        break;
                    case SDLK_DOWN:
                        move_down = true;
                        break;
                    case SDLK_LEFT:
                        move_left = true;
                        break;
                    case SDLK_RIGHT:
                        move_right = true;
                        break;
                    case SDLK_SPACE:
                        shoot_laser = true;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        move_up = false;
                        break;
                    case SDLK_DOWN:
                        move_down = false;
                        break;
                    case SDLK_LEFT:
                        move_left = false;
                        break;
                    case SDLK_RIGHT:
                        move_right = false;
                        break;
                    case SDLK_SPACE:
                        shoot_laser = false;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                game_is_running = false;
                break;
            default:
                break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Update function with a fixed time step
///////////////////////////////////////////////////////////////////////////////
void update(void) {
    // Get delta_time factor converted to seconds to be used to update objects
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0;
    // Store the milliseconds of the current frame to be used in the next one
    last_frame_time = SDL_GetTicks();

    float_main_count += delta_time;
    int_main_count = float_main_count;
    printf("%d - %.6f\n", int_main_count, float_main_count);

    ///////////////////////////////////////////////////////////////////////////////
    // Move game objects
    ///////////////////////////////////////////////////////////////////////////////
    // Move Background
    for (int i = 0; i < sizeof(background) / sizeof(background[0]); i++) {
        // The 'background' array holds two identical images at positions 0 and 1
        // 'j' toggles between 0 and 1, allowing access to the opposite index of the loop
        // This enables dynamic background object calling and infinite image scrolling
        bool j = !i;
        if (background[i].is_visible && background[i].y < WINDOW_HEIGHT) {
            background[i].y += background[i].vel_y * delta_time;
            // Set SDL_Rect coordinates
            background[i].rect.x = background[i].x;
            background[i].rect.y = background[i].y;
            if (background[i].y > 0) {
                background[j].is_visible = true;
            }
        } else {
            background[i].is_visible = false;
            background[i].y = -background[i].rect.h;
        }
    }

    // Move player
    if (move_up && !move_down && player.y > 0) {
        player.y -= player.vel_y * delta_time;
    }
    if (move_down && !move_up && player.y < WINDOW_HEIGHT - player.rect.h) {
        player.y += player.vel_y * delta_time;
    }
    if (move_left && !move_right && player.x > 0) {
        player.x -= player.vel_x * delta_time;
    }
    if (move_right && !move_left && player.x < WINDOW_WIDTH - player.rect.w) {
        player.x += player.vel_x * delta_time;
    }
    // Set SDL_Rect coordinates
    player.rect.x = player.x;
    player.rect.y = player.y;

    // Move enemies
    for (int i = 0; i < sizeof(enemies) / sizeof(enemies[0]); i++) {
        enemies[i].y += enemies[i].vel_y * delta_time;
        if (enemies[i].y >= 0 - enemies[i].rect.h && enemies[i].y < WINDOW_HEIGHT) {
            enemies[i].is_visible = true;
            // Set SDL_Rect coordinates
            enemies[i].rect.x = enemies[i].x;
            enemies[i].rect.y = enemies[i].y;
        } else {
            enemies[i].is_visible = false;
        }
    }

    // Move asteroids
    for (int i = 0; i < sizeof(asteroids) / sizeof(asteroids[0]); i++) {
        asteroids[i].y += asteroids[i].vel_y * delta_time;
        if (asteroids[i].y >= 0 - asteroids[i].rect.h && asteroids[i].y < WINDOW_HEIGHT) {
            asteroids[i].is_visible = true;
            // Set SDL_Rect coordinates
            asteroids[i].rect.x = asteroids[i].x;
            asteroids[i].rect.y = asteroids[i].y;
        } else {
            asteroids[i].is_visible = false;
        }
    }

    // Start player laser (if space was pressed)
    if (shoot_laser) {
        player_lasers[player_laser_count].x = player_lasers[player_laser_count].x = player.x + (player.rect.w / 2) - (player_lasers[player_laser_count].rect.w / 2);;
        player_lasers[player_laser_count].y = player.y;
        player_lasers[player_laser_count].is_visible = true;
        if (player_laser_count < (sizeof(player_lasers) / sizeof(player_lasers[0])) - 1) {
            player_laser_count++;
        } else {
            player_laser_count = 0;
        }
        shoot_laser = false;
    }

    // Move player lasers
    for (int i = 0; i < sizeof(player_lasers) / sizeof(player_lasers[0]); i++) {
        if (player_lasers[i].is_visible) {
            if (player_lasers[i].y > 0 - player_lasers[i].rect.h && player_lasers[i].y < WINDOW_HEIGHT) {
                player_lasers[i].y -= player_lasers[i].vel_y * delta_time;
                // Set SDL_Rect coordinates
                player_lasers[i].rect.x = player_lasers[i].x;
                player_lasers[i].rect.y = player_lasers[i].y;
            } else {
                player_lasers[i].is_visible = false;

            }
        }
    }
    // --------------------------------- T E S T I N G --------------------------------- //
    // Move enemy lasers
    for (int i = 0; i < sizeof(enemies) / sizeof(enemies[0]); i++) {
        if (int_main_count == 1 + i && flag == i) {
            enemy_lasers[i].x = enemies[i].x + (enemies[i].rect.w / 2) - (enemy_lasers[i].rect.w / 2);
            enemy_lasers[i].y = enemies[i].y + enemies[i].rect.h - enemy_lasers[i].rect.h;
            enemy_lasers[i].is_visible = true;
            flag++;
        }
    }
    for (int i = 0; i < sizeof(enemy_lasers) / sizeof(enemy_lasers[0]); i++) {
        if (enemy_lasers[i].is_visible) {
            if (enemy_lasers[i].y > 0 - enemy_lasers[i].rect.h && enemy_lasers[i].y < WINDOW_HEIGHT) {
                enemy_lasers[i].y += enemy_lasers[i].vel_y * delta_time;
                // Set SDL_Rect coordinates
                enemy_lasers[i].rect.x = enemy_lasers[i].x;
                enemy_lasers[i].rect.y = enemy_lasers[i].y;
            } else {
                enemy_lasers[i].is_visible = false;
            }
        }
    }
    // --------------------------------- T E S T I N G --------------------------------- //

    // Set duration explosion sprites remain visible
    for (int i = 0; i < sizeof(explosions) / sizeof(explosions[0]); i++) {
        if (explosions[i].is_visible) {
            if (explosions[i].count < 10) {
                // count increases as a function of delta time
                explosions[i].count += 100 * delta_time;
            } else {
                explosions[i].is_visible = false;
                explosions[i].count = 0;
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    // Collision detection
    ///////////////////////////////////////////////////////////////////////////////
    // Laser X Enemy
    for (int i = 0; i < sizeof(player_lasers) / sizeof(player_lasers[0]); i++) {
        for (int j = 0; j < sizeof(enemies) / sizeof(enemies[0]); j++) {
            if (player_lasers[i].is_visible && enemies[j].is_visible
                && player_lasers[i].rect.x > enemies[j].rect.x - player_lasers[i].rect.w
                && player_lasers[i].rect.x < enemies[j].rect.x + enemies[j].rect.w
                && player_lasers[i].rect.y < enemies[j].rect.y + enemies[j].rect.h) {
                // Reset laser
                player_lasers[i].is_visible = false;
                // Reset enemy
                enemies[j].y = -150;
                // Set explosion
                explosions[j].is_visible = true;
                explosions[j].rect.x = enemies[j].rect.x + (enemies[j].rect.w / 2) - (explosions[j].rect.w / 2);
                explosions[j].rect.y = enemies[j].rect.y + (enemies[j].rect.h / 2) - (explosions[j].rect.h / 2);
            }
        }
    }

    // Laser X Asteroid
    for (int i = 0; i < sizeof(player_lasers) / sizeof(player_lasers[0]); i++) {
        for (int j = 0; j < sizeof(asteroids) / sizeof(asteroids[0]); j++) {
            if (player_lasers[i].is_visible && asteroids[j].is_visible
                && player_lasers[i].rect.x > asteroids[j].rect.x - player_lasers[i].rect.w
                && player_lasers[i].rect.x < asteroids[j].rect.x + asteroids[j].rect.w
                && player_lasers[i].rect.y < asteroids[j].rect.y + asteroids[j].rect.h) {
                // Reset laser
                player_lasers[i].is_visible = false;
                // Reset asteroid
                asteroids[j].y = -150;
                // Set explosion
                explosions[j].is_visible = true;
                explosions[j].rect.x = asteroids[j].rect.x + (asteroids[j].rect.w / 2) - (explosions[j].rect.w / 2);
                explosions[j].rect.y = asteroids[j].rect.y + (asteroids[j].rect.h / 2) - (explosions[j].rect.h / 2);
            }
        }
    }

    // Player X Enemy
    for (int i = 0; i < sizeof(enemies) / sizeof(enemies[0]); i++) {
        if (enemies[i].is_visible
            && player.rect.x > enemies[i].rect.x - player.rect.w
            && player.rect.x < enemies[i].rect.x + enemies[i].rect.w
            && player.rect.y < enemies[i].rect.y + enemies[i].rect.h
            && player.rect.y > enemies[i].rect.y - player.rect.h) {
            enemies[i].y = -150;
        }
    }

    // Player X Asteroid
    for (int i = 0; i < sizeof(asteroids) / sizeof(asteroids[0]); i++) {
        if (asteroids[i].is_visible
            && player.rect.x > asteroids[i].rect.x - player.rect.w
            && player.rect.x < asteroids[i].rect.x + asteroids[i].rect.w
            && player.rect.y < asteroids[i].rect.y + asteroids[i].rect.h
            && player.rect.y > asteroids[i].rect.y - player.rect.h) {
            asteroids[i].y = -150;
        }
    }

    // Enemy X Enemy ?

}

///////////////////////////////////////////////////////////////////////////////
// Render function to draw game objects in the SDL window
///////////////////////////////////////////////////////////////////////////////
void render(void) {

    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw background
    for (int i = 0; i < sizeof(background) / sizeof(background[0]); i++) {
        if (background[i].is_visible) {
            SDL_RenderCopy(renderer, background_tex, NULL, &background[i].rect);
        }
    }
    // Draw visible player lasers
    for (int i = 0; i < sizeof(player_lasers) / sizeof(player_lasers[0]); i++) {
        if (player_lasers[i].is_visible) {
            SDL_RenderCopy(renderer, player_laser_tex, NULL, &player_lasers[i].rect);
        }
    }
    // Draw player
    SDL_RenderCopy(renderer, player.tex, NULL, &player.rect);
    // Draw visible enemy lasers
    for (int i = 0; i < sizeof(enemy_lasers) / sizeof(enemy_lasers[0]); i++) {
        if (enemy_lasers[i].is_visible) {
            SDL_RenderCopy(renderer, enemy_laser_tex, NULL, &enemy_lasers[i].rect);
        }
    }
    // Draw enemies
    for (int i = 0; i < sizeof(enemies) / sizeof(enemies[0]); i++) {
        if (enemies[i].is_visible) {
            SDL_RenderCopy(renderer, enemies[i].tex, NULL, &enemies[i].rect);
        }
    }
    // Draw asteroids
    for (int i = 0; i < sizeof(asteroids) / sizeof(asteroids[0]); i++) {
        if (asteroids[i].is_visible) {
            SDL_RenderCopy(renderer, asteroids[i].tex, NULL, &asteroids[i].rect);
        }
    }
    // Draw explosions (if collision happened)
    for (int i = 0; i < sizeof(explosions) / sizeof(explosions[0]); i++) {
        if (explosions[i].is_visible) {
            SDL_RenderCopy(renderer, explosions[i].tex, NULL, &explosions[i].rect);
        }
    }

    SDL_RenderPresent(renderer);
}

///////////////////////////////////////////////////////////////////////////////
// Function to destroy SDL window and renderer
///////////////////////////////////////////////////////////////////////////////
void destroy_window(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

///////////////////////////////////////////////////////////////////////////////
// Main function
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char *args[]) {
    game_is_running = initialize_window();

    initial_setup();

    while (game_is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}