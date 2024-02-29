#include "Game.h"
#include "Coin.h"
#include "Match.h"
#include "PlatformMobile.h"
#include <typeinfo>

#include <SFML/Window/Keyboard.hpp>

#include <iostream>
#include "GameOver.h"
#include "Enemy.h"


Match::Match(std::string fname,std::string jumpName, std::string leftName, std::string rightName, std::string attackName,std::string boosterName, float e1, float e2)
	:  m_player(fname,jumpName,leftName,rightName, attackName,boosterName,e1,e2), pointCount(0) {
	m_floor.setSize({800.0, 100.0});
	m_floor.setPosition({0.0, 500.0});
	m_floor.setFillColor({0, 0, 0, 0});
	textureMatch1.loadFromFile("./media/images/match1/backgroundSpace.png");
	spriteMatch1.setTexture(textureMatch1);
	
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
	
	// Creacion de las opciones del menu
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
}

void Match::update(Game &game, float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && pause == false){
		pause = true;
		game.playEnterSound();
	}
	
	if(m_player.getLifes() <= 0){
		GameOver* gameO= new GameOver(pointCount);
		game.setScene(gameO);
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
	
	for (auto& platform : platformsMobile) {
		if(m_player.collideWith(platform)){
			m_player.rewindJump(cooldown);
		}
		for (Enemy* enemy : enemyMatch) {
			// Verificar si el objeto no es de tipo Enemy3
			if (typeid(*enemy) != typeid(Enemy3)) {
				// Llamar a collideWith solo para objetos que no son de tipo Enemy3
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
		}
		m_player.updateInmortality();
	}
	
	for (auto& life : lifesBoost) {
		if (!life.isTakenB() && m_player.getGlobalBounds().intersects(life.getGlobalBounds())&& m_player.getLifes()<5) {
			life.setTakenB(true);
			m_player.updateLife();
		}
	}
}

void Match::draw(sf::RenderWindow &window) {
	window.clear(sf::Color(150, 255, 255));
	window.draw(spriteMatch1);
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
	// Mueve las plataformas moviles de derecha a izquierda
	for (auto& platform : platformsMobile) {
		platform.update(dt);
	}
	// Mueve las monedas de derecha a izquierda
	for (auto& coin : coins) {
		coin.update(dt);
	}
	// Mueve las monedas de derecha a izquierda
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
			enemy->update(dt,m_player);
			if(!m_player.getInmortal()){
				if(enemy->collideWithPlayer(m_player)){
					enemy->setMoveEnemy(false);
					timer.restart();
				} else if(enemy->attackPlayer(m_player) && cooldown == false ){
					m_player.loseLife();
					cooldown = true;
					timer.restart();
				}
			}
			if(m_player.getInmortal() && enemy->collideWithInmortal(m_player)){
				enemy->setMoveEnemy(false);
				timer.restart();
			}
		}
		if(timer.getElapsedTime() >= sf::seconds(0.6) && cooldown == true) cooldown = false;
		if(!enemy->getMoveEnemy()){
			if (timer.getElapsedTime() >= sf::seconds(3)) {
				// Llama al m�todo que deseas activar despu�s de 10 segundos
				enemy->setDespawnEnemy(true);
				
			} 
		}
	}
}


Match::~Match() {

}
