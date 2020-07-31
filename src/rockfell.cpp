#include <SDL.h>
#include <memory>

#include "globals.h"
#include "rockfell.h"
#include "entities/player.h"

CRockfell::CRockfell() {
	entities.push_back(std::make_unique<CPlayer>(textures["player"]));
}

void CRockfell::Render(SDL_Renderer* renderer) {
	for (auto& entity : entities) {
		entity->Render(renderer);
	}
}

void CRockfell::Update() {
	for (auto& entity : entities) {
		entity->Update();
	}
}