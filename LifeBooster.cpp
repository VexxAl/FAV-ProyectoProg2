#include "LifeBooster.h"

LifeBooster::LifeBooster(sf::Vector2f position, float speed, std::string fname) : taken(false), speed(speed), Object(fname) {
	m_sprite.setPosition(position);
	m_pos = position;
	
}

void LifeBooster::setTakenB(bool taken){
	this->taken = taken;
}

void LifeBooster::update (float dt) {
	m_sprite.move(speed * dt, 0.f);
	m_sprite.setTexture(m_texture);	
}

