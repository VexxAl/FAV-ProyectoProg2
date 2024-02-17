#ifndef MATCH1_H
#define MATCH1_H

#include "Scene.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "Player.h"
#include "PlataformMobile.h"



class Match1 : public Scene {
public:
	Match1();
	void update(Game &game, float dt) override;
	void draw(sf::RenderWindow &window) override;
	bool isMatch1() const override { return true; }
private:
	sf::RectangleShape m_floor;
	Player m_player;
	sf::Texture textureMatch1;
	sf::Sprite spriteMatch1;
	
	void generateRandomPlatformsMobile(); // Nueva función
	void movePlatformsMobile(float dt); 
	std::vector<PlataformMobile> platformsMobile;
};

#endif
