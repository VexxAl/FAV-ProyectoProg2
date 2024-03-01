#include "Game.h"
#include "Menu.h"
#include "Scene.h"
#include "Match1.h"
#include "Match2.h"
#include "MenuSelect.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>


Game::Game() : window(sf::VideoMode(800, 600), "FAV-Space"), currentScene(nullptr) {
	window.setFramerateLimit(60);

	menu_music.openFromFile("./media/sounds/deus_ex.wav");
	menu_music.setLoop(true);

	match1_music.openFromFile("./media/sounds/match1/spacetheme.wav");
	match1_music.setLoop(true);
	
	boss_music.openFromFile("./media/sounds/match1/God_Of_Thunder.wav");
	boss_music.setLoop(true);

	match2_music.openFromFile("./media/sounds/match2/match2.wav");
	match2_music.setLoop(true);
	
	cred_music.openFromFile("./media/sounds/bit_space.wav");
	cred_music.setLoop(true);

	sel_buffer.loadFromFile("./media/sounds/select_sound.wav");
	sel_sound.setBuffer(sel_buffer);

	enter_buffer.loadFromFile("./media/sounds/enter_sound.wav");
	enter_sound.setBuffer(enter_buffer);

	game_over_buffer.loadFromFile("./media/sounds/game_over.wav");
	game_over_sound.setBuffer(game_over_buffer);


	coin_buffer.loadFromFile("./media/sounds/get_coin.wav");
	coin_sound.setBuffer(coin_buffer);
}

void Game::run() {
	this->playMenuMusic();

	Scene* menuScene = new Menu();
	setScene(menuScene);
	
	while (window.isOpen()) {
		dt = clock.restart();
		processEvents();
		update(dt.asSeconds());
		render();
	}
	
	delete currentScene; //Libera la memoria al finalizar el juego
}

void Game::setScene(Scene* scene) {
	if (currentScene) {
		delete currentScene; //Limpia recursos o realiza acciones de limpieza necesarias para la escena actual
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
		if (currentScene) {
			currentScene->handleEvent(event); // Notifica el evento a la Escena actual
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
