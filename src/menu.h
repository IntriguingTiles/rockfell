#pragma once

#include <vector>
#include <memory>
#include <SDL.h>

#include "button.h"
#include "interfaces.h"

class CMenu : public IRenderable, public IEventListener {
	std::vector<std::unique_ptr<CButton>> buttons;

	SDL_Rect titleRect;
public:
	CMenu();
	void Render(SDL_Renderer*) override;
	void OnEvent(SDL_Event*) override;
};