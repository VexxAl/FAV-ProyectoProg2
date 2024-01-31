#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Scene.h"
#include "Menu.h"
#include "Match.h"


Menu::Menu() {
	m_font.loadFroFile("media\fonts\PixelGamer.otf");
	m_t1.setFront(m_font);
	m_t2.setFont(m_font);
	
	m_t1.setString("FAV");
	m_t1.setFillColor({255,255,255});
	m_t1.setPosition(110, 150);
	m_t1.setCharacterSize(50);
	
	m_t2.setString("<presione Enter para comenzar>");
	m_t2.setFillColor({150,150,150});
	m_t2.setPosition(150,350);
	m_t2.setCharacterSize(20);
}

void Menu::Update(Game &game){
	unsigned char r = rand();
	unsigned char g = rand();
	unsigned char b = rand();
	m_t1.setFillColor({r,g,b});
	if(Keyboard::isKeyPressed(Keyboard::Key::Return))
		game.SetScene(new Match());
}

void Menu::Draw(RenderWindow & window){
	window.clear({0,0,0});
	window.draw(m_t1);
	window.draw(m_t2);
	window.display();
}

	

