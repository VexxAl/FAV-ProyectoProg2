#ifndef ENEMY1_H
#define ENEMY1_H

#include "Enemy.h"
#include "Player.h"

#include <SFML/System/Vector2.hpp>


class Enemy1 : public Enemy {
public:
	Enemy1(std::string nameLeft,std::string nameRight, sf::Vector2f pos);
	
	void update(float dt, Player &p, float coef) override;
	bool collideWithPlayer(Object &o) override;
	bool attackPlayer(Object &o) override;
	bool collideWithInmortal(Object &o) override;
	
private:
	sf::Texture rightTex;
};

#endif
