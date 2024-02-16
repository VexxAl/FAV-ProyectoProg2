#include "Object.h"

Object::Object(std::string fname) {
	m_texture.loadFromFile(fname);
	m_sprite.setTexture(m_texture);
}

void Object::draw(sf::RenderWindow &window) {
	window.draw(m_sprite);
}

bool Object::collideWith(const Object &o) const {
	auto r1 = m_sprite.getGlobalBounds();
	auto r2 = o.m_sprite.getGlobalBounds();
	return r1.intersects(r2);
}

void Object::update(float dt) {
	// Lógica de actualización genérica, puedes personalizarla en las clases derivadas
}
