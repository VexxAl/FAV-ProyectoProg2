#include "Enemy.h"

#include <SFML/Window/Keyboard.hpp>


Enemy::Enemy(std::string nameLeft,std::string nameRight) : Object(nameLeft), moveEnemy(true),despawnEnemy(false) {
	m_pos.x = 800.f;
	m_pos.y = 470.f;
	m_sprite.setPosition(800, 470);
	rightTex.loadFromFile(nameRight);

	kill_enemy1_buffer.loadFromFile("./media/sounds/kill_enemy1.ogg");
	kill_enemy1_sound.setBuffer(kill_enemy1_buffer);
}

void Enemy::update (float dt, Player p) {
	m_pos += m_speed * dt;
	m_sprite.setPosition(m_pos);
	
	if (m_pos.x < 0) {
		m_pos.x = 0;
		m_speed.x = 0;
	}
	
	if (m_pos.y >= 470.f){
		m_speed.y = 0.0f;
		m_pos.y = 470.f;
	} else {
		m_speed.y += 50.f;
	}
	
	if(p.getPositionx() < m_pos.x) {
		m_speed.x -= 3.f; 
		m_sprite.setTexture(m_texture);
	} else {
		m_speed.x += 3.f;
		m_sprite.setTexture(rightTex);
	}
}

bool Enemy::collideWithPlayer(Object &o) {
	auto r1 = m_sprite.getGlobalBounds();
	auto r2 = o.getGlobalBounds();
	if (r2.intersects(r1)) {
		// Verifica si el jugador esta encima de la plataforma
		if (r2.top + r2.height < r1.top + 0.9f * r1.height) {
			// El jugador cae sobre la plataforma
			kill_enemy1_sound.play();
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

bool Enemy::collideWithInmortal(Object &o) {
	auto r1 = m_sprite.getGlobalBounds();
	auto r2 = o.getGlobalBounds();
	if (r2.intersects(r1)) {
		// Verifica si el jugador est� encima de la plataforma
		if (r2.top + r2.height < r1.top + 0.9f * r1.height) {
			// El jugador cae sobre la plataforma
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

bool Enemy::attackPlayer(Object &o) {
	auto r2 = m_sprite.getGlobalBounds();
	auto r1 = o.getGlobalBounds();
	if (r2.intersects(r1)) {
		// Verifica si el jugador est� encima de la plataforma
		if (r2.top + r2.height < r1.top + 0.9f * r1.height) {
			// El jugador cae sobre la plataforma
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

bool Enemy::getMoveEnemy() const {
	return moveEnemy;
}

void Enemy::setMoveEnemy(bool aux) {
	this->moveEnemy = aux;
}

bool Enemy::getDespawnEnemy() const {
	return despawnEnemy;
}

void Enemy::setDespawnEnemy(bool aux) {
	this->despawnEnemy = aux;
}
