#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics/RenderWindow.hpp>
class Game;


class Scene { 
public:
	Scene();
	virtual void update(Game &game, float dt) = 0;
	virtual void draw(sf::RenderWindow &window) = 0;
	virtual bool isMatch1() const = 0;
	~Scene() { }
private:

};

#endif

