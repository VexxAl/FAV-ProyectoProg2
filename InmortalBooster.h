#ifndef INMORTALBOOSTER_H
#define INMORTALBOOSTER_H
#include "Object.h"
#include "Player.h"
#include <SFML/Graphics/RenderWindow.hpp>

class InmortalBooster : public Object {
public:
	InmortalBooster(sf::Vector2f position, float speed, std::string fname, std::string imagen);
	bool isTakenB() const {return taken;}
	void setTakenB(bool taken);
	void update (float dt);
	sf::Sprite getSprite(){return topRightSprite;}
	
private:
	bool taken;
	float speed;
	sf::Texture topRightTexture;
	sf::Sprite topRightSprite;
	sf::Vector2f posSprite;
};

#endif


