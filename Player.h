#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"

#include <SFML/Audio.hpp>


class Player : public Object {
public:
	Player(std::string fname,std::string jumpName, std::string leftName, std::string rightName, float e1, float e2);
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

	sf::SoundBuffer jump_buffer;
	sf::Sound jump_sound;
};

#endif
