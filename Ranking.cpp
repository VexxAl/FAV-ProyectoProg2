#include "Game.h"
#include "Ranking.h"
#include "GameOver.h"


Ranking::Ranking() {
    rankingTexture.loadFromFile("./media/images/backgroundCreditos.jpg");
    rankingSprite.setTexture(rankingTexture);

    r_f1.loadFromFile("./media/fonts/PixelGamer.otf");
    r_f2.loadFromFile("./media/fonts/PixelEmulator.ttf");
    
    r_t1.setFont(r_f1);
    r_t1.setString("FAV Rankig");
    r_t1.setPosition(145, 50);
    r_t1.setColor({255, 255, 255});
    r_t1.setCharacterSize(100);

    r_t2.setFont(r_f2);
    r_t2.setString("Puntaje:");
    r_t2.setPosition(50, 200);
    r_t2.setColor({255, 255, 255});
    r_t2.setCharacterSize(30);
    
    r_t3.setFont(r_f2);
    r_t3.setString("Nombre del jugador:");
    r_t3.setPosition(350, 200);
    r_t3.setColor({255, 255, 255});
    r_t3.setCharacterSize(30);

    r_t4.setFont(r_f2);
    r_t4.setString("<Presiona 'F1' para volver al menu>");
    r_t4.setPosition(150, 505);
    r_t4.setColor({150, 150, 150});
    r_t4.setCharacterSize(17);

    datos.setFont(r_f2);
    datos.setColor({255, 255, 255});
    datos.setCharacterSize(30);    
}

void Ranking::update(Game &game, float dt) {
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1)){
        game.playEnterSound();
		Scene* newMenu = new Menu();
		game.setScene(newMenu);
    }    
}

void Ranking::draw(sf::RenderWindow &window) {
    window.clear();
    window.draw(rankingSprite);
    window.draw(r_t1);
    window.draw(r_t2);
    window.draw(r_t3);
    window.draw(r_t4);
    drawRanking(window, getRanking());
}

