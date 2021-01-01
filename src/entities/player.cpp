#include <SDL.h>

#include "entities/player.h"
#include "globals.h"

void CPlayer::Update() {
	if (g_Input.keys.right) Move(1, 0);
	else if (g_Input.keys.left) Move(-1, 0);
	if (rect.y >= 300 && g_Input.keys.jump && !jump) jump = true;
	if (jump) Move(0, -1);
	if (rect.y < 200 && jump) jump = false;
	if (rect.y < 300 && !jump) Move(0, 1);
	nextUpdate = SDL_GetTicks() + 3;
}