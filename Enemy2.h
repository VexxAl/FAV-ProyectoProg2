#ifndef ENEMY2_H
#define ENEMY2_H

#include "Enemy.h"

#include <SFML/Graphics.hpp>

class Enemy2 : public Enemy {
public:
	Enemy2(std::string nameLeft, std::string nameRight, std::string nameBulletLeft, std::string nameBulletRight);

	void update(float dt, Player &p) override;
	bool attackPlayer(Object &o) override;
	bool collideWithPlayer(Object &o) override;
	bool collideWithInmortal(Object &o) override;
	
	void draw(sf::RenderWindow &window);
	
	void updateBullet(float dt, Player &p);
	
private:
	sf::Texture rightTex;
	
	bool left;
	bool leftEnemy2;
	
	sf::Vector2f posBullet;
	int speedBullet;
	sf::Texture BulletTexRight;
	sf::Texture BulletTexLeft;
	sf::Sprite Bullet;
	sf::Clock bulletTimer; // Temporizador para el intervalo entre disparos

	sf::SoundBuffer kill_enemy2_buffer;
	sf::Sound kill_enemy2_sound;

	sf::SoundBuffer shot_buffer;
	sf::Sound shot_sound;
};

#endif
