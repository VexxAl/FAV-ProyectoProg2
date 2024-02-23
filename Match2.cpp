#include "Game.h"
#include "Match2.h"

#include <SFML/Window/Keyboard.hpp>
#include <iostream>

Match2::Match2() : m_player("./media/images/match2/p2.png","./media/images/match2/p2_jumpPrueba.png",
		"./media/images/match2/p2_left.png","./media/images/match2/p2_right.png",2.6f,2.6f) {
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
}

void Match2::update(Game &game, float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && pause == false){
		pause = true;
		game.playEnterSound();
	}
	
	if (!pause){
		m_player.update(m_floor.getGlobalBounds(), dt);
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
				game.playMatch2Music();
				
				state = true;
				Scene* newScene = new Match2();
				game.setScene(newScene);
			}
			else if (m_selectedOption == 2) {
				game.stopMatch2Music();
				game.playMenuMusic();
				
				state = true;
				Scene* newScene = new Menu();
				game.setScene(newScene);
			}
			
		}
	}
	
	for (auto& platform : platformsMobile) {
		if(m_player.collideWith(platform)){
			m_player.rewindJump();
		}
	}
	
	for (auto& coin : coins) {
		coinCount=0;
		if (!coin.isTaken() && m_player.getGlobalBounds().intersects(coin.getGlobalBounds())) {
			game.playCoinSound();

			coin.setTaken(true);
			coinCount++;
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

void Match2::generateRandomPlatformsMobile() {
	// Genera plataformas moviles aleatorias en la derecha de la pantalla
	if (rand() % 200 == 0) {
		sf::Vector2f platformPosition(800.f, rand() % 200 + 120.f); // Ajusta el rango vertical
		float platformSpeed = static_cast<float>(rand() % 200 + 50); // Ajusta la velocidad seg�n sea necesario
		platformsMobile.emplace_back(platformPosition, platformSpeed, "./media/images/match2/plataformaFAV.png");
	}
}

void Match2::movePlatformsMobile(float dt) {
	// Mueve las plataformas moviles de derecha a izquierda
	for (auto& platform : platformsMobile) {
		platform.update(dt);
	}
}

void Match2::moveCoins(float dt) {
	// Mueve las monedas de derecha a izquierda
	for (auto& coin : coins) {
		coin.update(dt);
	}
}

void Match2::generateRandomCoins() {
	// Genera monedas aleatorias en la derecha de la pantalla
	if (rand() % 100 == 1) {
		sf::Vector2f coinPosition(800.f, rand() % 450 + 50.f);  // Ajusta el rango vertical
		float coinSpeed = -100.f;  // Velocidad de la moneda (aj�stala seg�n sea necesario)
		coins.emplace_back(coinPosition, coinSpeed,"./media/images/match2/Sprite-Heart.png");
	}
}

void Match2::despawnCoins() {
	// Elimina las monedas que han salido de la pantalla por la izquierda
	coins.erase(std::remove_if(coins.begin(), coins.end(), [](const Coin& coin) {
		return coin.getPositionx() + coin.getWidth() < 0.f;
	}), coins.end());
}

