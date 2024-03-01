#ifndef ENEMY2_H
#define ENEMY2_H

#include "Enemy.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Enemy2 : public Enemy {
public:
	Enemy2(std::string nameLeft, std::string nameRight, std::string nameBulletLeft, std::string nameBulletRight, sf::Vector2f pos);

	void update(float dt, Player &p, float coef) override;
	bool attackPlayer(Object &o) override;
	bool collideWithPlayer(Object &o) override;
	bool collideWithInmortal(Object &o) override;
	
	void draw(sf::RenderWindow &window);
	
	void updateBullet(float dt, Player &p, float coef);
	
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
	
	sf::SoundBuffer shot_buffer;
	sf::Sound shot_sound;
};

#endif