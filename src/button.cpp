#include <functional>
#include <SDL.h>

#include "globals.h"
#include "button.h"

CButton::CButton(SDL_Rect rect, SDL_Texture* texture, std::function<void()> callback) {
	this->rect = rect;
	this->texture = texture;
	this->callback = callback;
}

void CButton::Render(SDL_Renderer* renderer) {
	if (hovered) SDL_SetTextureColorMod(texture, 200, 200, 200);
	if (pressed) SDL_SetTextureColorMod(texture, 100, 100, 100);

	SDL_RenderCopy(renderer, texture, nullptr, &rect);
	SDL_SetTextureColorMod(texture, 255, 255, 255);
}

void CButton::OnEvent(SDL_Event* e) {
	switch (e->type) {
	case SDL_MOUSEMOTION: {
		int x, y;

		SDL_GetMouseState(&x, &y);

		if (IsInRect(x, y)) hovered = true;
		else hovered = false;
		break;
	}
	case SDL_MOUSEBUTTONDOWN:
		if (e->button.button == SDL_BUTTON_LEFT) {
			int x, y;

			SDL_GetMouseState(&x, &y);

			if (IsInRect(x, y)) pressed = true;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (e->button.button == SDL_BUTTON_LEFT) {
			int x, y;

			SDL_GetMouseState(&x, &y);

			if (IsInRect(x, y) && pressed) {
				pressed = false;
				callback();
			} else {
				pressed = false;
			}
		}
		break;
	case SDL_FINGERMOTION: {
		int x = static_cast<int>(e->tfinger.x * SCREEN_WIDTH);
		int y = static_cast<int>(e->tfinger.y * SCREEN_HEIGHT);

		if (IsInRect(x, y)) hovered = true;
		else hovered = false;
		break;
	}
	case SDL_FINGERDOWN: {
		int x = static_cast<int>(e->tfinger.x * SCREEN_WIDTH);
		int y = static_cast<int>(e->tfinger.y * SCREEN_HEIGHT);

		if (IsInRect(x, y)) pressed = true;
		break;
	}
	case SDL_FINGERUP: {
		int x = static_cast<int>(e->tfinger.x * SCREEN_WIDTH);
		int y = static_cast<int>(e->tfinger.y * SCREEN_HEIGHT);

		if (IsInRect(x, y) && pressed) {
			pressed = false;
			callback();
		} else {
			pressed = false;
		}
	}
	}
}

bool CButton::IsInRect(int x, int y) {
	return (x >= rect.x && x < rect.x + rect.w && y >= rect.y && y < rect.y + rect.h);
}