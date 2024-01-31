#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics/RenderWindow.hpp>

class Game;


class Scene { 
public:
	Scene();
	virtual void Update(Game &game) = 0;
	virtual void Draw(sf::RenderWindow &window) = 0;
	~Scene() { }
private:
};

#endif
