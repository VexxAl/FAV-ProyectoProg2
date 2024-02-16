#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"

class Player : public Object {
public:
	Player(std::string fname1);
	void update(sf::FloatRect platformBounds, float dt);
	void draw(sf::RenderWindow &window) override;
private:
	sf::Vector2f m_pos;
	sf::Vector2f m_speed;
	int jumpCount;
};

#endif
