#ifndef MATCH1_H
#define MATCH1_H

#include "Coin.h"
#include "Scene.h"
#include "Player.h"
#include "PlatformMobile.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


class Match1 : public Scene {
public:
	Match1();
	void update(Game &game, float dt) override;
	void draw(sf::RenderWindow &window) override;
	
	void generateRandomPlatformsMobile();
	void movePlatformsMobile(float dt); 
	
	void generateRandomCoins();
	void despawnCoins();
	void moveCoins(float dt);
	
private:
	sf::RectangleShape m_floor;
	Player m_player;
	sf::Texture textureMatch1;
	sf::Sprite spriteMatch1;
	
	std::vector<PlatformMobile> platformsMobile;
	
	int coinCount;
	std::vector<Coin> coins;
	sf::Font font;
	sf::Text coinText;
	
	sf::RectangleShape m_floorPause;
	sf::Font m_font;
	std::vector<sf::Text> m_options;
	int m_selectedOption;
	bool state;
	bool upPressed;
	bool downPressed;
	bool pause;
};

#endif
