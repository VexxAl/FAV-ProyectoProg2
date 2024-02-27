#ifndef ENEMY2_H
#define ENEMY2_H

#include "Enemy.h"

#include <SFML/Graphics.hpp>

class Enemy2 : public Enemy {
public:
	Enemy2(std::string nameLeft, std::string nameRight, std::string nameBulletLeft, std::string nameBulletRight);
	void update(float dt, Player &p);
	void drawBullet(sf::RenderWindow& window); // Metodo para dibujar la bala
	void updateBullet(float dt, Player &p);
	bool attackPlayer(Object &o);
	bool collideWithPlayer(Object &o);
	bool collideWithInmortal(Object &o);
	
private:
	sf::Texture rightTex;
	int speedBullet;
	bool left;
	bool leftEnemy2;
	
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
