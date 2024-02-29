#ifndef ENEMY1_H
#define ENEMY1_H

#include "Enemy.h"
#include "Player.h"


class Enemy1 : public Enemy {
public:
	Enemy1(std::string nameLeft,std::string nameRight);
	
	void update(float dt, Player &p) override;
	bool collideWithPlayer(Object &o) override;
	bool attackPlayer(Object &o) override;
	bool collideWithInmortal(Object &o) override;
	
private:
	sf::Texture rightTex;

	sf::SoundBuffer kill_enemy1_buffer;
	sf::Sound kill_enemy1_sound;
};

#endif

