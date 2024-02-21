#include "PauseMenu.h"
#include "Match1.h"
#include <SFML/Window/Keyboard.hpp>
#include "Game.h"
#include "PlatformMobile.h"
#include "Coin.h"
#include <iostream>

Match1::Match1() : m_player("./media/player.png","./media/p1_jump.png","./media/p1_left.png","./media/p1_right.png"), coinCount(0) {
	m_floor.setSize({800.0, 100.0});
	m_floor.setPosition({0.0, 500.0});
	m_floor.setFillColor({0, 0, 0, 0});
	textureMatch1.loadFromFile("./media/backgroundSpace.png");
	spriteMatch1.setTexture(textureMatch1);
	
	if (!font.loadFromFile("./media/fonts/PixelEmulator.ttf")) {
		std::cerr << "Error al cargar la fuente" << std::endl;
	}
	
	coinText.setFont(font);
	coinText.setCharacterSize(24);
	coinText.setFillColor(sf::Color::White);
	coinText.setPosition(10.f, 10.f);
}

void Match1::update(Game &game, float dt) {
	
	generateRandomPlatformsMobile();
	movePlatformsMobile(dt);
	
	generateRandomCoins();
	despawnCoins();
	moveCoins(dt);
	
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
		m_player.update(m_floor.getGlobalBounds(), dt);
	}
	
	for (auto& platform : platformsMobile) {
		if(m_player.collideWith(platform)){
			m_player.rewindJump();
		}
	}
	
	for (auto& coin : coins) {
		if (!coin.isTaken() && m_player.getGlobalBounds().intersects(coin.getGlobalBounds())) {
			coin.setTaken(true);
			coinCount++;
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		game.isPaused();
	}
}

void Match1::draw(sf::RenderWindow &window) {
	window.clear(sf::Color(150, 255, 255));
	window.draw(spriteMatch1);
	window.draw(m_floor);
	m_player.draw(window);
	
	for (auto& platform : platformsMobile) {
		platform.draw(window);
	}
	
	for (auto& coin : coins) {
		if (!coin.isTaken()) {
			coin.draw(window);
		}
	}
	coinText.setString("Coins " + std::to_string(coinCount));
	window.draw(coinText);
}

void Match1::generateRandomPlatformsMobile() {
	// Genera plataformas móviles aleatorias en la derecha de la pantalla
	if (rand() % 200 == 0) {
		sf::Vector2f platformPosition(800.f, rand() % 200 + 120.f); // Ajusta el rango vertical
		float platformSpeed = static_cast<float>(rand() % 200 + 50); // Ajusta la velocidad según sea necesario
		platformsMobile.emplace_back(platformPosition, platformSpeed);
	}
}

void Match1::movePlatformsMobile(float dt) {
	// Mueve las plataformas móviles de derecha a izquierda
	for (auto& platform : platformsMobile) {
		platform.update(dt);
	}
}

void Match1::moveCoins(float dt) {
	// Mueve las monedas de derecha a izquierda
	for (auto& coin : coins) {
		coin.update(dt);
	}
}

void Match1::generateRandomCoins() {
	// Genera monedas aleatorias en la derecha de la pantalla
	if (rand() % 100 == 1) {
		sf::Vector2f coinPosition(800.f, rand() % 450 + 50.f);  // Ajusta el rango vertical
		float coinSpeed = -100.f;  // Velocidad de la moneda (ajústala según sea necesario)
		coins.emplace_back(coinPosition, coinSpeed);
	}
}

void Match1::despawnCoins() {
	// Elimina las monedas que han salido de la pantalla por la izquierda
	coins.erase(std::remove_if(coins.begin(), coins.end(), [](const Coin& coin) {
		return coin.getPositionx() + coin.getWidth() < 0.f;
	}), coins.end());
}


