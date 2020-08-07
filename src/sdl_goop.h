#pragma once

#include <SDL.h>
#include <vector>

class CSDLGoop {
private:
#ifdef __WIIU__
	std::vector<SDL_Joystick*> controllers;
#else
	std::vector<SDL_GameController*> controllers;
#endif
public:
	bool Init(SDL_Window** window, SDL_Renderer** renderer, const char* title, const char* iconPath, int w, int h);
	SDL_Texture* LoadTexture(const char* path, SDL_Renderer* renderer);
	void Shutdown(SDL_Window* window, SDL_Renderer* renderer);
};