#pragma once

#include <vector>
#include <SDL.h>

#include "button.h"
#include "interfaces.h"

class CMenu : public IRenderable, public IEventListener {
	std::vector<CButton> buttons;

	SDL_Rect titleRect;
public:
	CMenu();
	void Render(SDL_Renderer*) override;
	void OnEvent(SDL_Event*) override;
};