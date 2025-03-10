#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL2/SDL.h>
#include "setup.h"

void process_input(SDL_Event *event, GameControls *game_controls);

#endif
