#include "Game.h"
#include "Coin.h"
#include "Match1.h"
#include "PlatformMobile.h"

#include <SFML/Window/Keyboard.hpp>

#include <iostream>


Match1::Match1() : m_player("./media/images/match1/player.png", "./media/images/match1/p1_jump.png", "./media/images/match1/p1_left.png",
		"./media/images/match1/p1_right.png","./media/images/match1/p1_dead.png",1.0f,1.0f), pointCount(0) {
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

void Match1::update(Game &game, float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && pause == false){
		pause = true;
		game.playEnterSound();
	}

	if(m_player.getLifes() <= 0){
		GameOver* gameO= new GameOver(pointCount);
		game.setScene(gameO);
	}

	if (!pause){
		m_player.update(m_floor.getGlobalBounds(), dt, cooldown);
		generateRandomEnemy();
		enemy1Mecanic(dt);
		enemy2Mecanic(dt);
		enemy3Mecanic();
		generateRandomPlatformsMobile();
		movePlatformsMobile(dt);
		
		generateRandomCoins();
		despawnCoins();
		moveCoins(dt);
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
				Scene* newScene = new Match1();
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
		for (auto& enemy1 : enemylvl1) {
			enemy1.collideWith(platform);
		}
		for (auto& enemy2 : enemylvl2) {
			enemy2.collideWith(platform);
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
		m_player.updateInmortality(1);
	}
	
	for (auto& life : lifesBoost) {
		if (!life.isTakenB() && m_player.getGlobalBounds().intersects(life.getGlobalBounds())&& m_player.getLifes()<5) {
			life.setTakenB(true);
			m_player.updateLife();
		}
	}
}

void Match1::draw(sf::RenderWindow &window) {
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
	pointText.setString("Points " + std::to_string(pointCount));
	window.draw(pointText);
	
	for (auto& enemy1 : enemylvl1) {
		if(enemy1.getMoveEnemy() || !enemy1.getDespawnEnemy()){
			enemy1.draw(window);
		}
	}
	
	for (auto& enemy2 : enemylvl2) {
		if(enemy2.getMoveEnemy() || !enemy2.getDespawnEnemy()){
			enemy2.draw(window);
		}
		if(enemy2.getMoveEnemy()){
			enemy2.drawBullet(window);
		}
	}
	
	for (auto& enemy3 : enemylvl3) {
		if(enemy3.getMoveEnemy()){
			enemy3.draw(window);
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

void Match1::generateRandomPlatformsMobile() {
	// Genera plataformas moviles aleatorias en la derecha de la pantalla
	if (rand() % 200 == 0) {
		sf::Vector2f platformPosition(800.f, rand() % 200 + 120.f); // Ajusta el rango vertical
		float platformSpeed = static_cast<float>(rand() % 200 + 50); // Ajusta la velocidad segun sea necesario
		platformsMobile.emplace_back(platformPosition, platformSpeed, "./media/images/match1/plataformaSpace.png");
	}
}

void Match1::movePlatformsMobile(float dt) {
	// Mueve las plataformas mï¿½viles de derecha a izquierda
	for (auto& platform : platformsMobile) {
		platform.update(dt);
	}
}

void Match1::moveCoins(float dt) {
	// Mueve las monedas de derecha a izquierda
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

void Match1::generateRandomCoins() {
	// Genera monedas aleatorias en la derecha de la pantalla
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
		lifesBoost.emplace_back(positionLife, lifeSpeed,"./media/images/match2/Sprite-Heart.png");
	}
}

void Match1::despawnCoins() {
	// Elimina las monedas que han salido de la pantalla por la izquierda
	coins.erase(std::remove_if(coins.begin(), coins.end(), [](const Coin& coin) {
		return coin.getPositionx() + coin.getWidth() < 0.f;
	}), coins.end());
}

void Match1::generateRandomEnemy() {
	// Genera monedas aleatorias en la derecha de la pantalla
	if (rand() % 800 == 1) {
		enemylvl1.emplace_back("./media/images/match1/Enemy1_left.png","./media/images/match1/Enemy1_right.png");
	} 
	
	if (rand() % 800 == 1) {
		enemylvl2.emplace_back("./media/images/match1/Enemy2_left.png","./media/images/match1/Enemy2_right.png","./media/images/match1/BulletLeft.png","./media/images/match1/BulletRight.png");
	}
	
	if (rand() % 800 == 1) {
		float positionAux = rand() % 250 + 50.f;
		enemylvl3.emplace_back("./media/images/match1/Enemy3.png", positionAux);
	}
}

void Match1::enemy1Mecanic(float dt){
	for (auto& enemy1 : enemylvl1) {
		if(enemy1.getMoveEnemy()){
			enemy1.update(dt,m_player);
			if(!m_player.getInmortal()){
				if(enemy1.collideWithPlayer(m_player)){
					enemy1.setMoveEnemy(false);
					timer.restart();
				} else if(enemy1.attackPlayer(m_player) && cooldown == false ){
					m_player.loseLife();
					cooldown = true;
					timer.restart();
				}
			}
			if(m_player.getInmortal() && enemy1.collideWithInmortal(m_player)){
				enemy1.setMoveEnemy(false);
				timer.restart();
			}
		}
		if(timer.getElapsedTime() >= sf::seconds(0.6) && cooldown == true) cooldown = false;
		if(!enemy1.getMoveEnemy()){
			if (timer.getElapsedTime() >= sf::seconds(3)) {
				// Llama al método que deseas activar después de 10 segundos
				enemy1.setDespawnEnemy(true);
				
			} 
		}
	}
}

void Match1::enemy2Mecanic(float dt){
	for (auto& enemy2 : enemylvl2) {
		if(enemy2.getMoveEnemy()){
			enemy2.update(dt,m_player);
			if(!m_player.getInmortal()){
				if(enemy2.collideWithPlayer(m_player)){
					enemy2.setMoveEnemy(false);
					timer.restart();
				} else if(enemy2.attackPlayer(m_player) && cooldown == false){
					m_player.loseLife();
					cooldown = true;
					timer.restart();
				}
			}
			if(m_player.getInmortal() && enemy2.collideWithInmortal(m_player)){
				enemy2.setMoveEnemy(false);
				timer.restart();
			}
		}
		if(timer.getElapsedTime() >= sf::seconds(0.6) && cooldown == true) cooldown = false;
		if(!enemy2.getMoveEnemy()){
			if (timer.getElapsedTime() >= sf::seconds(3)) {
				// Llama al método que deseas activar después de 10 segundos
				enemy2.setDespawnEnemy(true);
			} 
		}
	}
}

void Match1::enemy3Mecanic(){
	for (auto& enemy3 : enemylvl3) {
		enemy3.update();
		if(!m_player.getInmortal()){
			if(enemy3.attackPlayer(m_player) && cooldown == false){
				if(!m_player.getInmortal()){
					m_player.loseLife();
					cooldown = true;
					timer.restart();
				}
			}
		}
		if(m_player.getInmortal() && enemy3.collideWithInmortal(m_player)){
			enemy3.setMoveEnemy(false);
			timer.restart();
		}
		if(timer.getElapsedTime() >= sf::seconds(0.6) && cooldown == true) cooldown = false;
	}
}


