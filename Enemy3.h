#ifndef ENEMY3_H
#define ENEMY3_H
#include "Enemy.h"

class Enemy3 : public Enemy {
public:
	Enemy3(std::string nameLeft, float pos);
	
	void update(float dt, Player &p) override;
	bool attackPlayer(Object &o) override;
	bool collideWithInmortal(Object &o) override;
	bool collideWithPlayer(Object &o) override;
	
	void draw(sf::RenderWindow &window);
	
private:
	bool up;
};

#endif
