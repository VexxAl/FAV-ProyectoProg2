#include "Win.h"
#include "Game.h"
#include "Creditos.h"

#include <SFML/Window/Keyboard.hpp>

Win::Win() {
	f1.loadFromFile("./media/fonts/PixelGamer.otf");
	f2.loadFromFile("./media/fonts/PixelEmulator.ttf");
	t1.setFont(f1);
	t2.setFont(f2);
	t3.setFont(f2);
	
	t1.setString("GANASTE");
	t1.setFillColor({255, 0, 255});
	t1.setPosition(180, 70);
	t1.setCharacterSize(100);
	
	t2.setString("<Presiona 'F1' para volver al menú>");
	t2.setFillColor({150,150,150});
	t2.setPosition(195, 300);
	t2.setCharacterSize(17);
	
	t3.setString("<Presiona 'F3' para ir a los creditos>");
	t3.setFillColor({150,150,150});
	t3.setPosition(177,  360);
	t3.setCharacterSize(17);
	
	winText.loadFromFile("./media/images/backgroundWin.jpg");
	winSprite.setTexture(winText);
}

void Win::update (Game & game, float dt) {
	unsigned char r = 200 + rand() %( 255 - 200 + 1);
	unsigned char g = 0 + rand() % (100 - 0 + 1);
	unsigned char b = 100 + rand() % (255- 100 + 1);
	t1.setFillColor({r, g, b});
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1)){
		game.playEnterSound();
		Scene* newMenu = new Menu();
		game.setScene(newMenu);
		
		game.stopCreditosMusic();
		game.playMenuMusic();
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3)){
		game.playEnterSound();
		Scene* newCred = new Creditos();
		game.setScene(newCred);
		
		game.stopCreditosMusic();
		game.playCreditosMusic();
	}
}

void Win::draw (sf::RenderWindow & window) {
	window.clear();
	window.draw(winSprite);
	window.draw(t1);
	window.draw(t2);
	window.draw(t3);
	
}

void Win::handleEvent (const sf::Event & event) {
	
}

