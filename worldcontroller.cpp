#include "worldcontroller.h"

WorldController::WorldController() {
	m_PlayerEntity = new Player("data/sprites/player.sprite");
}

WorldController* WorldController::get() {
	static WorldController* instance;
	if (instance == NULL) {
		instance = new WorldController();
	}
	return instance;
}

void WorldController::CreatePlatform(std::string filename, int x, int y) {
	int hashcode = GetStringHashcode(filename);

	if(m_LoadedPlatfromTemplates.find(hashcode) == m_LoadedPlatfromTemplates.end()) {
		m_LoadedPlatfromTemplates[hashcode] = PlatformTemplate(filename);
	}

	m_PlatformsInPlay.push_back(m_LoadedPlatfromTemplates[hashcode].CreatePlatform(x, y));
}

void WorldController::Update(long time) {
	m_PlayerEntity->Update(time);
}
