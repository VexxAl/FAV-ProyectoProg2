#include "Match1.h"
#include <SFML/Window/Keyboard.hpp>

#include <iostream>
#include "Game.h"

Match1::Match1(std::string fname,std::string jumpName, std::string leftName, std::string rightName, std::string attackName,std::string boosterName, float e1, float e2)
	:  Match(fname,jumpName,leftName,rightName,attackName,boosterName,e1, e2) {
	
	textureMatch.loadFromFile("./media/images/match1/backgroundSpace.png");
	spriteMatch.setTexture(textureMatch);
	
	lifesText.setFillColor(sf::Color::Cyan);
	
	pause=false;

	kill_enemy1_buffer.loadFromFile("./media/sounds/match1/kill_enemy1.ogg");
	kill_enemy1_sound.setBuffer(kill_enemy1_buffer);

	kill_enemy2_buffer.loadFromFile("./media/sounds/match1/kill_enemy2.ogg");
	kill_enemy2_sound.setBuffer(kill_enemy2_buffer);
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
	
	if(pointCount == 100){
		CoefSpeed = 1.7f;
	} else if(pointCount == 200){
		CoefSpeed = 2.1f;
	} else if(pointCount == 350){
		CoefSpeed = 2.5f;
	}else if(pointCount == 500){
		game.stopMatch1Music();
		game.playBossMusic();
		Scene* newScene = new BossScene("./media/images/match1/player.png", "./media/images/match1/p1_jump.png", "./media/images/match1/p1_left.png",
									 "./media/images/match1/p1_right.png","./media/images/match1/p1_dead.png","./media/images/match1/p1_booster.png",1.0f,1.0f);
		game.setScene(newScene);
		
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		pointCount = 100;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		pointCount = 200;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		pointCount = 350;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		pointCount = 500;
	}
	
}

void Match1::draw(sf::RenderWindow &window) {
	
	Match::draw(window);
	
	pointText.setString("Points " + std::to_string(pointCount));
	
}

