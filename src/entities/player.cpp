#include "entities/player.h"
#include "globals.h"

void CPlayer::Update() {
	if (g_Input.keys.right) Move(1, 0);
	else if (g_Input.keys.left) Move(-1, 0);
}