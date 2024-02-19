#ifndef PLATFORMMOBILE_H
#define PLATFORMMOBILE_H
#include "Object.h"
#include <SFML/Graphics/RectangleShape.hpp>

class PlatformMobile : public Object {
public:
	PlatformMobile(sf::Vector2f position, float speed);
	void draw (sf::RenderWindow & window) override;
	void update (float dt);
private:
	float speed;
};

#endif

