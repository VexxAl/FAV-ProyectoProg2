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
#include "InmortalBooster.h"
#include "LifeBooster.h"
#include "Enemy.h"
#include "Enemy1.h"
#include "Enemy3.h"
#include "Enemy2.h"


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
	
	void moveInmortal(float dt);
	void generateRandomBoosters();
	void despawnBoosters();
	
	void generateRandomItems();
	void despawnItems();
	void moveItems(float dt);
	
	void generateRandomEnemy();
	void enemy1Mecanic(float dt);
	void enemy2Mecanic(float dt);
	void enemy3Mecanic(float dt);
	
private:
	sf::Clock timer; 
	bool cooldown;
	sf::Text lifesText;
	std::vector<Enemy1> enemylvl1;
	std::vector<Enemy3> enemylvl3;
	std::vector<Enemy2> enemylvl2;
	sf::Clock attackBullTimer;
	bool attackBull;
	
	sf::RectangleShape m_floor;
	sf::Texture textureMatch2;
	sf::Sprite spriteMatch2;
	Player m_player;
	
	std::vector<PlatformMobile> platformsMobile;
	
	int coinCount=0;
	std::vector<Coin> coins;
	sf::Font font;
	sf::Text coinText;
	
	std::vector<InmortalBooster> inmortals;
	
	std::vector<LifeBooster> lifesBoost;
	
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
