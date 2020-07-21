#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "sdl_goop.h"

bool CSDLGoop::Init(SDL_Window** window, SDL_Renderer** renderer, const char* title, const char* iconPath, int w, int h) {
	if (SDL_Init(SDL_INIT_VIDEO) == -1) return false;
	if (!IMG_Init(IMG_INIT_PNG)) return false;

	*window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	if (!*window) return false;

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
	if (!*renderer) return false;

	SDL_SetRenderDrawColor(*renderer, 0x00, 0x00, 0x00, 0xFF);

	auto* icon = IMG_Load(iconPath);

	SDL_SetWindowIcon(*window, icon);

	return true;
}

SDL_Texture* CSDLGoop::LoadTexture(const char* path, SDL_Renderer* renderer) {
	auto* surface = IMG_Load(path);

	if (!surface) {
		return nullptr;
	}

	auto* texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (!texture) {
		return nullptr;
	}

	SDL_FreeSurface(surface);

	return texture;
}

void CSDLGoop::Shutdown(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}