#include "MenuSelect.h"

MenuSelect::MenuSelect() : m_selectedOption(0) {
	m_font.loadFromFile("./media/fonts/PixelGamer.otf");
	std::vector<std::string> optionNames = {"Jugar", "Modo FAV"};
	
	for (int i = 0; i < optionNames.size(); i++) {
		sf::Text text;
		text.setFont(m_font);
		text.setString(optionNames[i]);
		text.setPosition(100, i * 100 + 100);
		m_options.push_back(text);
	}
}

void MenuSelect::update(Game &game) {
	// Manejo de eventos de teclado
	sf::Event event;
	while (game.getWindow().pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			game.getWindow().close();
		break;
		case sf::Event::KeyPressed:
			switch (event.key.code) {
			case sf::Keyboard::Up:
				m_selectedOption = (m_selectedOption - 1 + m_options.size()) % m_options.size();
			break;
			case sf::Keyboard::Down:
				m_selectedOption = (m_selectedOption + 1) % m_options.size();
			break;
			case sf::Keyboard::Return:
				// Aquí puedes manejar la opción seleccionada
				break;
		}
			break;
		}
	}
}



void MenuSelect::draw(sf::RenderWindow &window) {
	window.clear();
	for (int i = 0; i < m_options.size(); i++) {
		if (i == m_selectedOption) {
			m_options[i].setFillColor(sf::Color::Red);
		} else {
			m_options[i].setFillColor(sf::Color::White);
		}
		window.draw(m_options[i]);
	}
}
