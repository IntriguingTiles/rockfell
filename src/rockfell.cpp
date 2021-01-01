#include <SDL.h>
#include <memory>
#include <iterator>

#include "globals.h"
#include "rockfell.h"
#include "entities/player.h"

CRockfell::CRockfell() {
	entities.push_back(std::make_unique<CPlayer>(g_Globals.textures["player"]));
}

void CRockfell::Render(SDL_Renderer* renderer) {
	for (auto& entity : entities) {
		entity->Render(renderer);
	}
}

void CRockfell::Update() {
	for (auto& entity : entities) {
		if (entity->nextUpdate <= SDL_GetTicks()) entity->Update();
	}
	
	if (!pending.empty()) {
		std::move(std::begin(pending), std::end(pending), std::back_inserter(entities));
		pending.clear();
	}
}