#ifndef RANKING_H
#define RANKING_H

#include "Scene.h"
#include "GameOver.h"

#include <vector>
#include <fstream>


class Ranking : public Scene {
public:
    Ranking();
    void update(Game &game, float dt);
    void draw(sf::RenderWindow &window);

private:
    sf::Texture rankingTexture;
    sf::Sprite rankingSprite;

    sf::Font r_f1;
    sf::Font r_f2;

    sf::Text r_t1; // FAV Ranking
    sf::Text r_t2; // Puntaje: {lista de puntos}
    sf::Text r_t3; // Nombre de Jugador: {lista de jugadores}
    sf::Text r_t4; // Volver al menu

    sf::Text datos;
    int x, y;

    std::vector<std::string> getRanking() {
        std::ifstream ranking("ranking.txt");

        std::string puntaje;
        std::vector<std::string> puntajes;
        while(std::getline(ranking, puntaje)) {
            puntajes.push_back(puntaje);
        }

        ranking.close();
        return puntajes;
    }

protected:
    void drawRanking(sf::RenderWindow &window, std::vector<std::string> puntaje) {
        x = 80; 
        y = 235;
        for (size_t i = 0; i < puntaje.size(); i++) {
            datos.setString(puntaje[i].substr(0,3));
            datos.setPosition(x, y);
            window.draw(datos);
            y = y + 35;
        }
        x = 550;
        y = 235;
        for (size_t i = 0; i < puntaje.size(); i++) {
            datos.setString(puntaje[i].substr(4));
            datos.setPosition(x, y);
            window.draw(datos);
            y = y + 35;
        }
    }
};

#endif
