#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"

#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>

class Player : public Object {
public:
	Player(std::string fname,std::string jumpName, std::string leftName, std::string rightName, std::string attackName, float e1, float e2);
	void update(sf::FloatRect platformBounds, float dt, bool cooldown);
	void rewindJump(bool cooldown);
	
	void loseLife();
	int getLifes();
	void updateLife();
	
	bool getInmortal();
	void clockInmortality();
	void setInmortal(bool inmortal);
	void updateInmortality(int aux);
	
	
private:
	int jumpCount;
	bool SpacePresed;
	sf::Vector2f previousPosition;
	bool isPaused;
	
	sf::Texture jumpTex;
	sf::Texture leftTex;
	sf::Texture rightTex;
	
	sf::Texture attackTex;
	int lifes;
	
	sf::SoundBuffer jump_buffer;
	sf::Sound jump_sound;

	sf::SoundBuffer hurt_buffer;
	sf::Sound hurt_sound;
	
	bool isInmortal;
	sf::Clock inmortalClock;
};

#endif
