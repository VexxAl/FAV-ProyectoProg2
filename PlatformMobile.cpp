#include "PlatformMobile.h"

PlatformMobile::PlatformMobile(sf::Vector2f position, sf::Vector2f size, float speed)
	: Object("./media/stoneHalf.png"), speed(speed) {
	shape.setPosition(position);
	shape.setSize(size);
	shape.setFillColor(sf::Color::Green); // Puedes ajustar el color según sea necesario
}

void PlatformMobile::draw (sf::RenderWindow & window) {
	window.draw(m_sprite);
}

void PlatformMobile::update (float dt) {
	shape.move(-speed * dt, 0.f);
}

sf::RectangleShape PlatformMobile::getShape() const {
	return shape;
}
