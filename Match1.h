#ifndef MATCH1_H
#define MATCH1_H

#include "Coin.h"
#include "Scene.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Player.h"
#include "PlatformMobile.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "InmortalBooster.h"
#include "LifeBooster.h"


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
	
	void generateRandomEnemy();
	void enemy1Mecanic(float dt);
	void enemy2Mecanic(float dt);
	void enemy3Mecanic();
	
private:
	sf::Clock timer; 
	bool cooldown;
	sf::Text lifesText;
	std::vector<Enemy> enemylvl1;
	std::vector<Enemy2> enemylvl2;
	std::vector<Enemy3> enemylvl3;
	sf::Clock attackBullTimer;
	bool attackBull;
	
	sf::RectangleShape m_floor;
	Player m_player;
	sf::Texture textureMatch1;
	sf::Sprite spriteMatch1;
	
	std::vector<InmortalBooster> inmortals;
	
	std::vector<LifeBooster> lifesBoost;
	
	std::vector<PlatformMobile> platformsMobile;
	
	int pointCount;
	std::vector<Coin> coins;
	sf::Font font;
	sf::Text pointText;
	
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
