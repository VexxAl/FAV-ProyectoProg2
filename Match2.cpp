#include "PauseMenu.h"
#include "Match2.h"
#include <SFML/Window/Keyboard.hpp>
#include "Game.h"

Match2::Match2() : m_player("./media/player2.png","./media/p2_jump.png","./media/p2_left.png","./media/p2_right.png") {
	m_floor.setSize({800.0, 100.0});
	m_floor.setPosition({0.0, 500.0});
	m_floor.setFillColor({0, 0, 0, 0});
	textureMatch2.loadFromFile("./media/backgroundFAV.png");
	spriteMatch2.setTexture(textureMatch2);
}

void Match2::update(Game &game, float dt) {
	if (game.isPaused()) {
		// No actualizar el jugador si el juego está pausado
		return;
	}
	
	m_player.update(m_floor.getGlobalBounds(), dt);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		game.setPaused(true);  // Pausa el juego
		m_player.pausedPlayer();      // Deja al jugador quieto
		Scene* pause = new PauseMenu();
		game.setScene(pause);
	}	
}


void Match2::draw(sf::RenderWindow &window) {
	window.clear(sf::Color(150, 255, 255));
	window.draw(spriteMatch2);
	window.draw(m_floor);
	m_player.draw(window);
}
