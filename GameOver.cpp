#include "GameOver.h"

GameOver::GameOver(int score) {
	matchScore = score;
	
	m_font1.loadFromFile("./media/fonts/PixelGamer.otf");
	m_font2.loadFromFile("./media/fonts/PixelEmulator.ttf");
	
	m_t1.setFont(m_font1);
	m_t1.setString("GAME OVER");
	m_t1.setFillColor({255, 0, 0});
	m_t1.setPosition(145, 75);
	m_t1.setCharacterSize(100);
	
	m_t2.setFont(m_font2);
	m_t2.setString("SCORE: " + std::to_string(matchScore));
	m_t2.setFillColor({255, 255, 255});
	m_t2.setPosition(150, 200);
	m_t2.setCharacterSize(50);
	
	playerName.setFont(m_font2);
	playerName.setFillColor({255, 255, 255});
	playerName.setPosition(150, 300);
	playerName.setCharacterSize(40);
	
	textureGameOver.loadFromFile("./media/images/backgroundSelect.jpg");
	spriteGameOver.setTexture(textureGameOver);
}

void GameOver::update(Game &game, float dt) {
	// Lógica de actualización si es necesario
}

bool GameOver::checkEvent(sf::RenderWindow &window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		} else if (event.type == sf::Event::TextEntered) {
			handleTextInput(event.text);
			textEntered = true;
		}
	}
	return textEntered;
}

void GameOver::draw(sf::RenderWindow &window) {
	window.clear();
	window.draw(spriteGameOver);
	window.draw(m_t1);
	window.draw(m_t2);
	window.draw(playerName); // Mostrar el nombre del jugador
}

void GameOver::handleTextInput(sf::Event::TextEvent textEvent) {
	if (textEvent.unicode < 128) {
		char typedChar = static_cast<char>(textEvent.unicode);
		if (typedChar == 8 && !inputText.empty()) {
			// Si es la tecla de retroceso y hay texto, elimina el último carácter
			inputText.pop_back();
		} else if (isprint(typedChar)) {
			// Si es un carácter imprimible, agrégalo al texto
			inputText.push_back(typedChar);
		}
		playerName.setString("Player: " + inputText);
	}
}
