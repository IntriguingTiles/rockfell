#pragma once

#include <SDL.h>

#include "interfaces.h"

struct Keys {
	bool left, right, jump, attack;
};

class CInput : public IEventListener {
public:
	Keys keys = {};
	void OnEvent(SDL_Event* e) override;
};