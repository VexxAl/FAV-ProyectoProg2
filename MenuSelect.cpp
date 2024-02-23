#include "Game.h"
#include "MenuSelect.h"

#include <SFML/Window/Keyboard.hpp>

#include <iostream>


MenuSelect::MenuSelect() : m_selectedOption(0) {
	textureSelect.loadFromFile("./media/images/backgroundSelect.jpg");
	spriteSelect.setTexture(textureSelect);
	m_font.loadFromFile("./media/fonts/PixelGamer.otf");
	std::vector<std::string> optionNames = {"Jugar", "Modo FAV", "volver"};
	
	for (int i = 0; i < optionNames.size(); i++) {
		sf::Text text;
		text.setFont(m_font);
		text.setString(optionNames[i]);
		text.setPosition(350, i * 100 + 150);
		m_options.push_back(text);
	}
}

bool upPressedM = false;
bool downPressedM = false;

void MenuSelect::update(Game& game, float dt) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !upPressedM) {
		m_selectedOption = (m_selectedOption - 1 + m_options.size()) % m_options.size();
		upPressedM = true;
		game.playSelectSound();

	} else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		upPressedM = false;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !downPressedM) {
		m_selectedOption = (m_selectedOption + 1) % m_options.size();
		downPressedM = true;
		game.playSelectSound();

	} else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		downPressedM = false;
	}
		
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
		game.playEnterSound();

		Scene *match = nullptr;
		if(m_selectedOption == 0){
			match = new Match1();

			game.stopMenuMusic();
			game.playMatch1Music();	
		} 
		else if(m_selectedOption == 1){
			match = new Match2();


			game.stopMenuMusic();
			game.playMatch2Music();
		} 
		else {
			match = new Menu();
			
		};
		game.setScene(match);		
	}
}


void MenuSelect::draw(sf::RenderWindow& window) {
	window.clear();
	window.draw(spriteSelect);
	for (int i = 0; i < m_options.size(); i++) {
		if (i == m_selectedOption) {
			m_options[i].setFillColor({136, 0, 208});
		} else {
			m_options[i].setFillColor(sf::Color::White);
		}
		window.draw(m_options[i]);
	}
}
