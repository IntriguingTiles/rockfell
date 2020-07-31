#pragma once

#include <vector>
#include <memory>

#include "interfaces.h"
#include "entities/base_entity.h"

class CRockfell : public IRenderable, public IUpdateable {
	std::vector<std::unique_ptr<CBaseEntity>> entities;
public:
	CRockfell();
	void Render(SDL_Renderer*) override;
	void Update() override;
};