#include <stdio.h>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <SDL.h>
#include <SDL_image.h>

#ifdef __WIIU__
#include <whb/proc.h>
#endif

#include "sdl_goop.h"
#include "globals.h"
#include "menu.h"
#include "rockfell.h"

bool isRunning = false;

bool running() {
#ifdef __WIIU__
	return WHBProcIsRunning();
#else
	return isRunning;
#endif
}

int main(int, char**) {
	CSDLGoop sdl;

	char title[64];
	snprintf(title, sizeof(title), "Rockfell (%s %s)", ROCKFELL_GIT_BRANCH, ROCKFELL_GIT_HASH);

	if (!std::filesystem::exists("data")) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Rockfell", "Data directory not found.", nullptr);
		return -1;
	}

	if (!sdl.Init(&g_Window, &g_Renderer, title, "data/icon.png", SCREEN_WIDTH, SCREEN_HEIGHT)) {
		char buf[128];
		snprintf(buf, sizeof(buf), "Failed to initialize SDL: %s", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Rockfell", buf, nullptr);
		sdl.Shutdown(g_Window, g_Renderer);
		return -1;
	}

	for (const auto& file : std::filesystem::directory_iterator("data/textures")) {
		textures[file.path().stem().string()] = sdl.LoadTexture(file.path().string().c_str(), g_Renderer);

		if (!textures[file.path().stem().string()]) {
			char buf[128];
			snprintf(buf, sizeof(buf), "Failed to load texture: %s", SDL_GetError());
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Rockfell", buf, nullptr);
			sdl.Shutdown(g_Window, g_Renderer);
			return -1;
		}
	}

#ifdef __WIIU__
	WHBProcInit();
#endif

	g_Menu = new CMenu;
	g_Rockfell = new CRockfell;
	g_EventListener = g_Menu;
	g_Renderable = g_Menu;

	isRunning = true;
	SDL_Event e;

	auto thread = SDL_CreateThread([](void*) {
		// this is really dumb and we will likely run into problems in the future but it works for now
		while (running()) {
			if (g_Updateable) g_Updateable->Update();
		}

		return 0;
	}, "update", nullptr);

	while (running()) {
		while (SDL_PollEvent(&e)) {
#ifdef __WIIU__
			if (e.type == SDL_QUIT) WHBProcStopRunning();
#else
			if (e.type == SDL_QUIT) isRunning = false;
#endif
			g_Input.OnEvent(&e);
			if (g_EventListener) g_EventListener->OnEvent(&e);
		}

		SDL_RenderClear(g_Renderer);
		g_Renderable->Render(g_Renderer);
		SDL_RenderPresent(g_Renderer);
	}

	SDL_WaitThread(thread, nullptr);

	for (const auto& texture : textures) {
		SDL_DestroyTexture(texture.second);
	}

	delete g_Menu;
	delete g_Rockfell;

#ifdef __WIIU__
	WHBProcShutdown();
#endif

	sdl.Shutdown(g_Window, g_Renderer);
	return 0;
}