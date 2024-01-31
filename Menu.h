#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Scene.h"
#include "Game.h"

class Menu : public Scene {
public:
	Menu();
	void Update(Game &game) override;
	void Draw(sf::RenderWindow &window) override;
private:
	sf::Font m_font;
	sf::Text m_t1, m_t2;
};


#endif

