#include <SDL.h>

#include "entities/energy_ball.h"
#include "globals.h"

void CEnergyBall::Update() {
	Move(1, 0);
	nextUpdate = SDL_GetTicks() + 2;
}