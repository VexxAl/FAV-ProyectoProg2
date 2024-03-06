#include "Game.h"
#include "Match2.h"
#include "GameOver.h"

#include <SFML/Window/Keyboard.hpp>

#include <iostream>


Match2::Match2(std::string fname,std::string jumpName, std::string leftName, std::string rightName, std::string attackName,std::string boosterName, float e1, float e2)
	:  Match(fname,jumpName,leftName,rightName,attackName,boosterName,e1, e2) {
	
	textureMatch.loadFromFile("./media/images/match2/backgroundFAV.png");
	spriteMatch.setTexture(textureMatch);
	
	lifesText.setFillColor(sf::Color::Yellow);
	
	CoefSpeed = 2.3f;
	pause=false;

	kill_enemy1_buffer.loadFromFile("./media/sounds/match2/kill_sound.wav");
	kill_enemy1_sound.setBuffer(kill_enemy1_buffer);

	kill_enemy2_buffer.loadFromFile("./media/sounds/match2/kill_sound_e2.wav");
	kill_enemy2_sound.setBuffer(kill_enemy2_buffer);

	isMatch2 = true;	
}

void Match2::update(Game &game, float dt) {
	
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
				game.playMatch2Music();
				state = true;
				Scene* newScene = new Match2("./media/images/match2/p2.png", "./media/images/match2/p2_jump.png", "./media/images/match2/p2_left.png",
											 "./media/images/match2/p2_right.png","./media/images/match2/p2_dead.png","./media/images/match2/p2_booster.png",2.6f,2.6f);
				game.setScene(newScene);
			} else if (m_selectedOption == 2) {
				game.stopMatch2Music();
				game.playMenuMusic();
				state = true;
				Scene* newScene = new Menu();
				game.setScene(newScene);
			}
			
		}
	}
	
}

void Match2::draw(sf::RenderWindow &window) {
	
	Match::draw(window);
	
	pointText.setString("Likes " + std::to_string(pointCount));
	
}

