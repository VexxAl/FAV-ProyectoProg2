#ifndef BOSSSCENE_H
#define BOSSSCENE_H

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


class BossScene : public Match {
public:
	BossScene(std::string fname, std::string jumpName, std::string leftName,std::string rightName, std::string attackName, std::string boosterName, float e1, float e2);
	void update (Game & game, float dt);
	void draw (sf::RenderWindow & window);
	
	void generateRandomItems();
	void generateRandomEnemy();
	
private:
	sf::Texture bossTexture;
	sf::Sprite bossSprite;
};

#endif

