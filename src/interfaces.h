#pragma once

#include <SDL.h>

class IRenderable {
public:
	virtual void Render(SDL_Renderer*) = 0;
	virtual ~IRenderable() {};
};

class IEventListener {
public:
	virtual void OnEvent(SDL_Event*) = 0;
	virtual ~IEventListener() {};
};

class IUpdateable {
public:
	virtual void Update() = 0;
	virtual ~IUpdateable() {};
};