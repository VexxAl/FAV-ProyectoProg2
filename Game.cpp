#include "Game.h"
#include <iostream>
#include "Match1.h"
#include "Match2.h"
#include "Menu.h"

Game::Game()
	: window(sf::VideoMode(800, 600), "Improved Ball Game"),
	currentScene(nullptr){
	window.setFramerateLimit(60);
}

void Game::run() {
	Menu* menuScene = new Menu();
	setScene(menuScene);
	
	sf::Clock clock;
	
	while (window.isOpen()) {
		sf::Time dt = clock.restart();
		processEvents();
		update(dt.asSeconds());
		render();
	}
	
	// Libera la memoria al finalizar el juego
	delete currentScene;
}

void Game::setScene(Scene* scene) {
	if (currentScene) {
		// Limpia recursos o realiza acciones de limpieza necesarias para la escena actual
		delete currentScene;
	}
	currentScene = scene;
}

void Game::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Game::update(float dt) {
	if (currentScene) {
		currentScene->update(*this);
	}
}

void Game::render() {
	window.clear();
	
	if (currentScene) {
		currentScene->draw(window);
	}
	
	window.display();
}

sf::RenderWindow& Game::getWindow() {
	return window;
}

