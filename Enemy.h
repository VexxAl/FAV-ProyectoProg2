#ifndef ENEMY_H
#define ENEMY_H

#include "Object.h"
#include "Player.h"


class Enemy : public Object {
public:
	Enemy(std::string nameLeft,std::string nameRight);
	void update(float dt, Player p);
	bool collideWithPlayer(Object &o);
	bool attackPlayer(Object &o);
	
	bool collideWithInmortal(Object &o);
	bool getMoveEnemy() const;
	bool getDespawnEnemy() const;
	void setMoveEnemy(bool taken);
	void setDespawnEnemy(bool taken);
private:
	sf::Texture rightTex;
	
	bool moveEnemy;
	bool despawnEnemy;

	sf::SoundBuffer kill_enemy1_buffer;
	sf::Sound kill_enemy1_sound;
};

#endif

