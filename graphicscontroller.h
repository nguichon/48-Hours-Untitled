#include "main.h"
#include <fstream>
#include <map>
#include <vector>

#ifndef GRAPHICS
#define GRAPHICS

class GraphicsController {
private:
	std::map<int,SDL_Surface*> m_LoadedImageFiles;
	std::map<int,SpriteTemplate> m_LoadedSpriteTemplates;

	std::vector<SpriteInstance> m_SpritesInPlay;
	SDL_Surface* m_Window; int m_CameraDisplacement;
	SDL_Surface* m_Background;

	GraphicsController();
public:
	static GraphicsController* get();

	SDL_Surface* LoadImage(std::string);
	int LoadSprite(std::string); //Returns the hashed string, NO sprite is loaded if sprite ALREADY EXISTS
	SpriteInstance* CreateSprite(std::string); //Returns a reference to the created sprite
	void DestroySprite(SpriteInstance*);

	void AdvanceCamera(int);
	int GetCameraDistance();
	void UpdateAndRenderAll(long);
};

class SpriteTemplate {
private:
	SDL_Surface* m_SpriteImage;
	std::map<int,SpriteAnimationFrame> m_Animations;
public:
	SpriteTemplate();
	SpriteTemplate(std::string);
	SpriteInstance CreateSprite();

	SpriteAnimationFrame* GetAnimation(std::string);
	SpriteAnimationFrame* GetAnimation(int);

	SDL_Surface* GetImage();
};

class SpriteInstance {
	SpriteTemplate* m_BaseSprite;

	SpriteAnimationFrame* m_CurrentFrame;
	int m_CurrentAnimation; int m_ElapsedTime; int m_NextAnimation;
public:
	SpriteInstance( SpriteTemplate* );
	void Update( long );
	int xLocation, yLocation; bool obsolete;
	int GetWidth();
	SpriteAnimationFrame* GetFrame();

	void ChangeAnimation( std::string );
	void ChangeAnimation( int );

	SDL_Surface* GetImage();
};



struct SpriteAnimationFrame {
	SDL_Rect frameCoordinates;
	long frameDuration;
	SpriteAnimationFrame* nextFrame;

	//SpriteAnimationFrame();
	//SpriteAnimationFrame(long,int,int,int,int);
};

#endif
