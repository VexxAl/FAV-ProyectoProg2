#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"

class Player : public Object {
public:
	Player(std::string fname,std::string jumpName, std::string leftName, std::string rightName);
	void update(sf::FloatRect platformBounds, float dt);
	void pausedPlayer();
	void resumePlayer();
	void rewindJump();
	
private:
	int jumpCount;
	bool SpacePresed;
	sf::Vector2f previousPosition;
	bool isPaused;
	
	sf::Texture jumpTex;
	sf::Texture leftTex;
	sf::Texture rightTex;
};

#endif
