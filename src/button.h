#pragma once

#include <functional>
#include <SDL.h>

#include "interfaces.h"

class CButton : public IRenderable, public IEventListener {
	SDL_Rect rect;
	SDL_Texture* texture = nullptr;
	std::function<void()> callback = nullptr;
	bool hovered = false;
	bool pressed = false;

	bool IsInRect(int x, int y);
public:
	CButton(SDL_Rect rect, SDL_Texture* texture, std::function<void()> callback);
	void Render(SDL_Renderer* renderer) override;
	void OnEvent(SDL_Event* e) override;
};