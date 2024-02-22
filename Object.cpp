#include "Object.h"

#include <SFML/Window/Keyboard.hpp>

#include <iostream>


Object::Object(std::string fname) {
	m_texture.loadFromFile(fname);
	m_sprite.setTexture(m_texture);
}

void Object::draw(sf::RenderWindow &window) {
	window.draw(m_sprite);
}

void Object::update(float dt) {
	// L�gica de actualizaci�n gen�rica, puedes personalizarla en las clases derivadas
}

bool Object::collideWith(Object &o) {
	auto r1 = m_sprite.getGlobalBounds();
	auto r2 = o.m_sprite.getGlobalBounds();
	if (r1.intersects(r2)) {
		// Verifica si el jugador est� encima de la plataforma
		if (r1.top + r1.height < r2.top + 0.9f * r2.height) {
			// El jugador cae sobre la plataforma
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
				m_pos.y = r2.top - r1.height;
				m_speed.y = 0.0f;
				return true;
			}
		} else {
			// El jugador choca por debajo de la plataforma y cae
			m_pos.y = r2.top + r2.height;  // Ajusta la posici�n del jugador debajo de la plataforma
			m_speed.y += 500.f;  // Simula la gravedad aumentando la velocidad hacia abajo
			return false;
		}
		return false;
	}
	return false;
}

sf::FloatRect Object::getGlobalBounds() {
	return m_sprite.getGlobalBounds();
}

float Object::getPositionx() const{
	return m_pos.x;
}

float Object::getWidth() const{
	return m_sprite.getGlobalBounds().width;
}

