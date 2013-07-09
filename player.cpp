#include "worldcontroller.h"
#include "graphicscontroller.h"


Player::Player(std::string spritefile) {
	m_PositionX = 0.0; m_PositionY = 0.0; m_VelocityX = 0.0; m_VelocityY = 1.0;
	m_Sprite = GraphicsController::get()->CreateSprite(spritefile);
	m_Sprite->xLocation = m_PositionX; m_Sprite->yLocation = m_PositionY;
}

void Player::Update(long time) {
	m_PositionX += m_VelocityX;
	m_PositionY += 2;
	//m_Sprite->xLocation = m_PositionX; m_Sprite->yLocation = 50;
	delete m_Sprite;
}

