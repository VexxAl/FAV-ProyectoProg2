#include "Game.h"
#include "Coin.h"
#include "Match.h"
#include "Enemy.h"
#include "GameOver.h"
#include "PlatformMobile.h"

#include <SFML/Window/Keyboard.hpp>

#include <typeinfo>
#include <iostream>


Match::Match(std::string fname,std::string jumpName, std::string leftName, std::string rightName, std::string attackName,std::string boosterName, float e1, float e2)
	:  m_player(fname,jumpName,leftName,rightName, attackName,boosterName,e1,e2), pointCount(0), CoefSpeed(1.f) {
	m_floor.setSize({800.0, 100.0});
	m_floor.setPosition({0.0, 500.0});
	m_floor.setFillColor({0, 0, 0, 0});

	
	if (!font.loadFromFile("./media/fonts/PixelEmulator.ttf")) {
		std::cerr << "Error al cargar la fuente" << std::endl;
	}
	
	pointText.setFont(font);
	pointText.setCharacterSize(24);
	pointText.setFillColor(sf::Color::White);
	pointText.setPosition(10.f, 10.f);
	
	lifesText.setFont(font);
	lifesText.setCharacterSize(24);
	lifesText.setFillColor(sf::Color::Cyan);
	lifesText.setPosition(670.f, 10.f);
	
	m_floorPause.setPosition({200.0, 100.0});
	m_floorPause.setSize({400.0, 350.0});
	m_floorPause.setFillColor({20, 0, 100, 150});
	m_font.loadFromFile("./media/fonts/PixelGamer.otf");
	
	std::vector<std::string> optionNames = {"Reanudar","Reiniciar" ,"Salir al menu"};
	for (int i = 0; i < optionNames.size(); i++) {
		sf::Text text;
		text.setFont(m_font);
		text.setString(optionNames[i]);
		text.setPosition(300, i * 100 + 150);
		m_options.push_back(text);
	}
	m_selectedOption = 0;
	upPressed = false;
	downPressed = false;
	state = false;
	cooldown = false;
	attackBull = false;
	isMatch2 = false;
}

void Match::update(Game &game, float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && pause == false){
		pause = true;
		game.playEnterSound();
	}
	
	if(m_player.getLifes() <= 0){
		game.stopMatch1Music();
		game.stopMatch2Music();
		game.stopBossMusic();
		game.playGameOverSound();
		
		Scene* gameO= new GameOver(pointCount, isMatch2);
		game.setScene(gameO);
	}
	
	
	for (auto& platform : platformsMobile) {
		if(m_player.collideWith(platform)){
			m_player.rewindJump(cooldown);
		}
		for (Enemy* enemy : enemyMatch) {
			if (typeid(*enemy) != typeid(Enemy3)) {
				enemy->collideWith(platform);
			}
		}
	}
	
	for (auto& coin : coins) {
		if (!coin.isTaken() && m_player.getGlobalBounds().intersects(coin.getGlobalBounds())) {
			game.playCoinSound();
			coin.setTaken(true);
			pointCount++;
		}
	}
	
	for (auto& inmortal : inmortals) {
		if (!inmortal.isTakenB() && m_player.getGlobalBounds().intersects(inmortal.getGlobalBounds())) {
			inmortal.setTakenB(true);
			m_player.setInmortal(true);
			m_player.clockInmortality();
			pointCount++;
		}
		m_player.updateInmortality();
	}
	
	for (auto& life : lifesBoost) {
		if (!life.isTakenB() && m_player.getGlobalBounds().intersects(life.getGlobalBounds())&& m_player.getLifes()<5) {
			life.setTakenB(true);
			m_player.updateLife();
			pointCount++;
		}
	}
}

