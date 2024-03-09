#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 720
#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

///////////////////////////////////////////////////////////////////////////////
// Global variables
///////////////////////////////////////////////////////////////////////////////
int game_is_running = false;
int last_frame_time = 0;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

SDL_Texture *background_tex = NULL;
SDL_Texture *player_tex = NULL;
SDL_Texture *laser_tex = NULL;
SDL_Texture *enemies_texs[14];
SDL_Texture *asteroids_texs[2];
SDL_Texture *explosion_tex = NULL;

bool move_up = false;
bool move_down = false;
bool move_left = false;
bool move_right = false;
bool shoot_laser = false;

int laser_count = 0;

///////////////////////////////////////////////////////////////////////////////
// Declare game objects
///////////////////////////////////////////////////////////////////////////////
struct background {
    SDL_Rect rect;
    float x;
    float y;
    float vel_y;
    bool is_visible;
} backgrounds[2];

struct game_object {
    SDL_Rect rect;
    SDL_Texture *tex;
    float x;
    float y;
    float vel_x;
    float vel_y;
    bool is_visible;
} player, lasers[14], enemies[8], asteroids[8];

struct explosion {
    SDL_Rect rect;
    SDL_Texture *tex;
    float x;
    float y;
    float count;
    bool is_visible;
} explosions[8];


///////////////////////////////////////////////////////////////////////////////
// Level 1 objects position
///////////////////////////////////////////////////////////////////////////////
//enemies[0].x = ;
//enemies[0].y = ;

