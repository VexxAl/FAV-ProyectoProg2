#ifndef WIN_H
#define WIN_H
#include "Scene.h"

class Win : public Scene {
public:
	Win();
	void update (Game & game, float dt);
	void draw (sf::RenderWindow & window);
	void handleEvent (const sf::Event & event);
private:
	sf::Text t1,t2,t3;
	sf::Font f1,f2;
	
	sf::Texture winText;
	sf::Sprite winSprite;
};

#endif

