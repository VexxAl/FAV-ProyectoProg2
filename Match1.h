#ifndef MATCH1_H
#define MATCH1_H

#include "Coin.h"
#include "Scene.h"
#include "Match.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Player.h"
#include "PlatformMobile.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "InmortalBooster.h"
#include "LifeBooster.h"


class Match1 : public Match {
public:
	Match1(std::string fname,std::string jumpName, std::string leftName, std::string rightName, std::string attackName,std::string boosterName, float e1, float e2);
	void update(Game &game, float dt) override;
	void draw(sf::RenderWindow &window) override;
	
	void generateRandomItems();
	void generateRandomEnemy();
	
private:

};

#endif
