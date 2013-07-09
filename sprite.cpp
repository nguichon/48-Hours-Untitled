#include "graphicscontroller.h"

SpriteTemplate::SpriteTemplate() {
	SpriteTemplate("data/sprites/invalid.sprite");
}

SpriteTemplate::SpriteTemplate(std::string filename) {
	//TODO: MC to write a file-loader
	std::ifstream fileReader( filename.c_str() );

	std::string imagepath;
	getline(fileReader, imagepath);
	m_SpriteImage = GraphicsController::get()->LoadImage(imagepath);

	std::string s;
	while(fileReader.good()) {
		fileReader >> s;
		int animationID = GetStringHashcode(s);

		int x, y, w, h; long d;

		fileReader >> d;
		fileReader >> x;
		fileReader >> y;
		fileReader >> w;
		fileReader >> h;

		if(m_Animations.find(animationID) == m_Animations.end()) {
			m_Animations[animationID] = SpriteAnimationFrame();
			m_Animations[animationID].frameCoordinates.x = x;
			m_Animations[animationID].frameCoordinates.y = y;
			m_Animations[animationID].frameCoordinates.w = w;
			m_Animations[animationID].frameCoordinates.h = h;
			m_Animations[animationID].frameDuration = d;
		} else {
			SpriteAnimationFrame* f;
			f = &m_Animations[animationID];
			while(f->nextFrame != NULL) {
				f = f->nextFrame;
			}
			f->nextFrame = new SpriteAnimationFrame();
			f = f->nextFrame;
			f->frameCoordinates.x = x;
			f->frameCoordinates.y = y;
			f->frameCoordinates.w = w;
			f->frameCoordinates.h = h;
			f->frameDuration = d;

		}

	}

	fileReader.close();
}

SpriteInstance SpriteTemplate::CreateSprite() {
	SpriteInstance sprite = SpriteInstance(this);
	sprite.ChangeAnimation("stand");
	sprite.xLocation = -1; sprite.yLocation = -1;

	return sprite;
}

SDL_Surface* SpriteTemplate::GetImage() {
	return m_SpriteImage;
}

SpriteAnimationFrame* SpriteTemplate::GetAnimation(int animationID) {
	return &m_Animations[animationID];
}

SpriteInstance::SpriteInstance(SpriteTemplate* base) {
	m_BaseSprite = base;
}

void SpriteInstance::ChangeAnimation(std::string animationName) {
	ChangeAnimation(GetStringHashcode(animationName));
}

void SpriteInstance::ChangeAnimation(int animationID) {
	m_CurrentFrame = m_BaseSprite->GetAnimation(animationID);
	m_ElapsedTime = 0; m_CurrentAnimation = animationID;
}

int SpriteInstance::GetWidth() {
	return m_CurrentFrame->frameCoordinates.x;
}

SpriteAnimationFrame* SpriteInstance::GetFrame() {
	return m_CurrentFrame;
}

SDL_Surface* SpriteInstance::GetImage() {
	return m_BaseSprite->GetImage();
}

void SpriteInstance::Update(long time) {
	m_ElapsedTime += time;
	if (m_ElapsedTime > m_CurrentFrame->frameDuration && m_CurrentFrame->frameDuration != -1) {
		m_ElapsedTime = 0;
		m_CurrentFrame = m_CurrentFrame->nextFrame;
		if(m_CurrentFrame == NULL) { m_CurrentFrame = m_BaseSprite->GetAnimation(m_CurrentAnimation); }
	}
}

/*SpriteAnimationFrame::SpriteAnimationFrame(long dur, int x, int y, int w, int h) {
	frameDuration = dur;
	frameCoordinates.x = x;
	frameCoordinates.y = y;
	frameCoordinates.w = w;
	frameCoordinates.h = h;
}*/
