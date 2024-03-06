#include "GameOver.h"
#include "Game.h"
#include "Creditos.h"
#include "Match.h"
#include "Menu.h"

#include <iostream>
#include <typeinfo>


GameOver::GameOver(int score, bool isMatch2) {
    matchScore = score;
    match2 = isMatch2;

    go_f1.loadFromFile("./media/fonts/PixelGamer.otf");
    go_f2.loadFromFile("./media/fonts/PixelEmulator.ttf");
    
    go_t1.setFont(go_f1);
    go_t1.setString("GAME OVER");
    go_t1.setFillColor({255, 0, 0});
    go_t1.setPosition(145, 75);
    go_t1.setCharacterSize(100);
    
    go_t2.setFont(go_f2);
    go_t2.setString("SCORE: " + std::to_string(matchScore));
    go_t2.setFillColor({255, 255, 255});
    go_t2.setPosition(150, 200);
    go_t2.setCharacterSize(50);

    go_t3.setFont(go_f2);    
    go_t3.setString("Playername: ");
    go_t3.setFillColor({255, 255, 255});
    go_t3.setPosition(150,300);
    go_t3.setCharacterSize(30);

    go_t4.setFont(go_f2);
	go_t4.setString("<Presiona 'F1' para volver al menu>");
	go_t4.setFillColor({150,150,150});
	go_t4.setPosition(170, 400);
	go_t4.setCharacterSize(17);

    go_t5.setFont(go_f2);
    go_t5.setString("<Presiona 'F2' para volver a jugar>");
    go_t5.setFillColor({150,150,150});
    go_t5.setPosition(170, 450);
    go_t5.setCharacterSize(17);

    go_t6.setFont(go_f2);
    go_t6.setString("<Presiona 'F3' para ir a los creditos>");
	go_t6.setFillColor({150,150,150});
	go_t6.setPosition(160, 500);
	go_t6.setCharacterSize(17);

    playerLetter.setFont(go_f2);
    playerLetter.setFillColor({255, 255, 255});
    playerLetter.setCharacterSize(30);
    
    textureGameOver.loadFromFile("./media/images/backgroundSelect.jpg");
    spriteGameOver.setTexture(textureGameOver);

    file_saved = false;
}	

void GameOver::update(Game &game, float dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1)){
        game.playEnterSound();
        Scene* newScene = new MenuSelect();
        game.setScene(newScene);
        
        game.stopCreditosMusic();
        game.playMenuMusic();
    } 
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
        if (!match2) {
            game.playEnterSound();
            Scene* newScene = new Match1("./media/images/match1/player.png", "./media/images/match1/p1_jump.png", "./media/images/match1/p1_left.png",
				"./media/images/match1/p1_right.png","./media/images/match1/p1_dead.png","./media/images/match1/p1_booster.png",1.0f,1.0f);
            game.setScene(newScene);
            game.playMatch1Music();
        }
        else if (match2) {
            game.playEnterSound();
            Scene* newScene = new Match2("./media/images/match2/p2.png", "./media/images/match2/p2_jumpPrueba.png", "./media/images/match2/p2_left.png",
				"./media/images/match2/p2_right.png","./media/images/match2/p2_dead.png","./media/images/match2/p2_booster.png",2.6f,2.6f);
            game.setScene(newScene);
            game.playMatch2Music();    
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3)){
        game.playEnterSound();
        Scene* newScene = new Creditos();
        game.setScene(newScene);
        
        game.stopCreditosMusic();
        game.playCreditosMusic();
    }
}

void GameOver::draw(sf::RenderWindow &window) {
	window.clear();
	window.draw(spriteGameOver);
	window.draw(go_t1);
	window.draw(go_t2);
    if (match2) {
        window.draw(go_t3);
        drawEnteredLetters(window);
        drawSaved(window);  
    }
    window.draw(go_t4);
    window.draw(go_t5);
    window.draw(go_t6);
}

void GameOver::handleEvent(const sf::Event &event) { 
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode >= 'A' && event.text.unicode <= 'z' && enteredLetters.size() < 3) {
            addLetter(static_cast<char>(event.text.unicode));
        }
    } 
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace) {
        deleteLetter();
    }
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
        if (!file_saved &&  0 < enteredLetters.size() < 3 && match2) {
            chargeFiles();
        }
    }
}
