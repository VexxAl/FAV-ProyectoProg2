#include "Game.h"
#include "Match2.h"

#include <SFML/Window/Keyboard.hpp>

Match2::Match2() : m_player("./media/images/match2/p2.png","./media/images/match2/p2_jumpPrueba.png",
		"./media/images/match2/p2_left.png","./media/images/match2/p2_right.png",2.6f,2.6f) {
	m_floor.setSize({800.0, 100.0});
	m_floor.setPosition({0.0, 500.0});
	m_floor.setFillColor({0, 0, 0, 0});
	textureMatch2.loadFromFile("./media/images/match2/backgroundFAV.png");
	spriteMatch2.setTexture(textureMatch2);
}

void Match2::update(Game &game, float dt) {
	
	m_player.update(m_floor.getGlobalBounds(), dt);
	
}

void Match2::draw(sf::RenderWindow &window) {
	window.clear(sf::Color(150, 255, 255));
	window.draw(spriteMatch2);
	window.draw(m_floor);
	m_player.draw(window);
}
