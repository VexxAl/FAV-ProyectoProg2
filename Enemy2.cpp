#include "Enemy2.h"

#include <SFML/System/Vector2.hpp>


Enemy2::Enemy2(std::string nameLeft, std::string nameRight, std::string nameBulletLeft, std::string nameBulletRight) : Enemy(nameLeft, nameRight) {
	m_pos.x = 800.f;
	m_pos.y = 420.f;
	m_sprite.setPosition(800, 425);
	rightTex.loadFromFile(nameRight);
	m_sprite.setScale(1.7,1.7);
	BulletTexLeft.loadFromFile(nameBulletLeft);
	BulletTexRight.loadFromFile(nameBulletRight);
	Bullet.setTexture(BulletTexLeft);

	kill_enemy2_buffer.loadFromFile("./media/sounds/kill_enemy2.ogg");
	kill_enemy2_sound.setBuffer(kill_enemy2_buffer);

	shot_buffer.loadFromFile("./media/sounds/shot.wav");
	shot_sound.setBuffer(shot_buffer);
}

void Enemy2::update(float dt, Player &p) {
	m_pos += m_speed * dt;
	m_sprite.setPosition(m_pos);
	
	if (m_pos.x < 0) {
		m_pos.x = 0;
		m_speed.x = 0;
	}
	
	if (rand() % 50 == 1 && m_pos.y == 425.f) {
		m_speed.y = -1500.f; 
	} else if (m_pos.y >= 425.f){
		m_speed.y = 0.0f;
		m_pos.y = 425.f;
	} else {
		m_speed.y += 50.f;
	}
	
	if (p.getPositionx() < m_pos.x) {
		m_speed.x -= 2.f;
		m_sprite.setTexture(m_texture);
		leftEnemy2 = true; 
	} else {
		m_speed.x += 2.f;
		m_sprite.setTexture(rightTex);
		leftEnemy2 = false; 
	}
	// Actualiza la posicion de la bala y maneja su logica
	updateBullet(dt, p);
}

void Enemy2::updateBullet(float dt, Player &p) {
	// Logica de la bala
	
	if (bulletTimer.getElapsedTime() >= sf::seconds(5)) {
		// Llama al metodo que deseas activar despues de 10 segundos
		Bullet.setPosition(m_pos.x,m_pos.y+15.f);
		
		// Configura la velocidad y textura de la bala segun la direccion del jugador
		if (p.getPositionx() < m_pos.x) {
			speedBullet = -350.f;
			Bullet.setTexture(BulletTexLeft);
			left = true;
		} else {
			speedBullet = 350.f;
			Bullet.setTexture(BulletTexRight);
			left = false;
		}
		// Reinicia el temporizador
		bulletTimer.restart();
		shot_sound.play();
	}
	
	// Actualiza la posicion de la bala
	sf::Vector2f posBullet = Bullet.getPosition();
	posBullet.x += speedBullet * dt;
	Bullet.setPosition(posBullet);
	
	if(left){
		Bullet.setTexture(BulletTexLeft);
	} else {
		Bullet.setTexture(BulletTexRight);
	}
	
}

void Enemy2::drawBullet(sf::RenderWindow& window) {
	// Dibuja la bala si esta activa
	window.draw(Bullet);
}

bool Enemy2::collideWithPlayer(Object &o) {
	auto r1 = m_sprite.getGlobalBounds();
	auto r2 = o.getGlobalBounds();
	
	
	if (r2.intersects(r1)) {
		// Verifica si el jugador esta encima de la plataforma
		if (r2.top + r2.height < r1.top + 0.9f * r1.height) {
			// El jugador cae sobre la plataforma
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
				
				m_pos.y = m_pos.y + 75.f;
				m_sprite.setPosition(m_pos);

				if(leftEnemy2){
					m_sprite.setTexture(m_texture);
				} 
				else {
					m_sprite.setTexture(rightTex);
				}
				m_sprite.setScale(2.f,0.3f);
				return true;
			}
		} 
		else {
			if(leftEnemy2){
				m_sprite.setTexture(m_texture);
			} 
			else {
				m_sprite.setTexture(rightTex);
			}
			return false;
		}
		return false;
	}
	return false;
}

bool Enemy2::attackPlayer(Object &o) {
	auto r2 = Bullet.getGlobalBounds();
	auto r1 = o.getGlobalBounds();
	if (r2.intersects(r1)) {
		// Verifica si el jugador est� encima de la plataforma
		if (r2.top + r2.height < r1.top + 0.9f * r1.height) {
			// El jugador cae sobre la plataforma
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

bool Enemy2::collideWithInmortal(Object &o) {
	auto r1 = m_sprite.getGlobalBounds();
	auto r2 = o.getGlobalBounds();
	if (r2.intersects(r1)) {
		// Verifica si el jugador est� encima de la plataforma
		if (r2.top + r2.height < r1.top + 0.9f * r1.height) {
			// El jugador cae sobre la plataforma
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
				m_pos.y = m_pos.y + 75.f;
				m_sprite.setPosition(m_pos);
				m_sprite.setScale(2.f,0.3f);
				return true;
			}
		} else {
			m_pos.y = m_pos.y + 75.f;
			m_sprite.setPosition(m_pos);
			m_sprite.setScale(2.f,0.3f);
			return true;
		}
		return true;
	}
	return false;
}
