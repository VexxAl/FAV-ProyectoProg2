#include "PlatformMobile.h"

#include <SFML/Window/Keyboard.hpp>


PlatformMobile::PlatformMobile(sf::Vector2f position, float speed, std::string fname)
	: Object(fname) {
	m_pos = position;
	m_sprite.setPosition(m_pos);
	m_speed.x = speed;
	m_sprite.scale(4,4); //vimos tambien en 5
}

void PlatformMobile::update (float dt) {
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
		m_sprite.move(-m_speed.x * dt, 0.f);
		m_pos += m_speed * dt;
	}
	m_sprite.setTexture(m_texture);
}
