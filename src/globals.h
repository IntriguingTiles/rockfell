#include <unordered_map>
#include <string>
#include <SDL.h>

#include "interfaces.h"
#include "menu.h"
#include "input.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

inline SDL_Window* g_Window = nullptr;
inline SDL_Renderer* g_Renderer = nullptr;
inline IRenderable* g_Renderable = nullptr;
inline IEventListener* g_EventListener = nullptr;

inline std::unordered_map<std::string, SDL_Texture*> textures;

inline CMenu* g_Menu = nullptr;

inline CInput g_Input;