#pragma once
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "Field.h"
#include "MyColors.h"

class Renderer {
private:
    sf::RenderWindow window;
    int windowWidth;
    int windowHeight;
    sf::Font font;
    sf::Texture flagTexture;
    sf::Texture mineTexture;
    bool hasGameStarted = false;
    bool lost = false;
public:
    Renderer(int windowWidth, int windowHeight, int fps);
    void render(Field* field);
    void processEvents(Field* field);
    void run(Field* field);
    void wantToPlayAgain();
    bool isGameOver(Field* field);
    sf::Color getNumberColor(int minesCount);
};
