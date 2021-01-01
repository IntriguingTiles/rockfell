#include <SDL.h>

#include "entities/player.h"
#include "entities/energy_ball.h"
#include "globals.h"

void CPlayer::Update() {
	if (g_Globals.input.keys.right) Move(1, 0);
	else if (g_Globals.input.keys.left) Move(-1, 0);
	if (rect.y >= 300 && g_Globals.input.keys.jump && !jump) jump = true;
	if (jump) Move(0, -1);
	if (rect.y < 200 && jump) jump = false;
	if (rect.y < 300 && !jump) Move(0, 1);

	if (g_Globals.input.keys.attack && nextAttack <= SDL_GetTicks()) {
		g_Globals.rockfell->pending.push_back(std::make_unique<CEnergyBall>(g_Globals.textures["start"], rect.x + 50, rect.y + 30));
		nextAttack = SDL_GetTicks() + 500;
	}

	nextUpdate = SDL_GetTicks() + 3;
}