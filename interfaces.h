#pragma once

#include <SDL.h>

class IRenderable {
public:
	virtual void Render(SDL_Renderer*) = 0;
};

class IEventListener {
public:
	virtual void Update(SDL_Event*) = 0;
};