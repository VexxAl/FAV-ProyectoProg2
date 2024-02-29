#ifndef MATCH1_H
#define MATCH1_H

#include "Match.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


class Match1 : public Match {
public:
	Match1(std::string fname,std::string jumpName, std::string leftName, std::string rightName, std::string attackName,std::string boosterName, float e1, float e2);
	void update(Game &game, float dt) override;
	void draw(sf::RenderWindow &window) override;
	
	void generateRandomItems();
	void generateRandomEnemy();
	
	~Match1();
private:
	
	bool QPressed;
	
};

#endif
