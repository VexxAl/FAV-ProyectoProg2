#ifndef BOSSSCENE_H
#define BOSSSCENE_H

#include "Match.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


class BossScene : public Match {
public:
	BossScene(std::string fname, std::string jumpName, std::string leftName,std::string rightName, std::string attackName, std::string boosterName, float e1, float e2);
	void update(Game &game, float dt) override;
	void draw(sf::RenderWindow &window) override;
	
	void generateRandomItems();
	void generateRandomEnemy();
	
	~BossScene();
private:
	sf::Texture bossTextureUp;
	sf::Texture bossTextureDown;
	sf::Sprite bossSprite;
	
	bool killPlayer;
	
	sf::Clock itemGenerationClock;
	float itemGenerationInterval;
};

#endif

