#include "PlatformMobile.h"

PlatformMobile::PlatformMobile(sf::Vector2f position, float speed)
	: Object("./media/stoneHalf.png") {
	m_pos = position;
	m_sprite.setPosition(m_pos);
	m_speed.x = speed;
}

void PlatformMobile::draw (sf::RenderWindow & window) {
	window.draw(m_sprite);
}

void PlatformMobile::update (float dt) {
	m_sprite.move(-m_speed.x * dt, 0.f);
	m_pos += m_speed * dt;
	m_sprite.setTexture(m_texture);
}

