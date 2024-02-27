
#define GAMEOVER_H
#include "Scene.h"
#include "Match2.h"
#include "Match1.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <SFML/Window/Event.hpp>
#include <SFML/System/String.hpp>

class GameOver : public Scene {
public:
	GameOver(int score);
	void update(Game &game, float dt);
	bool checkEvent(sf::RenderWindow &window);
	void draw(sf::RenderWindow &window);
	
private:
	int matchScore;
	sf::Font m_font1;
	sf::Font m_font2;
	sf::Text m_t1;
	sf::Text m_t2;
	sf::Text playerName;
	std::string inputText;
	bool textEntered = false;
	sf::Texture textureGameOver;
	sf::Sprite spriteGameOver;
	
	void handleTextInput(sf::Event::TextEvent textEvent);
};

