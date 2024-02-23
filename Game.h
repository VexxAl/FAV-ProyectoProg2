#ifndef GAME_H
#define GAME_H

#include "Scene.h"
#include "Menu.h"
#include "MenuSelect.h"
#include "Match1.h"
#include "Match2.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>


class Game {
public:
	Game();
	void run();
	void processEvents();
	void update(float dt);
	void render();
	sf::RenderWindow& getWindow();
	void setScene(Scene* scene);
	
	void playMenuMusic() { menu_music.play(); }
	void stopMenuMusic() { menu_music.stop(); }

	void playMatch1Music() { match1_music.play(); }
	void stopMatch1Music() { match1_music.stop(); }

	void playMatch2Music() { match2_music.play(); }
	void stopMatch2Music() { match2_music.stop(); }		

	void playCoinSound() { coin_sound.play(); }
	void playSelectSound() { sel_sound.play(); }
	void playEnterSound() { enter_sound.play(); }

private:
	sf::RenderWindow window;
	Scene* currentScene;
	sf::Clock clock;
	sf::Time dt;

	sf::Music menu_music;
	sf::Music match1_music;
	sf::Music match2_music;

	sf::SoundBuffer sel_buffer;
	sf::Sound sel_sound;

	sf::SoundBuffer enter_buffer;
	sf::Sound enter_sound;

	sf::SoundBuffer coin_buffer;
	sf::Sound coin_sound;
};

#endif // GAME_H


