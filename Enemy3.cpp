#include "Enemy3.h"
#include <SFML/Window/Keyboard.hpp>

Enemy3::Enemy3(std::string nameLeft, float pos) : Enemy(nameLeft) {
	m_sprite.setPosition(1000, 470);
	m_pos.x = 1000.f;
	m_pos.y = pos;
	up = true;
}

void Enemy3::update (float dt, Player &p, float coef) {
	m_pos += m_speed;
	m_sprite.setPosition(m_pos);
	
	if(up){
		m_speed.y -= 0.1f;
	} else {
		m_speed.y += 0.1f;
	}
	
	if(m_pos.y <= 50.f){
		up = false;
		m_speed.y = 2.5f;
	}
	if(m_pos.y >= 330.f){
		up = true;
		m_speed.y = -2.5f;
	}
	
	
	m_speed.x -= 0.02f * coef; 
	m_sprite.setTexture(m_texture);
	
}

void Enemy3::draw(sf::RenderWindow &window) {
	if(moveEnemy){
		Object::draw(window);
	}
}

bool Enemy3::collideWithPlayer(Object &o) {
	auto r1 = m_sprite.getGlobalBounds();
	auto r2 = o.getGlobalBounds();
	if (r2.intersects(r1)) {
		return false;
	}
	return false;
}

bool Enemy3::attackPlayer(Object &o) {
	auto r2 = m_sprite.getGlobalBounds();
	auto r1 = o.getGlobalBounds();
	if (r2.intersects(r1)) {
		if (r2.top + r2.height < r1.top + 0.9f * r1.height) {
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
				return true;
			}
		} else {
			return true;
		}
		return false;
	}
	return false;
}


bool Enemy3::collideWithInmortal(Object &o) {
	auto r1 = m_sprite.getGlobalBounds();
	auto r2 = o.getGlobalBounds();
	if (r2.intersects(r1)) {
		if (r2.top + r2.height < r1.top + 0.9f * r1.height) {
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
				return true;
			}
		} else {
			return true;
		}
		return true;
	}
	return false;
}
