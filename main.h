#include "SDL/SDL.h"
#include <string>

#ifndef MAIN
#define MAIN

int GetStringHashcode(std::string);
bool DoSDLRectsCollide(SDL_Rect*, SDL_Rect*);

//GRAPHICS CONTROLLER
class GraphicsController;
class SpriteAnimationFrame;
class SpriteInstance;
class SpriteTemplate;

//WORLD CONTROLLER
class WorldEvent;
class WorldController;
class EntityTemplate;
class EntityInstance;
class PlatformTemplate;
class PlatformInstance;
class Player;
class Trigger;

#endif
