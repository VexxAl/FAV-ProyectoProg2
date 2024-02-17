#include "PauseMenu.h"
#include "Match1.h"
#include <SFML/Window/Keyboard.hpp>
#include "Game.h"

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
}
