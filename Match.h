#ifndef MATCH_H
#define MATCH_H
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Scene.h"
#include "Ball.h"
#include "Player.h"

class Match {
public:
	Match();
	void Update(Game &game) override;
	void Draw(sf::RenderWindow &window) override;
private:
	Player m_player;
	Plataform m_plataform;
};

#endif

