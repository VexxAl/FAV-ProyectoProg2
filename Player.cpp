#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Player.h"

Player::Player(std::string fname1) : Object(fname1), jumpCount(0) {
	m_sprite.setPosition(50, 400); // Establece la posición inicial del jugador
}

void Player::update(sf::FloatRect platformBounds) {
	// Lógica de actualización específica del jugador
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_speed.x -= 0.6;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_speed.x += 0.6;
	else
		m_speed.x = 0;
	
	m_speed.y += 0.6;
	
	m_pos += m_speed;
	
	// Lógica para mantener al jugador dentro de los bordes de la pantalla
	if (m_pos.x < 0) {
		m_pos.x = 0;
		m_speed.x = 0;
	}
	else if (m_pos.x > 800 - m_sprite.getGlobalBounds().width) {
		m_pos.x = 800 - m_sprite.getGlobalBounds().width;
		m_speed.x = 0;
	}
	
	m_sprite.setPosition(m_pos);
	auto playerBounds = m_sprite.getGlobalBounds();
	
	if (playerBounds.intersects(platformBounds)){
		m_speed.y = 0;
		jumpCount = 0;
		m_pos.y = platformBounds.top - playerBounds.height;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && jumpCount <= 2){
		m_speed.y = -15 ;
		jumpCount++;
	}
	
	Object::update(0.0f);  // Puedes pasar un valor arbitrario para dt
}


void Player::draw(sf::RenderWindow &window) {
	window.draw(m_sprite);
}
