#include "Game.h"
#include "PauseMenu.h"


PauseMenu::PauseMenu() {
	// Carga de la fuente
	m_font.loadFromFile("./media/fonts/PixelGamer.otf");
	
	// Creacion de las opciones del menu
	std::vector<std::string> optionNames = {"Reanudar", "Salir al menu"};
	for (int i = 0; i < optionNames.size(); i++) {
		sf::Text text;
		text.setFont(m_font);
		text.setString(optionNames[i]);
		text.setPosition(300, i * 100 + 150);
		m_options.push_back(text);
	}
	
	m_selectedOption = 0;
	upPressed = false;
	downPressed = false;
	state = false;
}

void PauseMenu::update(Game& game, float dt) {
	if (game.getWindow().hasFocus()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !upPressed) {
			m_selectedOption = (m_selectedOption - 1 + m_options.size()) % m_options.size();
			upPressed = true;
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			upPressed = false;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !downPressed) {
			m_selectedOption = (m_selectedOption + 1) % m_options.size();
			downPressed = true;
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			downPressed = false;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			// Manejo de la opcion seleccionada:
			if (m_selectedOption == 0) {
				// game.isnotPaused();
			}
			else if (m_selectedOption == 1) {
				state = true;
				Scene* newScene = new Menu();
				game.setScene(newScene);
				
				game.playMenuMusic();
			}
		}
	}
}

void PauseMenu::draw(sf::RenderWindow &window) {
	// Dibujar un fondo (superposicion oscurecida u otro efecto visual)
	sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
	background.setFillColor(sf::Color(0, 0, 0, 10));
	window.draw(background);
	
	// Dibujar las opciones del men�
	for (int i = 0; i < m_options.size(); i++) {
		if (i == m_selectedOption) {
			m_options[i].setFillColor({136, 0, 208});
		} else {
			m_options[i].setFillColor(sf::Color::White);
		}
		window.draw(m_options[i]);
	}
}




