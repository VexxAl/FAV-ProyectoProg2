#include "PauseMenu.h"
#include "Match1.h"
#include <SFML/Window/Keyboard.hpp>
#include "Game.h"
#include "PlataformMobile.h"

Match1::Match1() : m_player("./media/player.png") {
	m_floor.setSize({800.0, 100.0});
	m_floor.setPosition({0.0, 500.0});
	m_floor.setFillColor({0, 0, 0, 0});
	textureMatch1.loadFromFile("./media/backgroundSpace.png");
	spriteMatch1.setTexture(textureMatch1);
}

void Match1::update(Game &game, float dt) {
	if (game.isPaused()) {
		return; // No update if paused
	}
	
	generateRandomPlatformsMobile();
	movePlatformsMobile(dt);
	
	m_player.update(m_floor.getGlobalBounds(), dt);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		game.setPaused(true);
		m_player.pausedPlayer();
		Scene* pause = new PauseMenu();
		game.setScene(pause);
	}
}

void Match1::draw(sf::RenderWindow &window) {
	window.clear(sf::Color(150, 255, 255));
	window.draw(spriteMatch1);
	window.draw(m_floor);
	m_player.draw(window);
	
	for (const auto& platform : platformsMobile) {
		window.draw(platform.getShape());
	}
}

void Match1::generateRandomPlatformsMobile() {
	// Genera plataformas móviles aleatorias en la derecha de la pantalla
	if (rand() % 100 == 0) {
		sf::Vector2f platformPosition(800.f, rand() % 450 + 50.f); // Ajusta el rango vertical
		sf::Vector2f platformSize(100.f, 20.f); // Ajusta el tamaño según sea necesario
		float platformSpeed = static_cast<float>(rand() % 200 + 50); // Ajusta la velocidad según sea necesario
		platformsMobile.emplace_back(platformPosition, platformSize, platformSpeed);
	}
}

void Match1::movePlatformsMobile(float dt) {
	// Mueve las plataformas móviles de derecha a izquierda
	for (auto& platform : platformsMobile) {
		platform.update(dt);
	}
}


