#ifndef MENU_H
#define MENU_H

#include "Scene.h"
#include "Game.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Keyboard.hpp>

class Menu : public Scene {
public:
	Menu();
	void update(Game &game) override;
	void draw(sf::RenderWindow &window) override;
private:
	sf::Font m_font;
	sf::Text m_t1, m_t2;
};


#endif

