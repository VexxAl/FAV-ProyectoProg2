#include "Game.h"
#include <iostream>
#include "Scene.h"
#include "Menu.h"
#include "MenuSelect.h"
#include "Match1.h"
#include "Match2.h"
#include <SFML/Graphics.hpp>


Game::Game()
	: window(sf::VideoMode(800, 600), "FAV-Space"),
	currentScene(nullptr){
	window.setFramerateLimit(60);
}

void Game::run() {
	Menu* menuScene = new Menu();
	setScene(menuScene);
	
	while (window.isOpen()) {
		dt = clock.restart();
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

void Game::update(float dt) {
	if (currentScene) {
		currentScene->update(*this, dt);
	}
}


void Game::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		
		// Agrega esta lógica para pausar/despausar al presionar una tecla específica
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::P) { // Puedes cambiar la tecla según tu preferencia
				// Toggle entre pausar y despausar (dt = 0 o dt = el valor real)
				dt = (dt == sf::Time::Zero) ? clock.restart() : sf::Time::Zero;
			}
		}
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

