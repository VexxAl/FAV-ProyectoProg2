#include "Game.h"
#include "Scene.h"
#include "Menu.h"

#include <SFML/Graphics.hpp>

Game::Game() : m_window(sf::VideoMode(1080, 720), "The Fav Project"){
	m_window.setFramerateLimit(60);
	m_scene= new Menu();
}

void Game::Run(){
	while(m_window.isOpen()) {
		ProcessEvents();
		Update();
		Draw();
		if(m_next_scene){
			delete m_scene;
			m_scene= m_next_scene;
			m_next_scene = nullptr;
		}
	}
}

void Game::Update(){
	m_scene->Update(*this);
}
	
void Game::Draw(){
	m_scene->Draw(m_window);
}

void Game::ProcessEvents(){
	sf::Event eve;
	while(m_window.pollEvent(eve)) {
		if(eve.type == sf::Event::Closed)
			m_window.close();	
	}
}

void Game::SetScene(Scene *next_scene){
	m_next_scene = next_scene;
}