///////////////////////////////////////////////////////////////////////////////
// Function to initialize our SDL window
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
// Function to poll SDL events and process keyboard input
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
// Setup function that runs once at the beginning of our program
///////////////////////////////////////////////////////////////////////////////
void setup(void) {

    // srand initialization - generate random numbers with rand()
    srand(time(NULL));

    // Create surfaces
    SDL_Surface *background_sfc = IMG_Load("assets/background.png");
    SDL_Surface *player_sfc = IMG_Load("assets/player.png");
    SDL_Surface *laser_sfc = IMG_Load("assets/laser.png");
    SDL_Surface *enemies_sfcs[14];
    enemies_sfcs[0] = IMG_Load("assets/enemy-blue-01.png");
    enemies_sfcs[1] = IMG_Load("assets/enemy-blue-02.png");
    enemies_sfcs[2] = IMG_Load("assets/enemy-brown-01.png");
    enemies_sfcs[3] = IMG_Load("assets/enemy-brown-02.png");
    enemies_sfcs[4] = IMG_Load("assets/enemy-green-01.png");
    enemies_sfcs[5] = IMG_Load("assets/enemy-green-02.png");
    enemies_sfcs[6] = IMG_Load("assets/enemy-orange-01.png");
    enemies_sfcs[7] = IMG_Load("assets/enemy-orange-02.png");
    enemies_sfcs[8] = IMG_Load("assets/enemy-purple-01.png");
    enemies_sfcs[9] = IMG_Load("assets/enemy-purple-02.png");
    enemies_sfcs[10] = IMG_Load("assets/enemy-red-01.png");
    enemies_sfcs[11] = IMG_Load("assets/enemy-red-02.png");
    enemies_sfcs[12] = IMG_Load("assets/enemy-yellow-01.png");
    enemies_sfcs[13] = IMG_Load("assets/enemy-yellow-02.png");
    SDL_Surface *asteroids_sfcs[2];
    asteroids_sfcs[0] = IMG_Load("assets/asteroid-01.png");
    asteroids_sfcs[1] = IMG_Load("assets/asteroid-02.png");
    SDL_Surface *explosion_sfc = IMG_Load("assets/explosion.png");

    // Create textures
    background_tex = SDL_CreateTextureFromSurface(renderer, background_sfc);
    SDL_FreeSurface(background_sfc);
    player_tex = SDL_CreateTextureFromSurface(renderer, player_sfc);
    SDL_FreeSurface(player_sfc);
    laser_tex = SDL_CreateTextureFromSurface(renderer, laser_sfc);
    SDL_FreeSurface(laser_sfc);
    for (int i = 0; i < sizeof(enemies_texs) / sizeof(enemies_texs[0]); i++) {
        enemies_texs[i] = SDL_CreateTextureFromSurface(renderer, enemies_sfcs[i]);
        SDL_FreeSurface(enemies_sfcs[i]);
    }
    for (int i = 0; i < sizeof(asteroids_texs) / sizeof(asteroids_texs[0]); i++) {
        asteroids_texs[i] = SDL_CreateTextureFromSurface(renderer, asteroids_sfcs[i]);
        SDL_FreeSurface(asteroids_sfcs[i]);
    }
    explosion_tex = SDL_CreateTextureFromSurface(renderer, explosion_sfc);

    // Get background sprite dimensions
    int background_img_width, background_img_height;
    SDL_QueryTexture(background_tex, NULL, NULL, &background_img_width, &background_img_height);
    // Initialize background object
    backgrounds[0].x = backgrounds[1].x = 0;
    backgrounds[0].y = WINDOW_HEIGHT - background_img_height;
    backgrounds[1].y = - background_img_height;
    backgrounds[0].vel_y = backgrounds[1].vel_y = 700;
    backgrounds[0].is_visible = true;
    backgrounds[1].is_visible = false;
    backgrounds[0].rect.w = backgrounds[1].rect.w = background_img_width;
    backgrounds[0].rect.h = backgrounds[1].rect.h = background_img_height;

    // Get player sprite dimensions
    player.tex = player_tex;
    SDL_QueryTexture(player.tex, NULL, NULL, &player.rect.w, &player.rect.h);
    // Initialize player object
    player.x = (WINDOW_WIDTH / 2) - (player.rect.w / 2);
    player.y = 500;
    player.vel_x = 300;
    player.vel_y = 300;

    // Get laser sprite dimensions
    int laser_img_width, laser_img_height;
    SDL_QueryTexture(laser_tex, NULL, NULL, &laser_img_width, &laser_img_height);
    // Initialize lasers objects
    for (int i = 0; i < sizeof(lasers) / sizeof(lasers[0]); i++) {
        lasers[i].tex = laser_tex;
        lasers[i].rect.w = laser_img_width;
        lasers[i].rect.h = laser_img_height;
        lasers[i].vel_y = 800;
        lasers[i].is_visible = false;
    }

    // Define enemies sprites
    int j;
    for (int i = 0; i < sizeof(enemies) / sizeof(enemies[0]); i++) {
        // Generate random index (j) to choose random sprite
        j = rand() % (sizeof(enemies_texs) / sizeof(enemies_texs[0]));
        enemies[i].tex = enemies_texs[j];
        // Get sprite dimensions
        SDL_QueryTexture(enemies[i].tex, NULL, NULL, &enemies[i].rect.w, &enemies[i].rect.h);
        // Initialize object
        enemies[i].x = i * 100;
        enemies[i].y = -(i * 150);
        enemies[i].vel_y = 40 + (rand() % 200);
        enemies[i].is_visible = false;
    }

    // Define asteroids sprites
    for (int i = 0; i < sizeof(asteroids) / sizeof(asteroids[0]); i++) {
        // Generate random index (j) to choose random sprite
        j = rand() % ((sizeof(asteroids_texs) / sizeof(asteroids_texs[0])));
        asteroids[i].tex = asteroids_texs[j];
        // Get sprite dimensions
        SDL_QueryTexture(asteroids[i].tex, NULL, NULL, &asteroids[i].rect.w, &asteroids[i].rect.h);
        // Initialize object
        asteroids[i].x = i * 100;
        asteroids[i].y = -(i * 150);
        asteroids[i].vel_y = 40 + (rand() % 200);
        asteroids[i].is_visible = false;
    }

    // Get explosion sprite dimensions
    int explosion_img_width, explosion_img_height;
    SDL_QueryTexture(explosion_tex, NULL, NULL, &explosion_img_width, &explosion_img_height);
    // Initialize explosion objects
    for (int i = 0; i < sizeof(explosions) / sizeof(explosions[0]); i++) {
        explosions[i].tex = explosion_tex;
        explosions[i].rect.w = explosion_img_width / 1.5;
        explosions[i].rect.h = explosion_img_height / 1.5;
        explosions[i].is_visible = false;
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

    for (int i = 0; i < sizeof(backgrounds) / sizeof(backgrounds[0]); i++) {
        bool j = !i;
        if (backgrounds[i].is_visible && backgrounds[i].y < WINDOW_HEIGHT){
            backgrounds[i].y += backgrounds[i].vel_y * delta_time;
            // Set SDL_Rect coordinates
            backgrounds[i].rect.x = backgrounds[i].x;
            backgrounds[i].rect.y = backgrounds[i].y;
            if (backgrounds[i].y > 0){
                backgrounds[j].is_visible = true;
            }
        } else {
            backgrounds[i].is_visible = false;
            backgrounds[i].y = - backgrounds[i].rect.h;
        }
    }

    // Move player as a function of delta time
    if (move_up && !move_down && player.y >= 0) {
        player.y -= player.vel_y * delta_time;
    }
    if (move_down && !move_up && player.y <= WINDOW_HEIGHT - player.rect.h) {
        player.y += player.vel_y * delta_time;
    }
    if (move_left && !move_right && player.x >= 0) {
        player.x -= player.vel_x * delta_time;
    }
    if (move_right && !move_left && player.x <= WINDOW_WIDTH - player.rect.w) {
        player.x += player.vel_x * delta_time;
    }
    // Set SDL_Rect coordinates
    player.rect.x = player.x;
    player.rect.y = player.y;

    // Set laser to visible if space was pressed
    if (shoot_laser) {
        lasers[laser_count].x = player.x + (player.rect.w / 2) - (lasers[laser_count].rect.w / 2);
        lasers[laser_count].y = player.y;
        lasers[laser_count].is_visible = true;
        if (laser_count < (sizeof(lasers) / sizeof(lasers[0])) - 1) {
            laser_count++;
        } else {
            laser_count = 0;
        }
        shoot_laser = false;
    }
    // Move visible lasers as a function of delta time
    for (int i = 0; i < sizeof(lasers) / sizeof(lasers[0]); i++) {
        if (lasers[i].is_visible && lasers[i].y > 0 - lasers[i].rect.h) {
            lasers[i].y -= lasers[i].vel_y * delta_time;
            // Set SDL_Rect coordinates
            lasers[i].rect.x = lasers[i].x;
            lasers[i].rect.y = lasers[i].y;
        } else {
            lasers[i].is_visible = false;
        }
    }

    // Move enemies as a function of delta time
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

    // Move asteroids as a function of delta time
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

    // Set duration explosions sprites remain visible before disappearing
    for (int i = 0; i < sizeof(explosions) / sizeof(explosions[0]); i++) {
        if (explosions[i].is_visible) {
            if (explosions[i].count < 10) {
                // Duration increases as a function of delta time
                explosions[i].count += 100 * delta_time;
            } else {
                explosions[i].is_visible = false;
                explosions[i].count = 0;
            }
        }
    }

    // TODO: COLLISION DETECTION
    // Laser X Enemy
    for (int i = 0; i < sizeof(lasers) / sizeof(lasers[0]); i++) {
        for (int j = 0; j < sizeof(enemies) / sizeof(enemies[0]); j++) {
            if (lasers[i].is_visible && enemies[j].is_visible
                && lasers[i].rect.x > enemies[j].rect.x - lasers[i].rect.w
                && lasers[i].rect.x < enemies[j].rect.x + enemies[j].rect.w
                && lasers[i].rect.y < enemies[j].rect.y + enemies[j].rect.h) {
                // Reset laser
                lasers[i].is_visible = false;
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
    for (int i = 0; i < sizeof(lasers) / sizeof(lasers[0]); i++) {
        for (int j = 0; j < sizeof(asteroids) / sizeof(asteroids[0]); j++) {
            if (lasers[i].is_visible && asteroids[j].is_visible
                && lasers[i].rect.x > asteroids[j].rect.x - lasers[i].rect.w
                && lasers[i].rect.x < asteroids[j].rect.x + asteroids[j].rect.w
                && lasers[i].rect.y < asteroids[j].rect.y + asteroids[j].rect.h) {
                // Reset laser
                lasers[i].is_visible = false;
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

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw background
    for (int i = 0; i < sizeof(backgrounds) / sizeof(backgrounds[0]); i++) {
        if (backgrounds[i].is_visible) {
            SDL_RenderCopy(renderer, background_tex, NULL, &backgrounds[i].rect);
        }
    }

    // Draw player
    SDL_RenderCopy(renderer, player.tex, NULL, &player.rect);

    // Draw visible lasers
    for (int i = 0; i < sizeof(lasers) / sizeof(lasers[0]); i++) {
        if (lasers[i].is_visible) {
            SDL_RenderCopy(renderer, laser_tex, NULL, &lasers[i].rect);
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

    setup();

    while (game_is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}