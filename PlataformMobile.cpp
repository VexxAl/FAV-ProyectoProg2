#include "PlataformMobile.h"

PlataformMobile::PlataformMobile(sf::Vector2f position, sf::Vector2f size, float speed)
	: Object("./media/stoneHalf.png"), speed(speed) {
	shape.setPosition(position);
	shape.setSize(size);
	shape.setFillColor(sf::Color::Green); // Puedes ajustar el color según sea necesario
}

void PlataformMobile::draw (sf::RenderWindow & window) {
	window.draw(m_sprite);
}

void PlataformMobile::update (float dt) {
	shape.move(-speed * dt, 0.f);
}

sf::RectangleShape PlataformMobile::getShape() const {
	return shape;
}
