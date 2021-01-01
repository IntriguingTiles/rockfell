#include <stdio.h>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <SDL.h>
#include <SDL_image.h>

#ifdef __WIIU__
#include <whb/proc.h>
#include <romfs-wiiu.h>
#define DATA_DIR "romfs:/"
#else
#define DATA_DIR "data/"
#endif

#include "sdl_goop.h"
#include "globals.h"
#include "menu.h"
#include "rockfell.h"

int main(int, char**) {
	CSDLGoop sdl;

#ifdef __WIIU__
	WHBProcInit();
	romfsInit();
#endif

	char title[64];
	snprintf(title, sizeof(title), "Rockfell (%s %s)", ROCKFELL_GIT_BRANCH, ROCKFELL_GIT_HASH);

	if (!std::filesystem::exists(DATA_DIR)) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Rockfell", "Data directory not found.", nullptr);
		return -1;
	}

	if (!sdl.Init(&g_Globals.window, &g_Globals.renderer, title, DATA_DIR "icon.png", SCREEN_WIDTH, SCREEN_HEIGHT)) {
		char buf[128];
		snprintf(buf, sizeof(buf), "Failed to initialize SDL: %s", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Rockfell", buf, nullptr);
		sdl.Shutdown(g_Globals.window, g_Globals.renderer);
		return -1;
	}

	for (const auto& file : std::filesystem::directory_iterator(DATA_DIR "textures")) {
		g_Globals.textures[file.path().stem().string()] = sdl.LoadTexture(file.path().string().c_str(), g_Globals.renderer);

		if (!g_Globals.textures[file.path().stem().string()]) {
			char buf[128];
			snprintf(buf, sizeof(buf), "Failed to load texture: %s", SDL_GetError());
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Rockfell", buf, nullptr);
			sdl.Shutdown(g_Globals.window, g_Globals.renderer);
			return -1;
		}
	}

	g_Globals.menu = new CMenu;
	g_Globals.rockfell = new CRockfell;
	g_Globals.eventListener = g_Globals.menu;
	g_Globals.renderable = g_Globals.menu;

	bool running = true;
	SDL_Event e;

#ifdef __WIIU__
	auto thread = SDL_CreateThread([](void*) {
		// on the wii u, v-sync is enforced which means rendering takes longer to complete than we're expecting, this works for now.
		while (WHBProcIsRunning()) {
			if (g_Globals.updateable) g_Globals.updateable->Update();
		}

		return 0;
	}, "update", nullptr);

	while (WHBProcIsRunning()) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) WHBProcStopRunning();
#else
	while (running) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) running = false;
#endif
			g_Globals.input.OnEvent(&e);
			if (g_Globals.eventListener) g_Globals.eventListener->OnEvent(&e);
		}

		SDL_RenderClear(g_Globals.renderer);
		g_Globals.renderable->Render(g_Globals.renderer);
		SDL_RenderPresent(g_Globals.renderer);
#ifndef __WIIU__
		if (g_Globals.updateable) g_Globals.updateable->Update();
#endif
	}

#ifdef __WIIU__
	SDL_WaitThread(thread, nullptr);
#endif

	for (const auto& texture : g_Globals.textures) {
		SDL_DestroyTexture(texture.second);
	}

	delete g_Globals.menu;
	delete g_Globals.rockfell;

#ifdef __WIIU__
	romfsExit();
	WHBProcShutdown();
#endif

	sdl.Shutdown(g_Globals.window, g_Globals.renderer);
	return 0;
}