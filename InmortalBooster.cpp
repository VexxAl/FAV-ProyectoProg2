#include "InmortalBooster.h"


InmortalBooster::InmortalBooster(sf::Vector2f position, float speed, std::string fname) : taken(false), speed(speed), Object(fname), posSprite(400.f, 10.f) {
	m_sprite.setPosition(position);
	m_pos = position;
	topRightTexture.loadFromFile("./media/images/Repost-Booster.png");
	topRightSprite.setPosition(posSprite);
	
}

void InmortalBooster::setTakenB(bool taken){
	this->taken = taken;
}

void InmortalBooster::update (float dt) {
	m_sprite.move(speed * dt, 0.f);
	m_sprite.setTexture(m_texture);	
	topRightSprite.setTexture(topRightTexture);
}


