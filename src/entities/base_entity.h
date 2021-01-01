#pragma once

#include <SDL.h>

#include "interfaces.h"

class CBaseEntity : public IRenderable, public IUpdateable {
protected:
	SDL_Rect rect;
	SDL_Texture* texture = nullptr;
public:
	CBaseEntity(SDL_Texture* texture);
	virtual void Update() override = 0;
	virtual void Render(SDL_Renderer* renderer) override;
	void Move(int x, int y);
};