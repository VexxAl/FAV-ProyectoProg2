#ifndef PAUSEMENU_H
#define PAUSEMENU_H
#include "Scene.h"
#include "Game.h"
#include <SFML/Graphics/Font.hpp>
#include <vector>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>


class PauseMenu : public Scene {
public:
	PauseMenu();
	void update (Game &game, float dt) override;
	void draw (sf::RenderWindow & window) override;
	bool getState(){return state;}
	bool isMatch1() const override { return false; }
private:
	sf::Font m_font;
	std::vector<sf::Text> m_options;
	int m_selectedOption;
	bool state;
	bool upPressed;
	bool downPressed;
};

#endif

