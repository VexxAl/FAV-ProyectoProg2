#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <string>

class Object {
public:
	Object(std::string fname);
	virtual void draw(sf::RenderWindow &window);
	virtual void update(float dt); // Metodo de actualizacion virtual
	bool collideWith(Object &o);
	sf::FloatRect getGlobalBounds();
	float getPositionx() const;
	float getWidth() const;
	
protected:
	sf::Vector2f m_pos;
	sf::Vector2f m_speed;
	
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

#endif

