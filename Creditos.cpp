#include "Creditos.h"

Creditos::Creditos() {
	m_font.loadFromFile("./media/fonts/PixelEmulator.ttf");
	m_t1.setFont(m_font);
	m_t2.setFont(m_font);
	m_t3.setFont(m_font);
	m_t4.setFont(m_font);
	m_t5.setFont(m_font);
	
	
	m_t1.setString("FAV-Space");
	m_t1.setFillColor({255,255,255});
	m_t1.setPosition(170, 30);
	m_t1.setCharacterSize(70);

	
	creditosTexture.loadFromFile("./media/images/creditos.jpg");
	creditosSprite.setTexture(creditosTexture);
	
	fotoTexture.loadFromFile("./media/images/creadores.jpg");
	fotoSprite.setTexture(fotoTexture);
	
	fotoSprite.setPosition(250, 130);
	
	m_t2.setString("F : Federico Mazzieri");
	m_t2.setFillColor({250,250,250});
	m_t2.setPosition(250,390);
	m_t2.setCharacterSize(17);
	
	m_t3.setString("A : Angelina Niedermayer");
	m_t3.setFillColor({250,250,250});
	m_t3.setPosition(250,420);
	m_t3.setCharacterSize(17);
	
	m_t4.setString("V : Valentín Alderete");
	m_t4.setFillColor({250,250,250});
	m_t4.setPosition(250,450);
	m_t4.setCharacterSize(17);
	
	m_t5.setString("Ing. en Inteligencia Artificial   -  Febrero 2024");
	m_t5.setFillColor({250,250,250});
	m_t5.setPosition(45, 550);
	m_t5.setCharacterSize(20);
}

void Creditos::update (Game & game, float dt) {
	unsigned char r = rand();
	unsigned char g = rand();
	unsigned char b = rand();
	m_t1.setFillColor({r, g, b});
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		Scene* newMenu = new MenuSelect();
		game.setScene(newMenu);

		game.playSelectSound();
		game.stopCreditosMusic();
		game.playMenuMusic();

	}
}

void Creditos::draw (sf::RenderWindow & window) {
	window.clear();
	window.draw(creditosSprite);
	window.draw(fotoSprite);
	window.draw(m_t1);
	window.draw(m_t2);
	window.draw(m_t3);
	window.draw(m_t4);
	window.draw(m_t5);
}

void Creditos::handleEvent (const sf::Event & event) {
	
}

