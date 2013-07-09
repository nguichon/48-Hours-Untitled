#include "main.h"
#include <fstream>
#include <map>
#include <vector>

#ifndef WORLD
#define WORLD

struct WorldEvent {
	int message;
	double value;
}; //0:React, 1:Take damage

class WorldController {
private:
	std::map<int,EntityTemplate> m_LoadedEntityTemplates;
	std::vector<EntityInstance>  m_EntitiesInPlay;

	std::map<int,PlatformTemplate> m_LoadedPlatfromTemplates;
	std::vector<PlatformInstance> m_PlatformsInPlay;

	Player* m_PlayerEntity;

	WorldController();
public:
	static WorldController* get();

	void CreateEntity(std::string, int, int, int); //template, x position, y position, facing
	void CreatePlatform(std::string, int, int); //template, x position, y position

	void Update(long);
};

class EntityTemplate {
private:
	int m_MaxLife, m_Damage; bool m_Flying; double m_Speed;
	std::string m_SpriteBase;
	int width, height;
public:
	EntityTemplate(std::string);
	EntityInstance* CreateEntity();
};

class EntityInstance {
private:
	EntityTemplate* m_BaseEntity; SpriteInstance* m_Sprite;
	int m_Life;
	double m_XLocation, m_YLocation, m_XSpeed, m_YSpeed;
	SDL_Rect m_CollisionBox;
public:
	EntityInstance(EntityTemplate*);
	void ReceiveMessage(WorldEvent);

	bool CheckCollision(EntityInstance*);
	bool CheckCollision(Player*);
	SDL_Rect GetCollisionBox();
	double GetAngleOfAttack(); //0 is LEFT, 90 is UP

	int getXPosition();
	int getYPosition();
};

class PlatformTemplate {
private:
	std::string m_SpriteBase;
	int m_Width, m_Height;
public:
	PlatformTemplate();
	PlatformTemplate(std::string);
	PlatformInstance CreatePlatform(int,int);
};

class PlatformInstance {
private:
	PlatformTemplate* m_BasePlatform; SpriteInstance* m_Sprite;
	SDL_Rect m_CollisionBox;
public:
	PlatformInstance(PlatformTemplate*, int, int, int, int, std::string*);

	int CheckCollision(Player*);
	int CheckCollision(EntityInstance*);
};

class Player {
private:
	SpriteInstance* m_Sprite;
	double m_PositionX, m_PositionY, m_VelocityX, m_VelocityY;
	SDL_Rect m_CollisionBox;
public:
	Player(std::string);
	void Update(long);
};

#endif
