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

	CButton startButton(startRect, textures["start"], []() {
		printf("Start!\n");
	});

	CButton quitButton(quitRect, textures["quit"], []() {
		SDL_Event e;
		e.type = SDL_QUIT;

		SDL_PushEvent(&e);
	});

	buttons.push_back(startButton);
	buttons.push_back(quitButton);
}

void CMenu::Render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, textures["title"], nullptr, &titleRect);

	for (auto& button : buttons) {
		button.Render(renderer);
	}
}

void CMenu::Update(SDL_Event* e) {
	for (auto& button : buttons) {
		button.Update(e);
	}
}