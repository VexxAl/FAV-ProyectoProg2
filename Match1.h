#ifndef MATCH1_H
#define MATCH1_H

#include "Scene.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "Player.h"

class Match1 : public Scene {
public:
	Match1();
	void update(Game &game) override;
	void draw(sf::RenderWindow &window) override;
private:
	sf::RectangleShape m_floor;
	Player m_player;
};

#endif
