#include <stdio.h>
#include <iostream>
#include <filesystem>
#include <SDL.h>
#include <SDL_image.h>

#include "sdl_goop.h"
#include "globals.h"

int main(int, char**) {
	CSDLGoop sdl;

	char title[64];
	snprintf(title, sizeof(title), "Rockfell (%s %s)", ROCKFELL_GIT_BRANCH, ROCKFELL_GIT_HASH);

	if (!sdl.Init(&g_Window, &g_Renderer, title, SCREEN_WIDTH, SCREEN_HEIGHT)) {
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

	g_Menu = new CMenu;
	g_EventListener = g_Menu;
	g_Renderable = g_Menu;

	bool running = true;
	SDL_Event e;

	while (running) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) running = false;
			g_Input.OnEvent(&e);
			g_EventListener->OnEvent(&e);
		}

		SDL_RenderClear(g_Renderer);
		g_Renderable->Render(g_Renderer);
		SDL_RenderPresent(g_Renderer);
	}

	for (const auto& texture : textures) {
		SDL_DestroyTexture(texture.second);
	}

	delete g_Menu;

	sdl.Shutdown(g_Window, g_Renderer);
	return 0;
}