void Match1::generateRandomItems(){
	
	if(ItemClock.getElapsedTime() >= sf::seconds(5.5f / CoefSpeed)){
		int random = rand() % 9;
		int position = rand() % 200 + 150.f;
		if (random == 1){
			platformsMobile.emplace_back(sf::Vector2f(800.f,position),120.f*CoefSpeed,"./media/images/match1/plataformaSpace.png");
			coins.emplace_back(sf::Vector2f(830.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(870.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(910.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(950.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
		} else if (random == 2){
			platformsMobile.emplace_back(sf::Vector2f(800.f,position),120.f*CoefSpeed,"./media/images/match1/plataformaSpace.png");
			coins.emplace_back(sf::Vector2f(830.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(870.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(910.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(950.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			platformsMobile.emplace_back(sf::Vector2f(1010.f,position),120.f*CoefSpeed,"./media/images/match1/plataformaSpace.png");
			coins.emplace_back(sf::Vector2f(1040.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1080.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1120.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1160.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			platformsMobile.emplace_back(sf::Vector2f(1220.f,position),120.f*CoefSpeed,"./media/images/match1/plataformaSpace.png");
			coins.emplace_back(sf::Vector2f(1250.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1290.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1330.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1370.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
		} else if (random == 3){
			platformsMobile.emplace_back(sf::Vector2f(800.f,position),120.f*CoefSpeed,"./media/images/match1/plataformaSpace.png");
			coins.emplace_back(sf::Vector2f(830.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(870.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(910.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(950.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			platformsMobile.emplace_back(sf::Vector2f(1220.f,position),120.f*CoefSpeed,"./media/images/match1/plataformaSpace.png");
			coins.emplace_back(sf::Vector2f(1250.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1290.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1330.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1370.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
		} else if (random == 4){
			platformsMobile.emplace_back(sf::Vector2f(800.f,position+30.f),120.f*CoefSpeed,"./media/images/match1/plataformaSpace.png");
			coins.emplace_back(sf::Vector2f(830.f,position-5.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(870.f,position-5.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(910.f,position-5.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			enemyMatch.push_back(new Enemy1("./media/images/match1/Enemy1_left.png", "./media/images/match1/Enemy1_right.png",sf::Vector2f(950.f,position-5.f)));
			platformsMobile.emplace_back(sf::Vector2f(1010.f,position+30.f),120.f*CoefSpeed,"./media/images/match1/plataformaSpace.png");
			enemyMatch.push_back(new Enemy1("./media/images/match1/Enemy1_left.png", "./media/images/match1/Enemy1_right.png",sf::Vector2f(1040.f,position-5.f)));
			coins.emplace_back(sf::Vector2f(1080.f,position-5.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1120.f,position-5.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1160.f,position-5.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			
			platformsMobile.emplace_back(sf::Vector2f(800.f,position-120.f),120.f*CoefSpeed,"./media/images/match1/plataformaSpace.png");
			coins.emplace_back(sf::Vector2f(830.f,position-35.f-120.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(870.f,position-35.f-120.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(910.f,position-35.f-120.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(950.f,position-35.f-120.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			platformsMobile.emplace_back(sf::Vector2f(1010.f,position-120.f),120.f*CoefSpeed,"./media/images/match1/plataformaSpace.png");
			coins.emplace_back(sf::Vector2f(1040.f,position-35.f-120.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1080.f,position-35.f-120.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1120.f,position-35.f-120.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1160.f,position-35.f-120.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
		} else if (random == 5){
			platformsMobile.emplace_back(sf::Vector2f(800.f,position+30.f),120.f*CoefSpeed,"./media/images/match1/plataformaSpace.png");
			coins.emplace_back(sf::Vector2f(830.f,position-5.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(870.f,position-5.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(910.f,position-5.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(950.f,position-5.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			platformsMobile.emplace_back(sf::Vector2f(1220.f,position+30.f),120.f*CoefSpeed,"./media/images/match1/plataformaSpace.png");
			coins.emplace_back(sf::Vector2f(1250.f,position-5.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1290.f,position-5.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1330.f,position-5.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1370.f,position-5.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			
			platformsMobile.emplace_back(sf::Vector2f(800.f,position-120.f),120.f*CoefSpeed,"./media/images/match1/plataformaSpace.png");
			coins.emplace_back(sf::Vector2f(830.f,position-35.f-120.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(870.f,position-35.f-120.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(910.f,position-35.f-120.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(950.f,position-35.f-120.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			platformsMobile.emplace_back(sf::Vector2f(1220.f,position-120.f),120.f*CoefSpeed,"./media/images/match1/plataformaSpace.png");
			coins.emplace_back(sf::Vector2f(1250.f,position-35.f-120.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1290.f,position-35.f-120.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1330.f,position-35.f-120.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1370.f,position-35.f-120.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
		} else if (random == 6 && pointCount > 100){
			platformsMobile.emplace_back(sf::Vector2f(800.f,position),120.f*CoefSpeed,"./media/images/match1/plataformaSpace.png");
			coins.emplace_back(sf::Vector2f(830.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(870.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(910.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(950.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			platformsMobile.emplace_back(sf::Vector2f(1010.f,position),120.f*CoefSpeed,"./media/images/match1/plataformaSpace.png");
			coins.emplace_back(sf::Vector2f(1040.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			enemyMatch.push_back(new Enemy1("./media/images/match1/Enemy1_left.png", "./media/images/match1/Enemy1_right.png",sf::Vector2f(1080.f,position-35.f)));
			enemyMatch.push_back(new Enemy1("./media/images/match1/Enemy1_left.png", "./media/images/match1/Enemy1_right.png",sf::Vector2f(1120.f,position-35.f)));
			coins.emplace_back(sf::Vector2f(1160.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			platformsMobile.emplace_back(sf::Vector2f(1220.f,position),120.f*CoefSpeed,"./media/images/match1/plataformaSpace.png");
			coins.emplace_back(sf::Vector2f(1250.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1290.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1330.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1370.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
		} else if (random == 7 && pointCount > 100){
			platformsMobile.emplace_back(sf::Vector2f(800.f,position),120.f*CoefSpeed,"./media/images/match1/plataformaSpace.png");
			coins.emplace_back(sf::Vector2f(830.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(870.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(910.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(950.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			platformsMobile.emplace_back(sf::Vector2f(1010.f,position),120.f*CoefSpeed,"./media/images/match1/plataformaSpace.png");
			coins.emplace_back(sf::Vector2f(1040.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			enemyMatch.push_back(new Enemy2("./media/images/match1/Enemy2_left.png", "./media/images/match1/Enemy2_right.png", "./media/images/match1/BulletLeft.png", "./media/images/match1/BulletRight.png",sf::Vector2f(1080.f,position-75.f)));
			enemyMatch.push_back(new Enemy2("./media/images/match1/Enemy2_left.png", "./media/images/match1/Enemy2_right.png", "./media/images/match1/BulletLeft.png", "./media/images/match1/BulletRight.png",sf::Vector2f(1120.f,position-75.f)));
			coins.emplace_back(sf::Vector2f(1160.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			platformsMobile.emplace_back(sf::Vector2f(1220.f,position),120.f*CoefSpeed,"./media/images/match1/plataformaSpace.png");
			coins.emplace_back(sf::Vector2f(1250.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1290.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1330.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			coins.emplace_back(sf::Vector2f(1370.f,position-35.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
		} else if (random == 8 && pointCount > 200) {
			platformsMobile.emplace_back(sf::Vector2f(800.f,position+30.f),120.f*CoefSpeed,"./media/images/match1/plataformaSpace.png");
			coins.emplace_back(sf::Vector2f(830.f,position-5.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			enemyMatch.push_back(new Enemy2("./media/images/match1/Enemy2_left.png", "./media/images/match1/Enemy2_right.png", "./media/images/match1/BulletLeft.png", "./media/images/match1/BulletRight.png",sf::Vector2f(890.f,position-45.f)));
			coins.emplace_back(sf::Vector2f(950.f,position-5.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			platformsMobile.emplace_back(sf::Vector2f(1220.f,position+30.f),120.f*CoefSpeed,"./media/images/match1/plataformaSpace.png");
			coins.emplace_back(sf::Vector2f(1250.f,position-5.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			enemyMatch.push_back(new Enemy2("./media/images/match1/Enemy2_left.png", "./media/images/match1/Enemy2_right.png", "./media/images/match1/BulletLeft.png", "./media/images/match1/BulletRight.png",sf::Vector2f(1310.f,position-45.f)));
			coins.emplace_back(sf::Vector2f(1370.f,position-5.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			
			platformsMobile.emplace_back(sf::Vector2f(800.f,position-120.f),120.f*CoefSpeed,"./media/images/match1/plataformaSpace.png");
			coins.emplace_back(sf::Vector2f(830.f,position-35.f-120.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			enemyMatch.push_back(new Enemy2("./media/images/match1/Enemy2_left.png", "./media/images/match1/Enemy2_right.png", "./media/images/match1/BulletLeft.png", "./media/images/match1/BulletRight.png",sf::Vector2f(890.f,position-75.f-120.f)));
			coins.emplace_back(sf::Vector2f(950.f,position-35.f-120.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			platformsMobile.emplace_back(sf::Vector2f(1220.f,position-120.f),120.f*CoefSpeed,"./media/images/match1/plataformaSpace.png");
			coins.emplace_back(sf::Vector2f(1250.f,position-35.f-120.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
			enemyMatch.push_back(new Enemy2("./media/images/match1/Enemy2_left.png", "./media/images/match1/Enemy2_right.png", "./media/images/match1/BulletLeft.png", "./media/images/match1/BulletRight.png",sf::Vector2f(1310.f,position-75.f-120.f)));
			coins.emplace_back(sf::Vector2f(1370.f,position-35.f-120.f),-120.f*CoefSpeed,"./media/images/match1/star.png");
		}
		ItemClock.restart();
	}
	
	if (rand()% 1400  == 1) {
		sf::Vector2f positionInmortal(800.f, rand() % 250 + 250.f);  // Ajusta el rango vertical
		float inmortalSpeed = -120.f;  // Velocidad del booster (aj�stala seg�n sea necesario)
		inmortals.emplace_back(positionInmortal, inmortalSpeed * CoefSpeed,"./media/images/match1/InmortalBoost.png","./media/images/match1/InmortalBoost.png");
	}
	
	if (rand()% 1400  == 1) {
		sf::Vector2f positionLife(800.f, rand() % 450 + 50.f);  // Ajusta el rango vertical
		float lifeSpeed = -120.f;  // Velocidad del booster (aj�stala seg�n sea necesario)
		lifesBoost.emplace_back(positionLife, lifeSpeed * CoefSpeed,"./media/images/match1/SaludBooster.png");
	}
	
}


void Match1::generateRandomEnemy() {
	if (rand() % 600 == 1) {
		enemyMatch.push_back(new Enemy1("./media/images/match1/Enemy1_left.png", "./media/images/match1/Enemy1_right.png",sf::Vector2f(800.f,465.f)));
	} 
	
	if (rand() % 600 == 1 && pointCount > 100) {
		enemyMatch.push_back(new Enemy2("./media/images/match1/Enemy2_left.png", "./media/images/match1/Enemy2_right.png", "./media/images/match1/BulletLeft.png", "./media/images/match1/BulletRight.png",sf::Vector2f(800.f,425.f)));
	}
	
	if (rand() % 600 == 1 && pointCount > 200) {
		float positionAux = rand() % 250 + 50.f;
		enemyMatch.push_back(new Enemy3("./media/images/match1/Enemy3.png", positionAux));
	}
}

Match1::~Match1() {
	for (auto& enemy : enemyMatch) {
		delete enemy;
	}
}


