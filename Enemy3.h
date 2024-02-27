#ifndef ENEMY3_H
#define ENEMY3_H
#include "Object.h"

class Enemy3 : public Object {
public:
	Enemy3(std::string nameLeft, float pos);
	void update();
	bool attackPlayer(Object &o);
private:
	sf::Texture rightTex;
	bool up;
};

#endif
