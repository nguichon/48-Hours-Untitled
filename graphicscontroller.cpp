#include "graphicscontroller.h"

GraphicsController::GraphicsController() {
	 m_Window = SDL_SetVideoMode(1000, 400, 32, SDL_SWSURFACE );
	 m_Background = LoadImage("resources/images/background.bmp");
}

GraphicsController* GraphicsController::get() {
	static GraphicsController* instance;
	if (instance == NULL) {
		instance = new GraphicsController();
	}
	return instance;
}

void GraphicsController::AdvanceCamera(int distance) {
	m_CameraDisplacement += distance;
}

int GraphicsController::LoadSprite(std::string filename) {
	//TODO: MC to write a file-loader
	int hashedFilename = GetStringHashcode(filename);
	m_LoadedSpriteTemplates[hashedFilename] = SpriteTemplate(filename);

	return hashedFilename;
}

SpriteInstance* GraphicsController::CreateSprite(std::string filename) {
	//TODO: MC to write a file-loader
	int hashedFilename = GetStringHashcode(filename);

	if(m_LoadedSpriteTemplates.find(hashedFilename) == m_LoadedSpriteTemplates.end()) {
		LoadSprite(filename);
	}

	m_SpritesInPlay.push_back(m_LoadedSpriteTemplates[hashedFilename].CreateSprite());
	return &m_SpritesInPlay.back();
}

SDL_Surface* GraphicsController::LoadImage(std::string filepath) {
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;

	loadedImage = SDL_LoadBMP( filepath.c_str());

	if( loadedImage != NULL )
	{
		optimizedImage = SDL_DisplayFormat( loadedImage );
		SDL_FreeSurface( loadedImage );
	}

	return optimizedImage;
}

void GraphicsController::UpdateAndRenderAll(long time) {
	//SDL_FillRect(m_Window, &m_Window->clip_rect, 0);
	SDL_Rect* zero = new SDL_Rect;
	zero->x = 0;
	zero->y = 0;
	zero->w = 1000;
	zero->h = 400;
	SDL_BlitSurface(m_Background, zero, m_Window, zero);

	std::vector<SpriteInstance>::iterator iterator;
	for ( iterator = m_SpritesInPlay.begin(); iterator != m_SpritesInPlay.end(); ++iterator ) {
		/*if(m_CameraDisplacement < iterator->xLocation + iterator->GetWidth()
				&& m_CameraDisplacement + 1000 > iterator->xLocation) {*/
			iterator->Update(time);
			SDL_Rect* source = &(iterator->GetFrame()->frameCoordinates);
			SDL_Rect* target = new SDL_Rect;
			target->x = iterator->xLocation - m_CameraDisplacement;
			target->y = iterator->yLocation;
			target->w = 0; target-> h = 0;

			SDL_BlitSurface(iterator->GetImage(), source, m_Window, target);
		//}
	}

	SDL_Flip(m_Window);
}
