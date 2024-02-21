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
	void isPaused();
	void isnotPaused();
	void setPaused(bool value) { pause = value; }

private:
	Match1* SceneKepper;
	sf::RenderWindow window;
	Scene* currentScene;
	sf::Clock clock;
	sf::Time dt;
	bool pause = false;

};

#endif // GAME_H


