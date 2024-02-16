#ifndef GAME_H
#define GAME_H

#include "Scene.h"
#include "Menu.h"
#include "MenuSelect.h"
#include "Match1.h"
#include "Match2.h"
#include <SFML/Graphics.hpp>

class Game {
public:
	Game();
	void run();
	void processEvents();
	void update(float dt);
	void render();
	sf::RenderWindow& getWindow();
	void setScene(Scene* scene);
	
private:
	
	sf::RenderWindow window;
	Scene* currentScene;
	sf::Clock clock;
	sf::Time dt;

};

#endif // GAME_H
