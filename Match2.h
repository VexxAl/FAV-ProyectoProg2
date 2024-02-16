#ifndef MATCH2_H
#define MATCH2_H

#include "Scene.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "Player.h"

class Match2 : public Scene {
public:
	Match2();
	void update(Game &game) override;
	void draw(sf::RenderWindow &window) override;
private:
	sf::RectangleShape m_floor;
	Player m_player;
};

#endif
