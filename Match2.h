#ifndef MATCH2_H
#define MATCH2_H

#include "Coin.h"
#include "Scene.h"
#include "Enemy.h"
#include "Match.h"
#include "Player.h"
#include "Enemy1.h"
#include "Enemy3.h"
#include "Enemy2.h"
#include "LifeBooster.h"
#include "PlatformMobile.h"
#include "InmortalBooster.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <vector>
#include <SFML/Graphics/Text.hpp>



class Match2 : public Match {
public:
	Match2(std::string fname,std::string jumpName, std::string leftName, std::string rightName, std::string attackName,std::string boosterName, float e1, float e2);
	void update(Game &game, float dt) ;
	void draw(sf::RenderWindow &window);
	
	void generateRandomItems();
	void generateRandomEnemy();
	
	~Match2();
private:
	sf::Clock ItemClock;
	
};

#endif
