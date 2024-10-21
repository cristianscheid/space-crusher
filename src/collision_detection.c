#include "collision_detection.h"

typedef enum
{
    ENEMY,
    ASTEROID
} GameObjectType;

void set_explosion(GameObjects *go, GameControls *gc, int go_index, GameObjectType object_type)
{
    if (object_type == ENEMY)
    {
        go->explosions[gc->explosion_count].rect.x = go->enemies[go_index].rect.x + (go->enemies[go_index].rect.w / 2) - (go->explosions[gc->explosion_count].rect.w / 2);
        go->explosions[gc->explosion_count].rect.y = go->enemies[go_index].rect.y + (go->enemies[go_index].rect.h / 2) - (go->explosions[gc->explosion_count].rect.h / 2);
    }
    else if (object_type == ASTEROID)
    {
        go->explosions[gc->explosion_count].rect.x = go->asteroids[go_index].rect.x + (go->asteroids[go_index].rect.w / 2) - (go->explosions[gc->explosion_count].rect.w / 2);
        go->explosions[gc->explosion_count].rect.y = go->asteroids[go_index].rect.y + (go->asteroids[go_index].rect.h / 2) - (go->explosions[gc->explosion_count].rect.h / 2);
    }
    go->explosions[gc->explosion_count].is_visible = true;
    go->explosions[gc->explosion_count].display_time = 0;
    if (gc->explosion_count < (sizeof(go->explosions) / sizeof(go->explosions[0])) - 1)
    {
        gc->explosion_count++;
    }
    else
    {
        gc->explosion_count = 0;
    }
}

void detect_collision(GameObjects *go, GameControls *gc)
{
    // Player Laser X Enemy
    for (int i = 0; i < sizeof(go->player_lasers) / sizeof(go->player_lasers[0]); i++)
    {
        for (int j = 0; j < sizeof(go->enemies) / sizeof(go->enemies[0]); j++)
        {
            if (go->player_lasers[i].is_visible && go->enemies[j].is_visible && go->player_lasers[i].rect.x > go->enemies[j].rect.x - go->player_lasers[i].rect.w && go->player_lasers[i].rect.x < go->enemies[j].rect.x + go->enemies[j].rect.w && go->player_lasers[i].rect.y < go->enemies[j].rect.y + go->enemies[j].rect.h)
            {
                // Set explosion
                set_explosion(go, gc, j, ENEMY);
                // Reset laser
                go->player_lasers[i].is_visible = false;
                // Reset enemy
                go->enemies[j].y = -150;
            }
        }
    }

    // Enemy Laser X Player
    for (int i = 0; i < sizeof(go->enemy_lasers) / sizeof(go->enemy_lasers[0]); i++)
    {
        if (go->enemy_lasers[i].is_visible && go->enemy_lasers[i].rect.x > go->player.rect.x - go->enemy_lasers[i].rect.w && go->enemy_lasers[i].rect.x < go->player.rect.x + go->player.rect.w && go->enemy_lasers[i].rect.y + go->enemy_lasers[i].rect.h > go->player.rect.y && go->enemy_lasers[i].rect.y < go->player.rect.y + go->player.rect.h)
        {
            go->player.health--;
            // Reset laser
            go->enemy_lasers[i].is_visible = false;
        }
    }

    // Player Laser X Asteroid
    for (int i = 0; i < sizeof(go->player_lasers) / sizeof(go->player_lasers[0]); i++)
    {
        for (int j = 0; j < sizeof(go->asteroids) / sizeof(go->asteroids[0]); j++)
        {
            if (go->player_lasers[i].is_visible && go->asteroids[j].is_visible && go->player_lasers[i].rect.x > go->asteroids[j].rect.x - go->player_lasers[i].rect.w && go->player_lasers[i].rect.x < go->asteroids[j].rect.x + go->asteroids[j].rect.w && go->player_lasers[i].rect.y < go->asteroids[j].rect.y + go->asteroids[j].rect.h)
            {
                // Set explosion
                set_explosion(go, gc, j, ASTEROID);
                // Reset laser
                go->player_lasers[i].is_visible = false;
                // Reset asteroid
                go->asteroids[j].y = -150;
            }
        }
    }

    // Player X Enemy
    for (int i = 0; i < sizeof(go->enemies) / sizeof(go->enemies[0]); i++)
    {
        if (go->enemies[i].is_visible && go->player.rect.x > go->enemies[i].rect.x - go->player.rect.w && go->player.rect.x < go->enemies[i].rect.x + go->enemies[i].rect.w && go->player.rect.y < go->enemies[i].rect.y + go->enemies[i].rect.h && go->player.rect.y > go->enemies[i].rect.y - go->player.rect.h)
        {
            go->enemies[i].y = -150;
        }
    }

    // Player X Asteroid
    for (int i = 0; i < sizeof(go->asteroids) / sizeof(go->asteroids[0]); i++)
    {
        if (go->asteroids[i].is_visible && go->player.rect.x > go->asteroids[i].rect.x - go->player.rect.w && go->player.rect.x < go->asteroids[i].rect.x + go->asteroids[i].rect.w && go->player.rect.y < go->asteroids[i].rect.y + go->asteroids[i].rect.h && go->player.rect.y > go->asteroids[i].rect.y - go->player.rect.h)
        {
            go->asteroids[i].y = -150;
        }
    }

    // Set duration explosion sprites remain visible
    for (int i = 0; i < sizeof(go->explosions) / sizeof(go->explosions[0]); i++)
    {
        if (go->explosions[i].is_visible)
        {
            if (go->explosions[i].display_time < 10)
            {
                // count increases as a function of delta time
                go->explosions[i].display_time += 100 * gc->delta_time;
            }
            else
            {
                go->explosions[i].is_visible = false;
                go->explosions[i].display_time = 0;
            }
        }
    }
}
