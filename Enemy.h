#ifndef ENEMY_H
#define ENEMY_H
#include "Object.h"
#include "Player.h"

class Enemy : public Object {
public:
	Enemy(std::string nameLeft);

	virtual void update(float dt, Player &p)=0;
	virtual bool attackPlayer(Object &o)=0;
	virtual bool collideWithInmortal(Object &o)=0;
	virtual bool collideWithPlayer(Object &o)=0;
	
	bool getMoveEnemy() const;
	void setMoveEnemy(bool taken);
	bool getDespawnEnemy() const;
	void setDespawnEnemy(bool taken);
	
	
protected:
	sf::Texture rightTex;
	
	bool moveEnemy;
	bool despawnEnemy;
};

#endif

