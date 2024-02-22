#include "Scene.h"
#include "Menu.h"

#include <SFML/Audio.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>


Menu::Menu() {
	m_font.loadFromFile("./media/fonts/PixelGamer.otf");
	m_t1.setFont(m_font);
	m_t2.setFont(m_font);
	
	m_t1.setString("FAV-Space");
	m_t1.setFillColor({255,255,255});
	m_t1.setPosition(153, 75);
	m_t1.setCharacterSize(100);
	
	m_t2.setString("<presione F para comenzar>");
	m_t2.setFillColor({150,150,150});
	m_t2.setPosition(360,350);
	m_t2.setCharacterSize(20);
	
	textureMenu.loadFromFile("./media/images/menu.jpg");
	spriteMenu.setTexture(textureMenu);
}

void Menu::update(Game &game, float dt) {
	unsigned char r = rand();
	unsigned char g = rand();
	unsigned char b = rand();
	m_t1.setFillColor({r, g, b});
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
		game.playEnterSound();

		MenuSelect* menuS = new MenuSelect();
		game.setScene(menuS);
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		game.getWindow().close();
	}
}

void Menu::draw(sf::RenderWindow &window) {
	window.clear({0, 0, 0});
	window.draw(spriteMenu);
	window.draw(m_t1);
	window.draw(m_t2);
}

	

