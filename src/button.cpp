#include <functional>
#include <SDL.h>

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
	if (e->type == SDL_MOUSEMOTION) {
		int x, y;

		SDL_GetMouseState(&x, &y);

		if (IsInRect(x, y)) hovered = true;
		else hovered = false;
	} else if (e->type == SDL_MOUSEBUTTONDOWN) {
		if (e->button.button == SDL_BUTTON_LEFT) {
			int x, y;

			SDL_GetMouseState(&x, &y);

			if (IsInRect(x, y)) pressed = true;
		}
	} else if (e->type == SDL_MOUSEBUTTONUP) {
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
	}
}

bool CButton::IsInRect(int x, int y) {
	return (x >= rect.x && x < rect.x + rect.w && y >= rect.y && y < rect.y + rect.h);
}