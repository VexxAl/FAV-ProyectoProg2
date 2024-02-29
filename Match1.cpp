#include "Match1.h"
#include <SFML/Window/Keyboard.hpp>

#include <iostream>
#include "Game.h"

Match1::Match1(std::string fname,std::string jumpName, std::string leftName, std::string rightName, std::string attackName,std::string boosterName, float e1, float e2)
	:  Match(fname,jumpName,leftName,rightName,attackName,boosterName,e1, e2) {
	
	textureMatch.loadFromFile("./media/images/match1/backgroundSpace.png");
	spriteMatch.setTexture(textureMatch);
	
	lifesText.setFillColor(sf::Color::Cyan);
	
}

void Match1::update(Game &game, float dt) {
	
	Match::update(game, dt);
	
	if (!pause){
		m_player.update(m_floor.getGlobalBounds(), dt, cooldown);
		
		generateRandomEnemy();
		enemyMecanic(dt);
		
		generateRandomItems();
		despawnItems();
		moveItems(dt);
	}
	if (pause) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !upPressed) {
			m_selectedOption = (m_selectedOption - 1 + m_options.size()) % m_options.size();
			upPressed = true;
			game.playSelectSound();
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			upPressed = false;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !downPressed) {
			m_selectedOption = (m_selectedOption + 1) % m_options.size();
			downPressed = true;
			game.playSelectSound();
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			downPressed = false;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			game.playEnterSound();
			
			// Manejo de la opcion seleccionada:
			if (m_selectedOption == 0) {
				pause = false;
			}
			else if (m_selectedOption == 1) {
				game.playMatch1Music();
				state = true;
				Scene* newScene = new Match1("./media/images/match1/player.png", "./media/images/match1/p1_jump.png", "./media/images/match1/p1_left.png",
											 "./media/images/match1/p1_right.png","./media/images/match1/p1_dead.png","./media/images/match1/p1_booster.png",1.0f,1.0f);
				game.setScene(newScene);
			} else if (m_selectedOption == 2) {
				game.stopMatch1Music();
				game.playMenuMusic();
				state = true;
				Scene* newScene = new Menu();
				game.setScene(newScene);
			}
			
		}
	}
	
}

void Match1::draw(sf::RenderWindow &window) {
	
	Match::draw(window);
	
	pointText.setString("Points " + std::to_string(pointCount));
	
}

void Match1::generateRandomItems(){
	
	if (rand() % 200 == 0) {
		sf::Vector2f platformPosition(800.f, rand() % 200 + 120.f); // Ajusta el rango vertical
		float platformSpeed = static_cast<float>(rand() % 200 + 50); // Ajusta la velocidad segun sea necesario
		platformsMobile.emplace_back(platformPosition, platformSpeed, "./media/images/match1/plataformaSpace.png");
	}
	
	if (rand() % 100 == 1) {
		sf::Vector2f coinPosition(800.f, rand() % 450 + 50.f);  // Ajusta el rango vertical
		float coinSpeed = -100.f;  // Velocidad de la moneda
		coins.emplace_back(coinPosition, coinSpeed,"./media/images/match1/star.png");
	}
	
	if (rand()% 500  == 1) {
		sf::Vector2f positionInmortal(800.f, rand() % 250 + 250.f);  // Ajusta el rango vertical
		float inmortalSpeed = -30.f;  // Velocidad del booster (ajústala según sea necesario)
		inmortals.emplace_back(positionInmortal, inmortalSpeed,"./media/images/match1/InmortalBoost.png","./media/images/match1/InmortalBoost.png");
	}
	
	if (rand()% 300  == 1) {
		sf::Vector2f positionLife(800.f, rand() % 450 + 50.f);  // Ajusta el rango vertical
		float lifeSpeed = -100.f;  // Velocidad del booster (ajústala según sea necesario)
		lifesBoost.emplace_back(positionLife, lifeSpeed,"./media/images/match1/SaludBooster.png");
	}
}


void Match1::generateRandomEnemy() {
	if (rand() % 800 == 1) {
		enemyMatch.push_back(new Enemy1("./media/images/match1/Enemy1_left.png", "./media/images/match1/Enemy1_right.png"));
	} 
	
	if (rand() % 400 == 1) {
		enemyMatch.push_back(new Enemy2("./media/images/match1/Enemy2_left.png", "./media/images/match1/Enemy2_right.png", "./media/images/match1/BulletLeft.png", "./media/images/match1/BulletRight.png"));
	}
	
	if (rand() % 800 == 1) {
		float positionAux = rand() % 250 + 50.f;
		enemyMatch.push_back(new Enemy3("./media/images/match1/Enemy3.png", positionAux));
	}
}

Match1::~Match1() {
	for (auto& enemy : enemyMatch) {
		delete enemy;
	}
}


