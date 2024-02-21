#ifndef MENU_H
#define MENU_H

#include "Scene.h"
#include "Game.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Menu : public Scene {
public:
	Menu();
	void update(Game &game, float dt) override;
	void draw(sf::RenderWindow &window) override;

private:
	sf::Font m_font;
	sf::Text m_t1, m_t2;
	sf::Texture textureMenu;
	sf::Sprite spriteMenu;
};


#endif

