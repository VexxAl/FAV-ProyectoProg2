#include "Match1.h"
#include <SFML/Window/Keyboard.hpp>

#include <iostream>

Match1::Match1(std::string fname,std::string jumpName, std::string leftName, std::string rightName, std::string attackName,std::string boosterName, float e1, float e2)
	:  Match(fname,jumpName,leftName,rightName,attackName,boosterName,e1, e2) {

}

void Match1::update(Game &game, float dt) {
	
	Match::update(game, dt);
	
	if (!pause){
		m_player.update(m_floor.getGlobalBounds(), dt, cooldown);
		
		generateRandomEnemy();
		enemy1Mecanic(dt);
		enemy2Mecanic(dt);
		enemy3Mecanic(dt);
		
		generateRandomItems();
		despawnItems();
		moveItems(dt);
	}
	
}

void Match1::draw(sf::RenderWindow &window) {
	
	Match::draw(window);
	
	pointText.setString("Points " + std::to_string(pointCount));
	
	lifesText.setString("Lifes " + std::to_string(m_player.getLifes()));
	
}

void Match1::generateRandomItems(){
	
	if (rand() % 200 == 0) {
		sf::Vector2f platformPosition(800.f, rand() % 200 + 120.f); // Ajusta el rango vertical
		float platformSpeed = static_cast<float>(rand() % 200 + 50); // Ajusta la velocidad segun sea necesario
		platformsMobile.emplace_back(platformPosition, platformSpeed, "./media/images/match1/plataformaSpace.png");
	}
	
	if (rand() % 100 == 1) {
		sf::Vector2f coinPosition(800.f, rand() % 450 + 50.f);  // Ajusta el rango vertical
		float coinSpeed = -100.f;  // Velocidad de la moneda
		coins.emplace_back(coinPosition, coinSpeed,"./media/images/match1/star.png");
	}
	
	if (rand()% 500  == 1) {
		sf::Vector2f positionInmortal(800.f, rand() % 250 + 250.f);  // Ajusta el rango vertical
		float inmortalSpeed = -30.f;  // Velocidad del booster (ajústala según sea necesario)
		inmortals.emplace_back(positionInmortal, inmortalSpeed,"./media/images/match1/InmortalBoost.png","./media/images/match1/InmortalBoost.png");
	}
	
	if (rand()% 300  == 1) {
		sf::Vector2f positionLife(800.f, rand() % 450 + 50.f);  // Ajusta el rango vertical
		float lifeSpeed = -100.f;  // Velocidad del booster (ajústala según sea necesario)
		lifesBoost.emplace_back(positionLife, lifeSpeed,"./media/images/match2/Sprite-Heart.png");
	}
}


void Match1::generateRandomEnemy() {
	// Genera monedas aleatorias en la derecha de la pantalla
	if (rand() % 800 == 1) {
		enemylvl1.emplace_back("./media/images/match1/Enemy1_left.png","./media/images/match1/Enemy1_right.png");
	} 
	
	if (rand() % 400 == 1) {
		enemylvl2.emplace_back("./media/images/match1/Enemy2_left.png","./media/images/match1/Enemy2_right.png","./media/images/match1/BulletLeft.png","./media/images/match1/BulletRight.png");
	}
	
	if (rand() % 800 == 1) {
		float positionAux = rand() % 250 + 50.f;
		enemylvl3.emplace_back("./media/images/match1/Enemy3.png", positionAux);
	}
}



