#pragma once

#include <SDL.h>

class CSDLGoop {
public:
	bool Init(SDL_Window** window, SDL_Renderer** renderer, const char* title, int w, int h);
	SDL_Texture* LoadTexture(const char* path, SDL_Renderer* renderer);
	void Shutdown(SDL_Window* window, SDL_Renderer* renderer);
};