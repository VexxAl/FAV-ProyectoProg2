#ifndef ENEMY3_H
#define ENEMY3_H
#include "Object.h"

class Enemy3 : public Object {
public:
	Enemy3(std::string nameLeft, float pos);
	void update();
	bool attackPlayer(Object &o);
	bool collideWithInmortal(Object &o);
	bool getMoveEnemy() const;
	void setMoveEnemy(bool taken);
private:
	sf::Texture rightTex;
	bool up;
	
	bool moveEnemy;
};

#endif
