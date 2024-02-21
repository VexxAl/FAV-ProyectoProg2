#ifndef MENUSELECT_H
#define MENUSELECT_H
#include "Scene.h"
#include "Game.h"
#include <vector>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
using namespace std;


class MenuSelect : public Scene {
public:
	MenuSelect();
	void update (Game &game, float dt)override;
	void draw (sf::RenderWindow & window)override;

private:
	sf::Font m_font;
	std::vector<sf::Text> m_options;
	int m_selectedOption;
	sf::Texture textureSelect;
	sf::Sprite spriteSelect;

};

#endif

