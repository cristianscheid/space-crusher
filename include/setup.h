#ifndef SETUP_H
#define SETUP_H

#include <stdbool.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 720

typedef struct
{
    SDL_Surface *background_sfc;
    SDL_Surface *player_sfc;
    SDL_Surface *enemy_sfcs[14];
    SDL_Surface *asteroid_sfcs[2];
    SDL_Surface *player_laser_sfc;
    SDL_Surface *enemy_laser_sfc;
    SDL_Surface *explosion_sfc;
} Surfaces;

typedef struct
{
    SDL_Texture *background_tex;
    SDL_Texture *player_tex;
    SDL_Texture *enemy_texs[14];
    SDL_Texture *asteroid_texs[2];
    SDL_Texture *player_laser_tex;
    SDL_Texture *enemy_laser_tex;
    SDL_Texture *explosion_tex;
} Textures;

typedef struct
{
    SDL_Rect rect;
    SDL_Texture *tex;
    float x;
    float y;
    float vel_x;
    float vel_y;
    int health;
    bool is_visible;
    float display_time;
} GameObject;

typedef struct
{
    GameObject background[2];
    GameObject player;
    GameObject enemies[10];
    GameObject asteroids[10];
    GameObject player_lasers[14];
    GameObject enemy_lasers[14];
    GameObject explosions[10];
    bool game_is_running;
} GameObjects;

typedef struct
{
    bool move_up;
    bool move_down;
    bool move_left;
    bool move_right;
    bool shoot_laser;
    int player_laser_count;
    int enemy_laser_count;
    int explosion_count;
    bool game_is_running;
    float delta_time;
    int last_frame_time;
    int int_main_count;
    float float_main_count;
    int flag;
} GameControls;

bool initialize_sdl(void);
SDL_Window *create_window(void);
SDL_Renderer *create_renderer(SDL_Window *window);
Surfaces *create_surfaces();
Textures *create_textures(SDL_Renderer *renderer, Surfaces *surfaces);
void free_surfaces(Surfaces *surfaces);
void destroy_textures(Textures *textures);

#endif
