#ifndef MATCH2_H
#define MATCH2_H

#include "Scene.h"
#include "Player.h"
#include "PlatformMobile.h"
#include "Coin.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <vector>
#include <SFML/Graphics/Text.hpp>


class Match2 : public Scene {
public:
	Match2();
	void update(Game &game, float dt) override;
	void draw(sf::RenderWindow &window) override;
	
	void generateRandomPlatformsMobile();
	void movePlatformsMobile(float dt); 
	
	void generateRandomCoins();
	void despawnCoins();
	void moveCoins(float dt);

private:
	sf::RectangleShape m_floor;
	sf::Texture textureMatch2;
	sf::Sprite spriteMatch2;
	Player m_player;
	
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
