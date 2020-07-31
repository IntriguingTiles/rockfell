#include <SDL.h>

#include "base_entity.h"

CBaseEntity::CBaseEntity(SDL_Texture* texture) {
	int w, h;
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

	rect.x = 0;
	rect.y = 0;
	rect.w = w;
	rect.h = h;

	this->texture = texture;
}

void CBaseEntity::Render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void CBaseEntity::Move(int x, int y) {
	rect.x += x;
	rect.y += y;
}