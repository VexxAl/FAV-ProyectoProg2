#include "Enemy1.h"

#include <SFML/Window/Keyboard.hpp>


Enemy1::Enemy1(std::string nameLeft,std::string nameRight , sf::Vector2f pos) : Enemy(nameLeft) {
	m_pos.x = pos.x;
	m_pos.y = pos.y;
	m_sprite.setPosition(pos);
	rightTex.loadFromFile(nameRight);
}

void Enemy1::update (float dt, Player &p, float coef) {
	m_pos += m_speed * dt;
	m_sprite.setPosition(m_pos);
	
	if (m_pos.x < 0) {
		m_pos.x = 0;
		m_speed.x = 0;
	}
	
	if (m_pos.y >= 465.f){
		m_speed.y = 0.0f;
		m_pos.y = 465.f;
	} else {
		m_speed.y += 50.f;
	}
	
	if(p.getPositionx() < m_pos.x) {
		m_speed.x -= 3.f * coef; 
		m_sprite.setTexture(m_texture);
	} else {
		m_speed.x += 3.f * coef;
		m_sprite.setTexture(rightTex);
	}
}

bool Enemy1::collideWithPlayer(Object &o) {
	auto r1 = m_sprite.getGlobalBounds();
	auto r2 = o.getGlobalBounds();
	if (r2.intersects(r1)) {
		if (r2.top + r2.height < r1.top + 0.9f * r1.height) {
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
				m_pos.y = m_pos.y + 30.f;
				m_sprite.setPosition(m_pos);
				m_sprite.setScale(1.2f,0.3f);
				return true;
			}
		} 
		else {
			return false;
		}
		return false;
	}
	return false;
}

bool Enemy1::collideWithInmortal(Object &o) {
	auto r1 = m_sprite.getGlobalBounds();
	auto r2 = o.getGlobalBounds();
	if (r2.intersects(r1)) {
		if (r2.top + r2.height < r1.top + 0.9f * r1.height) {
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
				m_pos.y = m_pos.y + 30.f;
				m_sprite.setPosition(m_pos);
				m_sprite.setScale(1.2f,0.3f);
				return true;
			}
		} else {
			m_pos.y = m_pos.y + 30.f;
			m_sprite.setPosition(m_pos);
			m_sprite.setScale(1.2f,0.3f);
			return true;
		}
		return true;
	}
	return false;
}

bool Enemy1::attackPlayer(Object &o) {
	auto r2 = m_sprite.getGlobalBounds();
	auto r1 = o.getGlobalBounds();
	if (r2.intersects(r1)) {
		if (r2.top + r2.height < r1.top + 0.9f * r1.height) {
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
				return false;
			}
		} else {
			return true;
		}
		return false;
	}
	return false;
}
