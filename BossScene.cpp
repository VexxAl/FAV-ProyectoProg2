#include "BossScene.h"
#include <SFML/Window/Keyboard.hpp>

#include <iostream>
#include "Game.h"

BossScene::BossScene(std::string fname, std::string jumpName, std::string leftName, std::string rightName, std::string attackName, std::string boosterName, float e1, float e2)
	: Match(fname, jumpName, leftName, rightName, attackName, boosterName, e1, e2) {
	
	platformsMobile.emplace_back(sf::Vector2f(75.f, 300.f), 0.f, "./media/images/match1/plataformaSpace.png");
	platformsMobile.emplace_back(sf::Vector2f(280.f, 100.f), 0.f, "./media/images/match1/BossMatch/plataformBoss.png");
	platformsMobile.emplace_back(sf::Vector2f(500.f, 300.f), 0.f, "./media/images/match1/plataformaSpace.png");
	
	bossTexture.loadFromFile("./media/images/match1/BossMatch/bossWatching.png");
	bossSprite.setTexture(bossTexture);
	bossSprite.setPosition(350.f, 30.f);
	bossSprite.setScale(2, 2);
	
	textureMatch.loadFromFile("./media/images/match1/BossMatch/backgroundBoss.jpg");
	spriteMatch.setTexture(textureMatch);
	
	lifesText.setFillColor(sf::Color::Cyan);
	
	itemGenerationClock.restart();
	pause=false;
}


void BossScene::update(Game &game, float dt) {
	
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
				game.stopBossMusic();
				game.playMatch1Music();
				state = true;
				Scene* newScene = new Match1("./media/images/match1/player.png", "./media/images/match1/p1_jump.png", "./media/images/match1/p1_left.png",
												"./media/images/match1/p1_right.png","./media/images/match1/p1_dead.png","./media/images/match1/p1_booster.png",1.0f,1.0f);
				game.setScene(newScene);
			} else if (m_selectedOption == 2) {
				game.stopBossMusic();
				game.playMenuMusic();
				state = true;
				Scene* newScene = new Menu();
				game.setScene(newScene);
			}
			
		}
	}
	
	
	
}

void BossScene::draw(sf::RenderWindow &window) {
	
	Match::draw(window);
	
	pointText.setString("Points " + std::to_string(pointCount));
	window.draw(bossSprite);
	
}

void BossScene::generateRandomItems(){	

	
	// Genera ítems cada cierto intervalo de tiempo
	if (itemGenerationClock.getElapsedTime() >= sf::seconds(5.0f)) {

		sf::Vector2f positionInmortal(rand() %700, rand() % 250 + 250.f);  // Ajusta el rango vertical
		float inmortalSpeed = 0.f;  // Velocidad del booster (ajústala según sea necesario)
		inmortals.emplace_back(positionInmortal, inmortalSpeed,"./media/images/match1/InmortalBoost.png","./media/images/match1/InmortalBoost.png");
		
		sf::Vector2f positionLife(rand() % 700 + 50.f, 450.f);  // Ajusta el rango vertical
		float lifeSpeed = 0.f;  // Velocidad del booster (ajústala según sea necesario)
		lifesBoost.emplace_back(positionLife, lifeSpeed,"./media/images/match1/SaludBooster.png");
		
		itemGenerationClock.restart();
	}
}


void BossScene::generateRandomEnemy() {
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

BossScene::~BossScene() {
	for (auto& enemy : enemyMatch) {
		delete enemy;
	}
}
