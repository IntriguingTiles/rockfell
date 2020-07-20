#include <SDL.h>

#include "input.h"

void CInput::OnEvent(SDL_Event* e) {
	if (e->type == SDL_KEYDOWN) {
		switch (e->key.keysym.sym) {
		case SDLK_a:
			keys.left = true;
			break;
		case SDLK_d:
			keys.right = true;
			break;
		case SDLK_SPACE:
			keys.jump = true;
			break;
		}
	} else if (e->type == SDL_KEYUP) {
		switch (e->key.keysym.sym) {
		case SDLK_a:
			keys.left = false;
			break;
		case SDLK_d:
			keys.right = false;
			break;
		case SDLK_SPACE:
			keys.jump = false;
			break;
		}
	} else if (e->type == SDL_MOUSEBUTTONDOWN) {
		if (e->button.button == SDL_BUTTON_LEFT) keys.attack = true;
	} else if (e->type == SDL_MOUSEBUTTONUP) {
		if (e->button.button == SDL_BUTTON_LEFT) keys.attack = false;
	}
}