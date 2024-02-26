#ifndef LIFEBOOSTER_H
#define LIFEBOOSTER_H
#include "Object.h"
#include "Player.h"

class LifeBooster : public Object {
public:
	LifeBooster(sf::Vector2f position, float speed, std::string fname);
	bool isTakenB() const {return taken;}
	void setTakenB(bool taken);
	void update (float dt);
private:
	bool taken;
	float speed;
};

#endif

