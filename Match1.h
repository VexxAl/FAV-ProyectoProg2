#ifndef MATCH1_H
#define MATCH1_H

#include "Scene.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "Player.h"
#include "PlatformMobile.h"



class Match1 : public Scene {
public:
	Match1();
	void update(Game &game, float dt) override;
	void draw(sf::RenderWindow &window) override;
	bool isMatch1() const override { return true; }
	
	void generateRandomPlatformsMobile();
	void movePlatformsMobile(float dt); 
private:
	sf::RectangleShape m_floor;
	Player m_player;
	sf::Texture textureMatch1;
	sf::Sprite spriteMatch1;
	
	std::vector<PlatformMobile> platformsMobile;
};

#endif
