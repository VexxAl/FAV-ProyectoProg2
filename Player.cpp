#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Player.h"

Player::Player(std::string fname1) : Object(fname1), jumpCount(0), 	SpacePresed(false) {
	m_sprite.setPosition(50, 400); // Establece la posición inicial del jugador
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_speed.x -= 75.f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_speed.x += 75.f;
	else
		m_speed.x = 0.0f;
	
	m_speed.y += 70.f; // Apply constant gravity using dt
	
	// Update position based on dt
	m_pos += m_speed * dt;
	
	// Lógica para mantener al jugador dentro de los bordes de la pantalla
	if (m_pos.x < 0) {
		m_pos.x = 0;
		m_speed.x = 0;
	} else if (m_pos.x > 800 - m_sprite.getGlobalBounds().width) {
		m_pos.x = 800 - m_sprite.getGlobalBounds().width;
		m_speed.x = 0;
	}
	
	m_sprite.setPosition(m_pos);
	auto playerBounds = m_sprite.getGlobalBounds();
	
	// Collision handling with platform considering dt
	if (playerBounds.intersects(platformBounds)) {
		m_speed.y = 0.0f;
		jumpCount = 0;
		m_pos.y = platformBounds.top - playerBounds.height;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !SpacePresed && jumpCount < 2) {
		m_speed.y = -1300.0f; // Use dt for consistent jump height
		SpacePresed = true;
		jumpCount++;
	} else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		SpacePresed = false;
	};
	
	// Pass dt to generic update in case needed
	Object::update(dt);
}

void Player::draw(sf::RenderWindow &window) {
	window.draw(m_sprite);
}
