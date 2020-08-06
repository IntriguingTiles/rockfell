#include <SDL.h>

#include "input.h"

#define DEADZONE 8000

void CInput::OnEvent(SDL_Event* e) {
	switch (e->type) {
	case SDL_KEYUP:
	case SDL_KEYDOWN:
		switch (e->key.keysym.sym) {
		case SDLK_a:
			keys.left = e->key.state;
			break;
		case SDLK_d:
			keys.right = e->key.state;
			break;
		case SDLK_SPACE:
			keys.jump = e->key.state;
			break;
		}
		break;
	case SDL_CONTROLLERBUTTONUP:
	case SDL_CONTROLLERBUTTONDOWN:
		switch (e->cbutton.button) {
		case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
			keys.left = e->cbutton.state;
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
			keys.right = e->cbutton.state;
			break;
		case SDL_CONTROLLER_BUTTON_A:
			keys.jump = e->cbutton.state;
			break;
		}
		break;
	case SDL_CONTROLLERAXISMOTION:
		if (e->caxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
			keys.left = e->caxis.value < -DEADZONE;
			keys.right = e->caxis.value > DEADZONE;
		}

		break;
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
		if (e->button.button == SDL_BUTTON_LEFT) keys.attack = e->button.state;
		break;
	}
}