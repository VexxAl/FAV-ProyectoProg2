#include "Match2.h"
#include <SFML/Window/Keyboard.hpp>
#include "Game.h"

Match2::Match2() : m_player("./media/player2.png") {
	m_floor.setSize({800.0, 100.0});
	m_floor.setPosition({0.0, 500.0});
	m_floor.setFillColor({0, 0, 0, 0});
	textureMatch2.loadFromFile("./media/backgroundFAV.png");
	spriteMatch2.setTexture(textureMatch2);
}

void Match2::update(Game &game) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		game.getWindow().close();
	m_player.update(m_floor.getGlobalBounds());
}

void Match2::draw(sf::RenderWindow &window) {
	window.clear(sf::Color(150, 255, 255));
	window.draw(spriteMatch2);
	window.draw(m_floor);
	m_player.draw(window);
}
