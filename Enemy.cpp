#include "Enemy.h"

Enemy::Enemy(std::string nameLeft) : Object(nameLeft), moveEnemy(true), despawnEnemy(false) {
}

bool Enemy::getMoveEnemy() const {
	return moveEnemy;
}

void Enemy::setMoveEnemy(bool aux) {
	this->moveEnemy = aux;
}

bool Enemy::getDespawnEnemy() const {
	return despawnEnemy;
}

void Enemy::setDespawnEnemy(bool aux) {
	this->despawnEnemy = aux;
}
