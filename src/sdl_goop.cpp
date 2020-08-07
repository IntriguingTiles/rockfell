#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#ifdef WIN32
#include <Windows.h>
#endif

#include "sdl_goop.h"

bool CSDLGoop::Init(SDL_Window** window, SDL_Renderer** renderer, const char* title, const char* iconPath, int w, int h) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) == -1) return false;
	if (!IMG_Init(IMG_INIT_PNG)) return false;

	for (int i = 0; i < SDL_NumJoysticks(); i++) {
#ifdef __WIIU__
		auto controller = SDL_JoystickOpen(i);
#else
		auto controller = SDL_GameControllerOpen(i);
#endif
		controllers.push_back(controller);
	}

#ifdef WIN32
	void* shcoreDLL = SDL_LoadObject("SHCORE.DLL");
	void* userDLL = SDL_LoadObject("USER32.DLL");
	BOOL(WINAPI * SetProcessDPIAware)(void) = nullptr;
	HRESULT(WINAPI * SetProcessDpiAwareness)(int awareness) = nullptr;

	if (shcoreDLL) {
		SetProcessDpiAwareness = (HRESULT(WINAPI*)(int)) SDL_LoadFunction(shcoreDLL, "SetProcessDpiAwareness");
	}

	if (userDLL) {
		SetProcessDPIAware = (BOOL(WINAPI*)(void)) SDL_LoadFunction(userDLL, "SetProcessDPIAware");
	}

	if (SetProcessDpiAwareness) {
		SetProcessDpiAwareness(2);
	} else if (SetProcessDPIAware) {
		SetProcessDPIAware();
	}
#endif

	*window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_ALLOW_HIGHDPI);
	if (!*window) return false;

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
	if (!*renderer) return false;

	SDL_SetRenderDrawColor(*renderer, 0x00, 0x00, 0x00, 0xFF);

	auto* icon = IMG_Load(iconPath);

	SDL_SetWindowIcon(*window, icon);
	SDL_FreeSurface(icon);

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
	for (auto& controller : controllers) {
#ifdef __WIIU__
		SDL_JoystickClose(controller);
#else
		SDL_GameControllerClose(controller);
#endif
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}