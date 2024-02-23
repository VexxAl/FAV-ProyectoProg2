#include "Coin.h"

Coin::Coin(sf::Vector2f position, float speed, std::string fname)
	: taken(false), speed(speed), Object(fname) {
	m_sprite.setPosition(position);
	m_pos = position;
}

bool Coin::isTaken() const {
	return taken;
}

void Coin::setTaken(bool taken) {
	this->taken = taken;
}

void Coin::update(float dt) {
	m_sprite.move(speed * dt, 0.f);
	m_sprite.setTexture(m_texture);
}
