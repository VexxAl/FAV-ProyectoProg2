#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Player.h"

Player::Player(std::string fname,std::string jumpName, std::string leftName, std::string rightName)
	: Object(fname), jumpCount(0), SpacePresed(false) {
	m_sprite.setPosition(50, 400); // Establece la posición inicial del jugador
	m_pos.x = 400.0f;
	jumpTex.loadFromFile(jumpName);
	leftTex.loadFromFile(leftName);
	rightTex.loadFromFile(rightName);
}

void Player::pausedPlayer() {
	// Guarda la posición actual del jugador
	previousPosition = m_pos;
	
	// Desactiva la velocidad del jugador
	m_speed = sf::Vector2f(0.0f, 0.0f);
	isPaused = true;
}

void Player::resumePlayer() {
	// Restaura la posición del jugador
	m_pos = previousPosition;
	isPaused = false;
}

void Player::update(sf::FloatRect platformBounds, float dt) {
	// Lógica de actualización específica del jugador
	
	// Movement based on dt
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		m_speed.x -= 55.f;
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || m_speed.y == 0.0f){
			m_sprite.setTexture(leftTex);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		m_speed.x += 55.f;
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || m_speed.y == 0.0f){
			m_sprite.setTexture(rightTex);
		}
	}
	else{
		m_speed.x = 0.0f;
	}
	
	m_speed.y += 60.f; // Apply constant gravity using dt
	
	
	// Update position based on dt
	m_pos += m_speed * dt;
	
	m_sprite.setPosition(m_pos);
	auto playerBounds = m_sprite.getGlobalBounds();
	
	// Lógica para mantener al jugador dentro de los bordes de la pantalla
	if (m_pos.x < 0) {
		m_pos.x = 0;
		m_speed.x = 0;
	} else if (m_pos.x > 800 - playerBounds.width) {
		m_pos.x = 800 - playerBounds.width;
		m_speed.x = 0;
	}
	
	
	// Collision handling with platform considering dt
	if (playerBounds.intersects(platformBounds)) {
		m_speed.y = 0.0f;
		jumpCount = 0;
		m_pos.y = platformBounds.top - playerBounds.height;
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			m_sprite.setTexture(m_texture);
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !SpacePresed && jumpCount < 2) {
		m_speed.y = -1200.0f; // Use dt for consistent jump height
		SpacePresed = true;
		jumpCount++;
		m_sprite.setTexture(jumpTex);
	} else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		SpacePresed = false;
	};
}

void Player::rewindJump(){
	jumpCount = 0;
	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		m_sprite.setTexture(m_texture);
	}
}

