#include "worldcontroller.h"
#include "graphicscontroller.h"

PlatformTemplate::PlatformTemplate() {
	SpriteTemplate("data/platforms/invalid.sprite");
}
PlatformTemplate::PlatformTemplate(std::string filename) {
	//TODO: MC to write a file-loader
	std::ifstream fileReader( filename.c_str() );

	fileReader >> m_SpriteBase;
	fileReader >> m_Width;
	fileReader >> m_Height;

	fileReader.close();
}

PlatformInstance PlatformTemplate::CreatePlatform(int x, int y) {
	return PlatformInstance(this, x, y, m_Width, m_Height, &m_SpriteBase);
}

PlatformInstance::PlatformInstance(PlatformTemplate* base, int xPosition, int yPosition, int width, int height, std::string* p_SpriteTemplate) {
	m_BasePlatform = base;

	m_CollisionBox.x = xPosition;
	m_CollisionBox.y = yPosition;
	m_CollisionBox.w = width;
	m_CollisionBox.h = height;

	m_Sprite = GraphicsController::get()->CreateSprite(*p_SpriteTemplate);
	m_Sprite->xLocation = m_CollisionBox.x; m_Sprite->yLocation = m_CollisionBox.y;
}
