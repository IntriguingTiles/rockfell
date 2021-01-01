#include <unordered_map>
#include <string>
#include <SDL.h>

#include "interfaces.h"
#include "menu.h"
#include "rockfell.h"
#include "input.h"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

struct Globals {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	IRenderable* renderable = nullptr;
	IEventListener* eventListener = nullptr;
	IUpdateable* updateable = nullptr;
	std::unordered_map<std::string, SDL_Texture*> textures;
	CMenu* menu = nullptr;
	CRockfell* rockfell = nullptr;
	CInput input;
};

inline Globals g_Globals;