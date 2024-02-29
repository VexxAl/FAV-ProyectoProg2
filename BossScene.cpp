#include "BossScene.h"
#include <SFML/Window/Keyboard.hpp>

#include <iostream>

BossScene::BossScene(std::string fname, std::string jumpName, std::string leftName, std::string rightName, std::string attackName, std::string boosterName, float e1, float e2)
	: Match(fname, jumpName, leftName, rightName, attackName, boosterName, e1, e2) {
	
	platformsMobile.emplace_back(sf::Vector2f(400.f, 300.f), 0.f, "./media/images/match1/plataformaSpace.png");
	platformsMobile.emplace_back(sf::Vector2f(400.f, 300.f), 0.f, "./media/images/match1/BossMatch/plataformBoss.png");
	platformsMobile.emplace_back(sf::Vector2f(400.f, 300.f), 0.f, "./media/images/match1/plataformaSpace.png");
	
	bossTexture.loadFromFile("./media/images/match1/BossMatch/bossWatching.png");
	bossSprite.setTexture(bossTexture);
	
	lifesText.setFillColor(sf::Color::Cyan);
}


void BossScene::update(Game &game, float dt) {
	
	Match::update(game, dt);
	
	if (!pause){
		m_player.update(m_floor.getGlobalBounds(), dt, cooldown);
		
		generateRandomEnemy();
		enemyMecanic(dt);
		
		generateRandomItems();
		despawnItems();
		moveItems(dt);
	}
	
}

void BossScene::draw(sf::RenderWindow &window) {
	
	Match::draw(window);
	
	pointText.setString("Points " + std::to_string(pointCount));
	
}

void BossScene::generateRandomItems(){
	
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
		lifesBoost.emplace_back(positionLife, lifeSpeed,"./media/images/match1/SaludBooster.png");
	}
}


void BossScene::generateRandomEnemy() {
	if (rand() % 800 == 1) {
		enemyMatch.push_back(new Enemy1("./media/images/match1/Enemy1_left.png", "./media/images/match1/Enemy1_right.png"));
	} 
	
	if (rand() % 400 == 1) {
		enemyMatch.push_back(new Enemy2("./media/images/match1/Enemy2_left.png", "./media/images/match1/Enemy2_right.png", "./media/images/match1/BulletLeft.png", "./media/images/match1/BulletRight.png"));
	}
	
	if (rand() % 800 == 1) {
		float positionAux = rand() % 250 + 50.f;
		enemyMatch.push_back(new Enemy3("./media/images/match1/Enemy3.png", positionAux));
	}
}

BossScene::~BossScene() {
	for (auto& enemy : enemyMatch) {
		delete enemy;
	}
}
