#include "GameOver.h"

#include <iostream>


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

    playerLetter.setFont(m_font2);
    playerLetter.setFillColor({255, 255, 255});
    playerLetter.setCharacterSize(30);
    
    textureGameOver.loadFromFile("./media/images/backgroundSelect.jpg");
    spriteGameOver.setTexture(textureGameOver);
}

void GameOver::update(Game &game, float dt) {}

void GameOver::draw(sf::RenderWindow &window) {
	window.clear();
	window.draw(spriteGameOver);
	window.draw(m_t1);
	window.draw(m_t2);
    drawEnteredLetters(window);    
}

void GameOver::handleEvent(const sf::Event &event) {
	if (event.type == sf::Event::TextEntered) {
		if (event.text.unicode >= 'A' && event.text.unicode <= 'z' && enteredLetters.size() < 3) {
            addLetter(static_cast<char>(event.text.unicode));
		}
    } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace) {
        deleteLetter();
    }
}
