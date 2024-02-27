#include "Player.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>


Player::Player(std::string fname,std::string jumpName, std::string leftName, std::string rightName, std::string attackName, float e1, float e2)
	: Object(fname), jumpCount(0), SpacePresed(false), lifes(3) {
	m_sprite.setPosition(450, 400); // Establece la posicion inicial del jugador
	m_pos.x = 400.0f;
	m_pos.y = 450.0f;
	jumpTex.loadFromFile(jumpName);
	leftTex.loadFromFile(leftName);
	rightTex.loadFromFile(rightName);
	attackTex.loadFromFile(attackName);
	m_sprite.setScale(e1,e2);
	
	jump_buffer.loadFromFile("./media/sounds/jump_sound.wav");
	jump_sound.setBuffer(jump_buffer);

	hurt_buffer.loadFromFile("./media/sounds/hurt_sound.wav");
	hurt_sound.setBuffer(hurt_buffer);
	
}


void Player::update(sf::FloatRect platformBounds, float dt, bool cooldown) {
	// Logica de actualizacion especifica del jugador
	// Movement based on dt
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		m_speed.x -= 55.f;
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || m_speed.y == 0.0f){
			if(cooldown){
				m_sprite.setTexture(attackTex);
			} else {
				m_sprite.setTexture(leftTex);
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		m_speed.x += 55.f;
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || m_speed.y == 0.0f){
			if(cooldown){
				m_sprite.setTexture(attackTex);
			} else {
				m_sprite.setTexture(rightTex);
			}
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
	
	// Logica para mantener al jugador dentro de los bordes de la pantalla
	if (m_pos.x < 0) {
		m_pos.x = 0;
		m_speed.x = 0;
	} else if (m_pos.x > 800 - playerBounds.width) {
		m_pos.x = 800 - playerBounds.width;
		m_speed.x = 0;
	}
	
	if (m_pos.y < 0) {
		m_pos.y = 0;
		m_speed.y = 0;
	} else if (m_pos.y > 800 - playerBounds.width) {
		m_pos.y = 800 - playerBounds.width;
		m_speed.y = 0;
	}
	
	// Collision handling with platform considering dt
	if (playerBounds.intersects(platformBounds)) {
		m_speed.y = 0.0f;
		jumpCount = 0;
		m_pos.y = platformBounds.top - playerBounds.height;
		if(cooldown){
			m_sprite.setTexture(attackTex);
		}
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			if(cooldown){
				m_sprite.setTexture(attackTex);
			} else {
				m_sprite.setTexture(m_texture);
			}
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !SpacePresed && jumpCount < 2) {
		jump_sound.play();
		m_speed.y = -1200.0f; // Use dt for consistent jump height
		SpacePresed = true;
		jumpCount++;
		if(cooldown){
			m_sprite.setTexture(attackTex);
		} else {
			m_sprite.setTexture(jumpTex);
		}
	} else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		SpacePresed = false;
	}
}

void Player::rewindJump(bool cooldown){
	jumpCount = 0;
	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		if(cooldown){
			m_sprite.setTexture(attackTex);
		} else {
			m_sprite.setTexture(m_texture);
		}
	}
}

void Player::loseLife(){
	m_sprite.setTexture(attackTex);
	lifes--;

	hurt_sound.play();
}

int Player::getLifes(){
	return lifes;
}


void Player::setInmortal(bool inmortal) {
	isInmortal = inmortal;
}

bool Player::getInmortal() {
	return isInmortal;
}

void Player::updateInmortality(int aux) {
	if (isInmortal && inmortalClock.getElapsedTime() <= sf::seconds(10.0f)) {
		if(aux == 1){
			m_texture.loadFromFile("./media/images/match1/p1_booster.png");
			jumpTex.loadFromFile("./media/images/match1/p1_booster.png");
			leftTex.loadFromFile("./media/images/match1/p1_booster.png");
			rightTex.loadFromFile("./media/images/match1/p1_booster.png");
			attackTex.loadFromFile("./media/images/match1/p1_booster.png");
		}
		if(aux == 2){
			m_texture.loadFromFile("./media/images/match2/p2_booster.png");
			jumpTex.loadFromFile("./media/images/match2/p2_booster.png");
			leftTex.loadFromFile("./media/images/match2/p2_booster.png");
			rightTex.loadFromFile("./media/images/match2/p2_booster.png");
			attackTex.loadFromFile("./media/images/match2/p2_booster.png");
		}
	} 
	if (isInmortal && inmortalClock.getElapsedTime() >= sf::seconds(10.0f)) {
		if(aux == 1){
			m_texture.loadFromFile("./media/images/match1/player.png");
			jumpTex.loadFromFile("./media/images/match1/p1_jump.png");
			leftTex.loadFromFile("./media/images/match1/p1_left.png");
			rightTex.loadFromFile("./media/images/match1/p1_right.png");
			attackTex.loadFromFile("./media/images/match1/p1_dead.png");
		}
		if(aux == 2){
			m_texture.loadFromFile("./media/images/match2/p2.png");
			jumpTex.loadFromFile("./media/images/match2/p2_jump.png");
			leftTex.loadFromFile("./media/images/match2/p2_left.png");
			rightTex.loadFromFile("./media/images/match2/p2_right.png");
			attackTex.loadFromFile("./media/images/match2/p2_hurt.png");
		}
		isInmortal = false;
	}
}

void Player::clockInmortality() {
	inmortalClock.restart();
}

void Player::updateLife(){
	lifes++;
}
