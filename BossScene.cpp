#include "BossScene.h"
#include "Game.h"
#include "Win.h"

#include <SFML/Window/Keyboard.hpp>

#include <iostream>


BossScene::BossScene(std::string fname, std::string jumpName, std::string leftName, std::string rightName, std::string attackName, std::string boosterName, float e1, float e2)
	: Match(fname, jumpName, leftName, rightName, attackName, boosterName, e1, e2) {
	
	platformsMobile.emplace_back(sf::Vector2f(75.f, 300.f), 0.f, "./media/images/match1/plataformaSpace.png");
	platformsMobile.emplace_back(sf::Vector2f(280.f, 100.f), 0.f, "./media/images/match1/BossMatch/plataformBoss.png");
	platformsMobile.emplace_back(sf::Vector2f(500.f, 300.f), 0.f, "./media/images/match1/plataformaSpace.png");
	
	bossTextureUp.loadFromFile("./media/images/match1/BossMatch/bossWatching.png");
	bossTextureDown.loadFromFile("./media/images/match1/BossMatch/bossNotWatching.png");
	bossSprite.setTexture(bossTextureDown);
	bossSprite.setPosition(360.f, 30.f);
	bossSprite.setScale(2, 2);
	
	textureMatch.loadFromFile("./media/images/match1/BossMatch/backgroundBoss.jpg");
	spriteMatch.setTexture(textureMatch);
	
	lifesText.setFillColor(sf::Color::Cyan);
	pause=false; killPlayer=false; danger=false; bossLife=3;
	itemGenerationClock.restart(); killerBoss.restart(); AttackBoss.restart();
	killRectangle.setPosition({0.0, 0.0});
	killRectangle.setSize({800.0, 600.0});
	killRectangle.setFillColor({100, 0, 0, 110});
	lifesBossText.setFont(font);
	lifesBossText.setCharacterSize(24);
	lifesBossText.setFillColor(sf::Color::Red);
	lifesBossText.setPosition(10.f, 60.f);
	AttackText.setFont(font);
	AttackText.setCharacterSize(24);
	AttackText.setFillColor(sf::Color::Red);
	AttackText.setPosition(380.f, 230.f);
}


void BossScene::update(Game &game, float dt) {
	Match::update(game, dt);
	pointCount = 500;
	BossCollide();
	
	if (!pause){
		m_player.update(m_floor.getGlobalBounds(), dt, cooldown);
		
		generateRandomEnemy();
		enemyMecanic(dt);
		
		bossMecanic();
		BossCollide();
		
		generateRandomItems();
		despawnItems();
		moveItems(dt);
	}
	if (pause) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !upPressed) {
			m_selectedOption = (m_selectedOption - 1 + m_options.size()) % m_options.size();
			upPressed = true;
			game.playSelectSound();
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			upPressed = false;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !downPressed) {
			m_selectedOption = (m_selectedOption + 1) % m_options.size();
			downPressed = true;
			game.playSelectSound();
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			downPressed = false;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			game.playEnterSound();
			
			// Manejo de la opcion seleccionada:
			if (m_selectedOption == 0) {
				pause = false;
			}
			else if (m_selectedOption == 1) {
				game.stopBossMusic();
				game.playMatch1Music();
				state = true;
				Scene* newScene = new Match1("./media/images/match1/player.png", "./media/images/match1/p1_jump.png", "./media/images/match1/p1_left.png",
												"./media/images/match1/p1_right.png","./media/images/match1/p1_dead.png","./media/images/match1/p1_booster.png",1.0f,1.0f);
				game.setScene(newScene);
			} else if (m_selectedOption == 2) {
				game.stopBossMusic();
				game.playMenuMusic();
				state = true;
				Scene* newScene = new Menu();
				game.setScene(newScene);
			}
			
		}
	}
	
	for (auto& coin : coins) {
		if (!coin.isTaken() && m_player.getGlobalBounds().intersects(coin.getGlobalBounds())) {
			bossLife--;
			BlueWindow.restart();
		}
	}
	
	if(bossLife == 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
		Scene* win = new Win();
		game.setScene(win);
		
		game.stopBossMusic();
		game.playCreditosMusic();
	}
	
}

