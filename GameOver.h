#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "Scene.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>


class GameOver : public Scene {
public:
	GameOver(int score, bool isMatch2);
	
	void update(Game &game, float dt);
	void draw(sf::RenderWindow &window);
	
	void handleEvent(const sf::Event &event) override;

private:
	int matchScore; // Puntuación del juego
	bool match2;
	
	sf::Texture textureGameOver;
	sf::Sprite spriteGameOver;

    sf::Font go_f1; // Fuente para GAME OVER
    sf::Font go_f2; // Fuente para SCORE: [score]
    
    sf::Text go_t1; // GAME OVER
	sf::Text go_t2; // SCORE: [score]
	sf::Text go_t3;	// Playername: [letters]
	sf::Text go_t4;	// Back to Menu
	sf::Text go_t5; // Play again
	sf::Text go_t6; // Show Credits

	std::vector<sf::Text> enteredLetters; // Letras ingresadas por el jugador
	sf::Text playerLetter;

	bool file_saved;

	std::string getPlayerName() {
		std::string playerName;
		for (size_t i = 0; i < enteredLetters.size(); i++) {
			playerName += enteredLetters[i].getString();
		}
		return playerName;
	}

protected:
	void addLetter(char currentLetter) {			
		playerLetter.setString(currentLetter);
		playerLetter.setPosition(390 + enteredLetters.size() * 30, 300);
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

	void chargeFiles() {
		std::fstream ranking("ranking.txt", std::fstream::in | std::fstream::out);

		if (!ranking.is_open()) {
			std::cerr << "Error al abrir el archivo." << std::endl;
			return;
		}

		std::ostringstream ss;
		ss << std::setw(3) << std::setfill('0') << matchScore;
		std::string points = ss.str();

		std::string newLine = points + " " + getPlayerName();
		
		std::string line;
		std::vector<std::string> lines;
		while (std::getline(ranking, line)) {
			lines.push_back(line);
		}

		std::sort(lines.begin(), lines.end(), [](const std::string& a, const std::string& b) {
					return std::stoi(a.substr(0, 3)) > std::stoi(b.substr(0, 3));
		});

		for (size_t i = 0; i < lines.size(); i++) {
			if (std::stoi(points) >= std::stoi(lines[i].substr(0, 3))) {
				lines.pop_back();
				lines.push_back(newLine);
				std::sort(lines.begin(), lines.end(), [](const std::string& a, const std::string& b) {
					return std::stoi(a.substr(0, 3)) > std::stoi(b.substr(0, 3));
				});
				
				ranking.clear();
				ranking.seekp(0);
				for (size_t j = 0; j < lines.size(); j++) {
					ranking << lines[j] << std::endl;
				}

				file_saved = true;
				break;
			}
		}

		ranking.close();
	}

	void drawSaved(sf::RenderWindow &window) {
		if (file_saved) {
			sf::Text saved;
			saved.setFont(go_f2);
			saved.setString("Puntaje guardado!");
			saved.setFillColor({255,255,255});
			saved.setPosition(-1, -1);
			saved.setCharacterSize(10);

			window.draw(saved);
		}
	}
};

#endif
