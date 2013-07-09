#include "main.h"
#include "graphicscontroller.h"
#include "worldcontroller.h"

int main( int argc, char* args[] )
{
	SDL_Init(SDL_INIT_EVERYTHING);

	GraphicsController::get();
	WorldController::get();
	WorldController::get()->CreatePlatform("data/platforms/test.platform", 0, 320);
	WorldController::get()->CreatePlatform("data/platforms/test.platform", 900, 230);
	WorldController::get()->CreatePlatform("data/platforms/test.platform", 600, 260);
	WorldController::get()->CreatePlatform("data/platforms/test.platform", 300, 290);
	WorldController::get()->CreatePlatform("data/platforms/test.platform", 1200, 200);

	SDL_Event event;
	bool isLeft = false, isRight = false;
	bool quit = false;

	while(!quit) {
		if(SDL_PollEvent( &event ) == 1) {
			switch(event.type) {
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					switch( event.key.keysym.sym )
	                {
	                    case SDLK_LEFT: isLeft = true; break;
	                    case SDLK_RIGHT: isRight = true; break;
	                }
					break;
				case SDL_KEYUP:
					switch( event.key.keysym.sym )
					{
						case SDLK_LEFT: isLeft = false; break;
						case SDLK_RIGHT: isRight = false; break;
					}
					break;
			}
		}
		GraphicsController::get()->UpdateAndRenderAll(33);
		WorldController::get()->Update(33);
		//GraphicsController::get()->RenderAll();
		SDL_Delay(33);
		if(isRight) { GraphicsController::get()->AdvanceCamera(1); }
		if(isLeft) { GraphicsController::get()->AdvanceCamera(-1); }
	}

	SDL_Quit();
	return 0;
}

int GetStringHashcode(std::string toHash) {
	int hash = 0;
	for (unsigned int i = 0; i < toHash.length(); i++) {
		hash = 31*hash + toHash.c_str()[i];
	}
	return hash;
}

bool DoSDLRectsCollide(SDL_Rect* A, SDL_Rect* B) {
	//The sides of the rectangles
	unsigned int LeftA, LeftB;
	unsigned int RightA, RightB;
	unsigned int TopA, TopB;
	unsigned int BottomA, BottomB;

	//Get the sizes from the SDL_Rect structs - Rect A
	LeftA = A->x;
	RightA = A->x + A->w;
	TopA = A->y;
	BottomA = A->y + A->h;

	//Get the sizes from the SDL_Rect structs - Rect B
	LeftB = B->x;
	RightB = B->x + B->w;
	TopB = B->y;
	BottomB = B->y + B->h;


	if( (BottomA <= TopB) || (TopA >= BottomB) || (RightA <= LeftB) || (LeftA >= RightB) )
	      return false;

	else
	{
	      return true;
	}

}
