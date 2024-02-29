#ifndef MATCH_H
#define MATCH_H

#include "Coin.h"
#include "Scene.h"
#include "Enemy.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Player.h"
#include "PlatformMobile.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "InmortalBooster.h"
#include "LifeBooster.h"


class Match : public Scene {
public:
	Match(std::string fname,std::string jumpName, std::string leftName, std::string rightName, std::string attackName,std::string boosterName, float e1, float e2);
	
	virtual void update(Game &game, float dt);
	virtual void draw(sf::RenderWindow &window);
	
	void despawnItems();
	void moveItems(float dt);
	
	void enemyMecanic(float dt);
	
	~Match();
	
protected:
	sf::Clock timer; 
	bool cooldown;
	sf::Text lifesText;
	std::vector<Enemy*> enemyMatch;
	sf::Clock attackBullTimer;
	bool attackBull;
	
	sf::RectangleShape m_floor;
	Player m_player;
	sf::Texture textureMatch;
	sf::Sprite spriteMatch;
	
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
