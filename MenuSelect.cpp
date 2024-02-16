#include "MenuSelect.h"
#include "Game.h" // Include your Game class here
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

MenuSelect::MenuSelect() : m_selectedOption(0) {
	m_font.loadFromFile("./media/fonts/PixelGamer.otf");
	std::vector<std::string> optionNames = {"Jugar", "Modo FAV", "volver"};
	
	for (int i = 0; i < optionNames.size(); i++) {
		sf::Text text;
		text.setFont(m_font);
		text.setString(optionNames[i]);
		text.setPosition(100, i * 100 + 100);
		m_options.push_back(text);
	}
}

bool upPressed = false;
bool downPressed = false;

void MenuSelect::update(Game& game, float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !upPressed) {
		m_selectedOption = (m_selectedOption - 1 + m_options.size()) % m_options.size();
		upPressed = true;
	} else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		upPressed = false;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !downPressed) {
		m_selectedOption = (m_selectedOption + 1) % m_options.size();
		downPressed = true;
	} else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		downPressed = false;
	}
		
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
		Scene *match = nullptr;
		if(m_selectedOption == 0){
			match = new Match1();
		} else if(m_selectedOption == 1){
			match = new Match2();
		} else {
			match = new Menu();
		};
		game.setScene(match);
		
	}
}


void MenuSelect::draw(sf::RenderWindow& window) {
	window.clear();
	for (int i = 0; i < m_options.size(); i++) {
		if (i == m_selectedOption) {
			m_options[i].setFillColor(sf::Color::Red);
		} else {
			m_options[i].setFillColor(sf::Color::White);
		}
		window.draw(m_options[i]);
	}
}
