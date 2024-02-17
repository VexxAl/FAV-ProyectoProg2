#ifndef MATCH2_H
#define MATCH2_H

#include "Scene.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "Player.h"

class Match2 : public Scene {
public:
	Match2();
	void update(Game &game, float dt) override;
	void draw(sf::RenderWindow &window) override;
	bool isMatch1() const override { return false; }
private:
	sf::RectangleShape m_floor;
	sf::Texture textureMatch2;
	sf::Sprite spriteMatch2;
	Player m_player;
};

#endif
