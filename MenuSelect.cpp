#include "Game.h"
#include "Creditos.h"
#include "Ranking.h"
#include "MenuSelect.h"

#include <SFML/Window/Keyboard.hpp>

#include <iostream>


MenuSelect::MenuSelect() : m_selectedOption(0) {
	textureSelect.loadFromFile("./media/images/backgroundSelect.jpg");
	spriteSelect.setTexture(textureSelect);
	m_font.loadFromFile("./media/fonts/PixelGamer.otf");
	std::vector<std::string> optionNames = {"Jugar", "Modo FAV", "FAV Ranking", "Cr�ditos" ,"Volver"};
	
	for (int i = 0; i < optionNames.size(); i++) {
		sf::Text text;
		text.setFont(m_font);
		text.setString(optionNames[i]);
		text.setPosition(320, i * 80 + 120);
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
			match = new Match1("./media/images/match1/player.png", "./media/images/match1/p1_jump.png", "./media/images/match1/p1_left.png",
				"./media/images/match1/p1_right.png","./media/images/match1/p1_dead.png","./media/images/match1/p1_booster.png",1.0f,1.0f);

			game.stopMenuMusic();
			game.playMatch1Music();	
		} 
		else if(m_selectedOption == 1){
			match = new Match2("./media/images/match2/p2.png", "./media/images/match2/p2_jumpPrueba.png", "./media/images/match2/p2_left.png",
				"./media/images/match2/p2_right.png","./media/images/match2/p2_dead.png","./media/images/match2/p2_booster.png",2.6f,2.6f);

			game.stopMenuMusic();
			game.playMatch2Music();
		}
		else if (m_selectedOption == 2) {
			match = new Ranking();
			game.stopMenuMusic();
		} 
		else if(m_selectedOption == 3){
			match = new Creditos();
			game.stopMenuMusic();
			game.playCreditosMusic();
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
