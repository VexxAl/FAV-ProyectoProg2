#ifndef GAME_H
#define GAME_H

#include "Scene.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Game{
public:
	Game();
	void Run();
	void ProcessEvents();
	void Update();
	void Draw();
	void SetScene(Scene *next_scene);
private:
	sf::RenderWindow m_window;
	Scene *m_scene;
	Scene *m_next_scene = nullptr;
};

#endif
