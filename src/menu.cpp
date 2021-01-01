#include <memory>
#include <SDL.h>

#include "menu.h"
#include "button.h"
#include "globals.h"

CMenu::CMenu() {
	SDL_Rect startRect;
	SDL_Rect quitRect;

	startRect.x = SCREEN_WIDTH / 2 - 64;
	startRect.y = SCREEN_HEIGHT / 2 + 32;
	startRect.w = 128;
	startRect.h = 64;

	quitRect.x = SCREEN_WIDTH / 2 - 64;
	quitRect.y = SCREEN_HEIGHT / 2 + 128;
	quitRect.w = 128;
	quitRect.h = 64;

	titleRect.x = SCREEN_WIDTH / 2 - 256;
	titleRect.y = SCREEN_HEIGHT / 2 - 256;
	titleRect.w = 256 * 2;
	titleRect.h = 64 * 2;

	buttons.push_back(std::make_unique<CButton>(startRect, g_Globals.textures["start"], []() {
		g_Globals.renderable = g_Globals.rockfell;
		g_Globals.updateable = g_Globals.rockfell;
		g_Globals.eventListener = nullptr;
	}));

	buttons.push_back(std::make_unique<CButton>(quitRect, g_Globals.textures["quit"], []() {
		SDL_Event e;
		e.type = SDL_QUIT;

		SDL_PushEvent(&e);
	}));
}

void CMenu::Render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, g_Globals.textures["title"], nullptr, &titleRect);

	for (auto& button : buttons) {
		button->Render(renderer);
	}
}

void CMenu::OnEvent(SDL_Event* e) {
	for (auto& button : buttons) {
		button->OnEvent(e);
	}
}