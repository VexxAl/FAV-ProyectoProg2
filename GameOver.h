#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "Scene.h"
#include "Match2.h"
#include "Match1.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


class GameOver : public Scene {
public:
	GameOver(int score);
	
	void update(Game &game, float dt);
	void draw(sf::RenderWindow &window);
	
	void handleEvent(const sf::Event &event) override;

private:
	int matchScore; // Puntuación del juego
	
	sf::Texture textureGameOver;
	sf::Sprite spriteGameOver;

    sf::Text m_t1; // GAME OVER
    sf::Font m_font1; // Fuente para GAME OVER
    
	sf::Text m_t2; // SCORE: [score]
    sf::Font m_font2; // Fuente para SCORE: [score]
    
	std::vector<sf::Text> enteredLetters; // Letras ingresadas por el jugador
	sf::Text playerLetter;
	int letterSpacing = 10;

protected:
	void addLetter(char currentLetter) {			
		playerLetter.setString(currentLetter);
		playerLetter.setPosition(150 + enteredLetters.size() * 30 + letterSpacing, 300);
		enteredLetters.push_back(playerLetter);
	}

	void deleteLetter() {
		if (!enteredLetters.empty()) {
			enteredLetters.pop_back();
		}
	}

	void drawEnteredLetters(sf::RenderWindow &window) {
		for (size_t i = 0; i < enteredLetters.size(); i++) {
			window.draw(enteredLetters[i]);
		}
	}
};

#endif