void BossScene::draw(sf::RenderWindow &window) {
	
	Match::draw(window);
	
	pointText.setString("Points " + std::to_string(pointCount));
	window.draw(bossSprite);
	
	if(sf::seconds(13.0f) >= AttackBoss.getElapsedTime() && AttackBoss.getElapsedTime() >= sf::seconds(12.0f)){
		AttackText.setString("3"); window.draw(AttackText);
		AttackText.setPosition(380.f, 230.f);
	}
	if(sf::seconds(14.0f) >= AttackBoss.getElapsedTime() && AttackBoss.getElapsedTime() >= sf::seconds(13.0f)){
		AttackText.setString("2"); window.draw(AttackText);
	}
	if(sf::seconds(15.0f) >= AttackBoss.getElapsedTime() && AttackBoss.getElapsedTime() >= sf::seconds(14.0f)){
		AttackText.setString("1"); window.draw(AttackText);
	}
	if(sf::seconds(18.0f) >= AttackBoss.getElapsedTime() && AttackBoss.getElapsedTime() >= sf::seconds(15.0f)){
		AttackText.setString("QUIETO"); window.draw(AttackText);
		AttackText.setPosition(340.f, 230.f);
	}
	
	if (danger){
		killRectangle.setFillColor({100, 0, 0, 110});
		window.draw(killRectangle);
	}
	if (BlueWindow.getElapsedTime() <= sf::seconds(0.9f) && bossLife < 3){
		killRectangle.setFillColor({0, 0, 100, 150});
		window.draw(killRectangle);
	}
	lifesBossText.setString("Lifes Boss " + std::to_string(bossLife));
	window.draw(lifesBossText);
	
}

void BossScene::generateRandomItems(){	

	// Genera �tems cada cierto intervalo de tiempo
	if (itemGenerationClock.getElapsedTime() >= sf::seconds(20.0f)) {
		sf::Vector2f positionInmortal(rand() %700, rand() % 250 + 250.f);  // Ajusta el rango vertical
		float inmortalSpeed = 0.f;  // Velocidad del booster (aj�stala seg�n sea necesario)
		inmortals.emplace_back(positionInmortal, inmortalSpeed,"./media/images/match1/InmortalBoost.png","./media/images/match1/InmortalBoost.png");
		
		sf::Vector2f positionLife(rand() % 700 + 50.f, 450.f);  // Ajusta el rango vertical
		float lifeSpeed = 0.f;  // Velocidad del booster (aj�stala seg�n sea necesario)
		lifesBoost.emplace_back(positionLife, lifeSpeed,"./media/images/match1/SaludBooster.png");
		
		itemGenerationClock.restart();
	}
	if (killerBoss.getElapsedTime() >= sf::seconds(30.0f)) {
		coins.emplace_back(sf::Vector2f(380.f,430.f),0.f,"./media/images/match1/bomb.png");
		killerBoss.restart();
	}
	
}


void BossScene::generateRandomEnemy() {
	
	if (rand() % 700 == 1) {
		enemyMatch.push_back(new Enemy1("./media/images/match1/Enemy1_left.png", "./media/images/match1/Enemy1_right.png",sf::Vector2f(800.f,465.f)));
	} 
	
	if (rand() % 600 == 1) {
		enemyMatch.push_back(new Enemy2("./media/images/match1/Enemy2_left.png", "./media/images/match1/Enemy2_right.png", "./media/images/match1/BulletLeft.png", "./media/images/match1/BulletRight.png",sf::Vector2f(800.f,425.f)));
	}
	
	if (rand() % 600 == 1) {
		float positionAux = rand() % 250 + 50.f;
		enemyMatch.push_back(new Enemy3("./media/images/match1/Enemy3.png", positionAux));
	}
	
}

void BossScene::BossCollide(){
	if(!m_player.getInmortal()){
		if(bossSprite.getGlobalBounds().intersects(m_player.getGlobalBounds()) && cooldown == false){
			m_player.loseLife();
			cooldown = true;
			timer.restart();
		}
		if(danger && cooldown == false){
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
				m_player.loseLife();
				cooldown = true;
				timer.restart();
			}
		}
	}
	if(m_player.getInmortal() && bossSprite.getGlobalBounds().intersects(m_player.getGlobalBounds())){
		timer.restart();
	}
	if(timer.getElapsedTime() >= sf::seconds(0.6) && cooldown == true) cooldown = false;
}

void BossScene::bossMecanic(){
	if(AttackBoss.getElapsedTime() >= sf::seconds(15.0f)) danger = true;
	if(AttackBoss.getElapsedTime() >= sf::seconds(18.0f)){
		AttackBoss.restart();
		danger = false;
	}
	if (danger){
		bossSprite.setPosition(360.f, 30.f);
		bossSprite.setTexture(bossTextureUp);
	} else {
		bossSprite.setPosition(330.f, 30.f);
		bossSprite.setTexture(bossTextureDown);
	}
}

BossScene::~BossScene() {
	for (auto& enemy : enemyMatch) {
		delete enemy;
	}
}
