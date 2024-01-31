#include "Match.h"

Match::Match() {
	
}

void Match::Update(Game &game){
	if(sf::Keyboard::isKeyPressed(Keyboard::Key::Escape))
		game.SetScene(new Menu());
	m_player.Update();
}

void Match::Draw(sf::RenderWindow &window){
	window.clear();
	m_player.draw(window);
}
