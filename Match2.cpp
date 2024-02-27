#include "Game.h"
#include "Match2.h"

#include <SFML/Window/Keyboard.hpp>
#include <iostream>

Match2::Match2() : m_player("./media/images/match2/p2.png","./media/images/match2/p2_jumpPrueba.png",
							"./media/images/match2/p2_left.png","./media/images/match2/p2_right.png","./media/images/match2/p2_hurt.png",2.6f,2.6f) {
	m_floor.setSize({800.0, 100.0});
	m_floor.setPosition({0.0, 500.0});
	m_floor.setFillColor({0, 0, 0, 0});
	textureMatch2.loadFromFile("./media/images/match2/backgroundFAV.png");
	spriteMatch2.setTexture(textureMatch2);
	
	if (!font.loadFromFile("./media/fonts/PixelEmulator.ttf")) {
		std::cerr << "Error al cargar la fuente" << std::endl;
	}
	
	coinText.setFont(font);
	coinText.setCharacterSize(24);
	coinText.setFillColor(sf::Color::White);
	coinText.setPosition(10.f, 10.f);
	
	lifesText.setFont(font);
	lifesText.setCharacterSize(24);
	lifesText.setFillColor(sf::Color::Cyan);
	lifesText.setPosition(670.f, 10.f);
	
	m_floorPause.setPosition({200.0, 100.0});
	m_floorPause.setSize({400.0, 350.0});
	m_floorPause.setFillColor({20, 0, 100, 150});
	m_font.loadFromFile("./media/fonts/PixelGamer.otf");
	// Creación de las opciones del menú
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
}

void Match2::update(Game &game, float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && pause == false){
		pause = true;
		game.playEnterSound();
	}
	
	if (!pause){
		m_player.update(m_floor.getGlobalBounds(), dt, false);
		
		generateRandomItems();
		moveItems(dt);
		despawnItems();
		
	}
	
	if (pause) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !upPressed) {
			m_selectedOption = (m_selectedOption - 1 + m_options.size()) % m_options.size();
			upPressed = true;
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			upPressed = false;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !downPressed) {
			m_selectedOption = (m_selectedOption + 1) % m_options.size();
			downPressed = true;
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			downPressed = false;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			// Manejo de la opción seleccionada:
			if (m_selectedOption == 0) {
				pause = false;
			}
			else if (m_selectedOption == 1) {
				state = true;
				Scene* newScene = new Match2();
				game.setScene(newScene);
			}else if (m_selectedOption == 2) {
				state = true;
				Scene* newScene = new Menu();
				game.setScene(newScene);
			}
			
		}
	}
	
	for (auto& platform : platformsMobile) {
		if(m_player.collideWith(platform)){
			m_player.rewindJump(false);
		}
	}
	
	for (auto& coin : coins) {
		if (!coin.isTaken() && m_player.getGlobalBounds().intersects(coin.getGlobalBounds())) {
			coin.setTaken(true);
			coinCount++;
		}
	}
	
	for (auto& inmortal : inmortals) {
		if (!inmortal.isTakenB() && m_player.getGlobalBounds().intersects(inmortal.getGlobalBounds())) {
			inmortal.setTakenB(true);
			m_player.setInmortal(true);
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

void Match2::draw(sf::RenderWindow &window) {
	window.clear(sf::Color(150, 255, 255));
	window.draw(spriteMatch2);
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
	coinText.setString("Likes " + std::to_string(coinCount));
	window.draw(coinText);
	
	lifesText.setString("Lifes " + std::to_string(m_player.getLifes()));
	window.draw(lifesText);
	
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

void Match2::generateRandomItems(){
	// Genera plataformas móviles aleatorias en la derecha de la pantalla
	if (rand() % 200 == 0) {
		sf::Vector2f platformPosition(800.f, rand() % 200 + 120.f); // Ajusta el rango vertical
		float platformSpeed = static_cast<float>(rand() % 200 + 50); // Ajusta la velocidad según sea necesario
		platformsMobile.emplace_back(platformPosition, platformSpeed, "./media/images/match2/plataformaFAV.png");
	}
	// Genera monedas aleatorias en la derecha de la pantalla
	if (rand() % 100 == 1) {
		sf::Vector2f coinPosition(800.f, rand() % 450 + 50.f);  // Ajusta el rango vertical
		float coinSpeed = -100.f;  // Velocidad de la moneda (ajústala según sea necesario)
		coins.emplace_back(coinPosition, coinSpeed,"./media/images/match2/likeP.png");
	}
	
	if (rand()% 100  == 1) {
		sf::Vector2f positionInmortal(800.f, rand() % 450 + 50.f);  // Ajusta el rango vertical
		float inmortalSpeed = -100.f;  // Velocidad del booster (ajústala según sea necesario)
		inmortals.emplace_back(positionInmortal, inmortalSpeed,"./media/images/Repost-Booster.png");
	}
	
	if (rand()% 100  == 1) {
		sf::Vector2f positionLife(800.f, rand() % 450 + 50.f);  // Ajusta el rango vertical
		float lifeSpeed = -100.f;  // Velocidad del booster (ajústala según sea necesario)
		lifesBoost.emplace_back(positionLife, lifeSpeed,"./media/images/match2/Sprite-Heart.png");
	}
}

void Match2::despawnItems(){
	// Elimina las monedas que han salido de la pantalla por la izquierda
	coins.erase(std::remove_if(coins.begin(), coins.end(), [](const Coin& coin) {
		return coin.getPositionx() + coin.getWidth() < 0.f;
	}), coins.end());
	// Elimina las monedas que han salido de la pantalla por la izquierda
	inmortals.erase(std::remove_if(inmortals.begin(), inmortals.end(), [](const InmortalBooster& inmortal) {
		return inmortal.getPositionx() + inmortal.getWidth() < 0.f;
	}), inmortals.end());
	lifesBoost.erase(std::remove_if(lifesBoost.begin(), lifesBoost.end(), [](const LifeBooster& life) {
		return life.getPositionx() + life.getWidth() < 0.f;
	}), lifesBoost.end());
	
}

void Match2::moveItems(float dt){
	// Mueve las plataformas móviles de derecha a izquierda
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