void Match2::generateRandomItems(){
	
	if(ItemClock.getElapsedTime() >= sf::seconds(5.5f / CoefSpeed)){
		int random = rand() % 9;
		int position = rand() % 200 + 150.f;
		if (random == 1){
			platformsMobile.emplace_back(sf::Vector2f(800.f,position),120.f*CoefSpeed,"media/images/match2/plataformaFAV.png");
			coins.emplace_back(sf::Vector2f(830.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(870.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(910.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(950.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
		} else if (random == 2){
			platformsMobile.emplace_back(sf::Vector2f(800.f,position),120.f*CoefSpeed,"media/images/match2/plataformaFAV.png");
			coins.emplace_back(sf::Vector2f(830.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(870.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(910.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(950.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			platformsMobile.emplace_back(sf::Vector2f(1010.f,position),120.f*CoefSpeed,"media/images/match2/plataformaFAV.png");
			coins.emplace_back(sf::Vector2f(1040.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1080.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1120.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1160.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			platformsMobile.emplace_back(sf::Vector2f(1220.f,position),120.f*CoefSpeed,"media/images/match2/plataformaFAV.png");
			coins.emplace_back(sf::Vector2f(1250.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1290.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1330.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1370.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
		} else if (random == 3){
			platformsMobile.emplace_back(sf::Vector2f(800.f,position),120.f*CoefSpeed,"media/images/match2/plataformaFAV.png");
			coins.emplace_back(sf::Vector2f(830.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(870.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(910.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(950.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			platformsMobile.emplace_back(sf::Vector2f(1220.f,position),120.f*CoefSpeed,"media/images/match2/plataformaFAV.png");
			coins.emplace_back(sf::Vector2f(1250.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1290.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1330.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1370.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
		} else if (random == 4){
			platformsMobile.emplace_back(sf::Vector2f(800.f,position+30.f),120.f*CoefSpeed,"media/images/match2/plataformaFAV.png");
			coins.emplace_back(sf::Vector2f(830.f,position-5.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(870.f,position-5.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(910.f,position-5.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			enemyMatch.push_back(new Enemy1("media/images/match2/Enemy1_left.png", "media/images/match2/Enemy1_right.png",sf::Vector2f(950.f,position-5.f)));
			platformsMobile.emplace_back(sf::Vector2f(1010.f,position+30.f),120.f*CoefSpeed,"media/images/match2/plataformaFAV.png");
			enemyMatch.push_back(new Enemy1("media/images/match2/Enemy1_left.png", "media/images/match2/Enemy1_right.png",sf::Vector2f(1040.f,position-5.f)));
			coins.emplace_back(sf::Vector2f(1080.f,position-5.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1120.f,position-5.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1160.f,position-5.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			
			platformsMobile.emplace_back(sf::Vector2f(800.f,position-120.f),120.f*CoefSpeed,"media/images/match2/plataformaFAV.png");
			coins.emplace_back(sf::Vector2f(830.f,position-35.f-120.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(870.f,position-35.f-120.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(910.f,position-35.f-120.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(950.f,position-35.f-120.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			platformsMobile.emplace_back(sf::Vector2f(1010.f,position-120.f),120.f*CoefSpeed,"media/images/match2/plataformaFAV.png");
			coins.emplace_back(sf::Vector2f(1040.f,position-35.f-120.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1080.f,position-35.f-120.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1120.f,position-35.f-120.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1160.f,position-35.f-120.f),-120.f*CoefSpeed,"media/images/match2/like.png");
		} else if (random == 5){
			platformsMobile.emplace_back(sf::Vector2f(800.f,position+30.f),120.f*CoefSpeed,"media/images/match2/plataformaFAV.png");
			coins.emplace_back(sf::Vector2f(830.f,position-5.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(870.f,position-5.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(910.f,position-5.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(950.f,position-5.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			platformsMobile.emplace_back(sf::Vector2f(1220.f,position+30.f),120.f*CoefSpeed,"media/images/match2/plataformaFAV.png");
			coins.emplace_back(sf::Vector2f(1250.f,position-5.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1290.f,position-5.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1330.f,position-5.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1370.f,position-5.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			
			platformsMobile.emplace_back(sf::Vector2f(800.f,position-120.f),120.f*CoefSpeed,"media/images/match2/plataformaFAV.png");
			coins.emplace_back(sf::Vector2f(830.f,position-35.f-120.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(870.f,position-35.f-120.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(910.f,position-35.f-120.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(950.f,position-35.f-120.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			platformsMobile.emplace_back(sf::Vector2f(1220.f,position-120.f),120.f*CoefSpeed,"media/images/match2/plataformaFAV.png");
			coins.emplace_back(sf::Vector2f(1250.f,position-35.f-120.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1290.f,position-35.f-120.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1330.f,position-35.f-120.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1370.f,position-35.f-120.f),-120.f*CoefSpeed,"media/images/match2/like.png");
		} else if (random == 6){
			platformsMobile.emplace_back(sf::Vector2f(800.f,position),120.f*CoefSpeed,"media/images/match2/plataformaFAV.png");
			coins.emplace_back(sf::Vector2f(830.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(870.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(910.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(950.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			platformsMobile.emplace_back(sf::Vector2f(1010.f,position),120.f*CoefSpeed,"media/images/match2/plataformaFAV.png");
			coins.emplace_back(sf::Vector2f(1040.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			enemyMatch.push_back(new Enemy1("media/images/match2/Enemy1_left.png", "media/images/match2/Enemy1_right.png",sf::Vector2f(1080.f,position-35.f)));
			enemyMatch.push_back(new Enemy1("media/images/match2/Enemy1_left.png", "media/images/match2/Enemy1_right.png",sf::Vector2f(1120.f,position-35.f)));
			coins.emplace_back(sf::Vector2f(1160.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			platformsMobile.emplace_back(sf::Vector2f(1220.f,position),120.f*CoefSpeed,"media/images/match2/plataformaFAV.png");
			coins.emplace_back(sf::Vector2f(1250.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1290.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1330.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1370.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
		} else if (random == 7){
			platformsMobile.emplace_back(sf::Vector2f(800.f,position),120.f*CoefSpeed,"media/images/match2/plataformaFAV.png");
			coins.emplace_back(sf::Vector2f(830.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(870.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(910.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(950.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			platformsMobile.emplace_back(sf::Vector2f(1010.f,position),120.f*CoefSpeed,"media/images/match2/plataformaFAV.png");
			coins.emplace_back(sf::Vector2f(1040.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			enemyMatch.push_back(new Enemy2("media/images/match2/Enemy2_left.png", "media/images/match2/Enemy2_right.png", "media/images/match2/BulletLeft.png", "media/images/match2/BulletRight.png",sf::Vector2f(1080.f,position-75.f)));
			enemyMatch.push_back(new Enemy2("media/images/match2/Enemy2_left.png", "media/images/match2/Enemy2_right.png", "media/images/match2/BulletLeft.png", "media/images/match2/BulletRight.png",sf::Vector2f(1120.f,position-75.f)));
			coins.emplace_back(sf::Vector2f(1160.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			platformsMobile.emplace_back(sf::Vector2f(1220.f,position),120.f*CoefSpeed,"media/images/match2/plataformaFAV.png");
			coins.emplace_back(sf::Vector2f(1250.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1290.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1330.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			coins.emplace_back(sf::Vector2f(1370.f,position-35.f),-120.f*CoefSpeed,"media/images/match2/like.png");
		} else if (random == 8) {
			platformsMobile.emplace_back(sf::Vector2f(800.f,position+30.f),120.f*CoefSpeed,"media/images/match2/plataformaFAV.png");
			coins.emplace_back(sf::Vector2f(830.f,position-5.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			enemyMatch.push_back(new Enemy2("media/images/match2/Enemy2_left.png", "media/images/match2/Enemy2_right.png", "media/images/match2/BulletLeft.png", "media/images/match2/BulletRight.png",sf::Vector2f(890.f,position-45.f)));
			coins.emplace_back(sf::Vector2f(950.f,position-5.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			platformsMobile.emplace_back(sf::Vector2f(1220.f,position+30.f),120.f*CoefSpeed,"media/images/match2/plataformaFAV.png");
			coins.emplace_back(sf::Vector2f(1250.f,position-5.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			enemyMatch.push_back(new Enemy2("media/images/match2/Enemy2_left.png", "media/images/match2/Enemy2_right.png", "media/images/match2/BulletLeft.png", "media/images/match2/BulletRight.png",sf::Vector2f(1310.f,position-45.f)));
			coins.emplace_back(sf::Vector2f(1370.f,position-5.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			
			platformsMobile.emplace_back(sf::Vector2f(800.f,position-120.f),120.f*CoefSpeed,"media/images/match2/plataformaFAV.png");
			coins.emplace_back(sf::Vector2f(830.f,position-35.f-120.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			enemyMatch.push_back(new Enemy2("media/images/match2/Enemy2_left.png", "media/images/match2/Enemy2_right.png", "media/images/match2/BulletLeft.png", "media/images/match2/BulletRight.png",sf::Vector2f(890.f,position-75.f-120.f)));
			coins.emplace_back(sf::Vector2f(950.f,position-35.f-120.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			platformsMobile.emplace_back(sf::Vector2f(1220.f,position-120.f),120.f*CoefSpeed,"media/images/match2/plataformaFAV.png");
			coins.emplace_back(sf::Vector2f(1250.f,position-35.f-120.f),-120.f*CoefSpeed,"media/images/match2/like.png");
			enemyMatch.push_back(new Enemy2("media/images/match2/Enemy2_left.png", "media/images/match2/Enemy2_right.png", "media/images/match2/BulletLeft.png", "media/images/match2/BulletRight.png",sf::Vector2f(1310.f,position-75.f-120.f)));
			coins.emplace_back(sf::Vector2f(1370.f,position-35.f-120.f),-120.f*CoefSpeed,"media/images/match2/like.png");
		}
		ItemClock.restart();
	}
	
	if (rand()% 1400  == 1) {
		sf::Vector2f positionInmortal(800.f, rand() % 250 + 250.f);  // Ajusta el rango vertical
		float inmortalSpeed = -120.f;  // Velocidad del booster (aj�stala seg�n sea necesario)
		inmortals.emplace_back(positionInmortal, inmortalSpeed * CoefSpeed,"media/images/match2/InmortalBoost.png","media/images/match2/InmortalBoost.png");
	}
	
	if (rand()% 1400  == 1) {
		sf::Vector2f positionLife(800.f, rand() % 450 + 50.f);  // Ajusta el rango vertical
		float lifeSpeed = -120.f;  // Velocidad del booster (aj�stala seg�n sea necesario)
		lifesBoost.emplace_back(positionLife, lifeSpeed * CoefSpeed,"media/images/match2/SaludBooster.png");
	}
	
}


void Match2::generateRandomEnemy() {
	if (rand() % 600 == 1) {
		enemyMatch.push_back(new Enemy1("media/images/match2/Enemy1_left.png", "media/images/match2/Enemy1_right.png",sf::Vector2f(800.f,465.f)));
	} 
	
	if (rand() % 600 == 1) {
		enemyMatch.push_back(new Enemy2("media/images/match2/Enemy2_left.png", "media/images/match2/Enemy2_right.png", "media/images/match2/BulletLeft.png", "media/images/match2/BulletRight.png",sf::Vector2f(800.f,425.f)));
	}
	
	if (rand() % 600 == 1) {
		float positionAux = rand() % 250 + 50.f;
		enemyMatch.push_back(new Enemy3("./media/images/match2/Enemy3.png", positionAux));
	}
}


Match2::~Match2() {
	for (auto& enemy : enemyMatch) {
		delete enemy;
	}
}


