#ifndef COIN_H
#define COIN_H
#include "Object.h"
#include <SFML/Graphics/CircleShape.hpp>


class Coin : public Object {
public:
	Coin(sf::Vector2f position, float speed);
	bool isTaken() const;
	void setTaken(bool taken);
	void update (float dt);
	
private:
	bool taken;
	float speed;
};

#endif