void Match::draw(sf::RenderWindow &window) {
	window.clear(sf::Color(150, 255, 255));
	window.draw(spriteMatch);
	window.draw(m_floor);
	m_player.draw(window);
	
	for (auto& platform : platformsMobile) {
		platform.draw(window);
	}
	
	for (auto& coin : coins) {
		if (!coin.isTaken()) {
			coin.draw(window);
		}
	}
	
	window.draw(pointText);
	
	for (Enemy* enemy : enemyMatch) {
		if(enemy->getMoveEnemy() || !enemy->getDespawnEnemy()){
			enemy->draw(window);
		}
	}
	
	for (auto& inmortal : inmortals) {
		if (!inmortal.isTakenB()) {
			inmortal.draw(window);
		}
		if(m_player.getInmortal()){
			window.draw(inmortal.getSprite());
		}
	}
	
	for(auto& life: lifesBoost){
		if(!life.isTakenB()){
			life.draw(window);
		}
	}
	
	lifesText.setString("Lifes " + std::to_string(m_player.getLifes()));
	window.draw(lifesText);
	
	if (pause){
		window.draw(m_floorPause);
		for (int i = 0; i < m_options.size(); i++) {
			if (i == m_selectedOption) {
				m_options[i].setFillColor({136, 0, 208});
			} else {
				m_options[i].setFillColor(sf::Color::White);
			}
			window.draw(m_options[i]);
		}
	}
}

void Match::moveItems(float dt){
	for (auto& platform : platformsMobile) {
		platform.update(dt);
	}
	for (auto& coin : coins) {
		coin.update(dt);
	}
	for (auto& inmortal : inmortals) {
		inmortal.update(dt);
	}
	
	for(auto& life : lifesBoost) {
		life.update(dt);
	}
}


void Match::despawnItems(){
	
	platformsMobile.erase(std::remove_if(platformsMobile.begin(), platformsMobile.end(), [](const PlatformMobile& platformsMobile) {
		return platformsMobile.getPositionx() + platformsMobile.getWidth() < 0.f;
	}), platformsMobile.end());
	
	coins.erase(std::remove_if(coins.begin(), coins.end(), [](const Coin& coin) {
		return coin.getPositionx() + coin.getWidth() < 0.f;
	}), coins.end());

	inmortals.erase(std::remove_if(inmortals.begin(), inmortals.end(), [](const InmortalBooster& inmortal) {
		return inmortal.getPositionx() + inmortal.getWidth() < 0.f;
	}), inmortals.end());
	
	lifesBoost.erase(std::remove_if(lifesBoost.begin(), lifesBoost.end(), [](const LifeBooster& life) {
		return life.getPositionx() + life.getWidth() < 0.f;
	}), lifesBoost.end());
	
	enemyMatch.erase(std::remove_if(enemyMatch.begin(), enemyMatch.end(), [](const Enemy* enemy) {
		return !(enemy->getMoveEnemy() || !enemy->getDespawnEnemy());
	}), enemyMatch.end());
	
}


void Match::enemyMecanic(float dt){
	for (Enemy* enemy : enemyMatch) {
		if(enemy->getMoveEnemy()){
			enemy->update(dt,m_player, CoefSpeed);
			if(!m_player.getInmortal()){
				if(enemy->collideWithPlayer(m_player)){		
					pointCount += 5;
					enemy->setMoveEnemy(false);
					timer.restart();
					
					if (typeid(*enemy) == typeid(Enemy1)) {
						kill_enemy1_sound.play();
					}
					else if (typeid(*enemy) == typeid(Enemy2)) {
						kill_enemy2_sound.play();
					}
				} else if(enemy->attackPlayer(m_player) && cooldown == false ){
					m_player.loseLife();
					cooldown = true;
					timer.restart();
				}
			}
			if(m_player.getInmortal() && enemy->collideWithInmortal(m_player)){
				pointCount += 3;
				enemy->setMoveEnemy(false);
				timer.restart();
				
				if (typeid(*enemy) == typeid(Enemy1)) {
					kill_enemy1_sound.play();
				}
				else if (typeid(*enemy) == typeid(Enemy2)) {
					kill_enemy2_sound.play();
				}	
			}
		}
		if(timer.getElapsedTime() >= sf::seconds(0.6) && cooldown == true) cooldown = false;
		if(!enemy->getMoveEnemy()){
			if (timer.getElapsedTime() >= sf::seconds(3)) {
				enemy->setDespawnEnemy(true);
				
			} 
		}
	}
}


Match::~Match() {

}

