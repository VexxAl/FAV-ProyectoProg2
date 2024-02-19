#ifndef PLATFORMMOBILE_H
#define PLATFORMMOBILE_H
#include "Object.h"
#include <SFML/Graphics/RectangleShape.hpp>

class PlatformMobile : public Object {
public:
	PlatformMobile(sf::Vector2f position, sf::Vector2f size, float speed);
	sf::RectangleShape getShape() const;
	void draw (sf::RenderWindow & window) override;
	void update (float dt);
private:
	sf::RectangleShape shape;
	float speed;
};

#endif
