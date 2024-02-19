// Object.h
#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>

class Object {
public:
	Object(std::string fname);
	virtual void draw(sf::RenderWindow &window);
	virtual void update(float dt); // Método de actualización virtual
	bool collideWith(const Object &o) const;
protected:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

#endif

