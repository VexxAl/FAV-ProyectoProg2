#ifndef CREDITOS_H
#define CREDITOS_H
#include "Scene.h"
#include "Game.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Creditos : public Scene {
public:
	Creditos();
	void update (Game & game, float dt);
	void draw (sf::RenderWindow & window);
	void handleEvent (const sf::Event & event);
private:
	sf::Texture creditosTexture;
	sf::Sprite creditosSprite;
	sf::Texture fotoTexture;
	sf::Sprite fotoSprite;
	sf::Font m_font;
	sf::Text m_t1, m_t2, m_t3, m_t4, m_t5;
};

#endif

