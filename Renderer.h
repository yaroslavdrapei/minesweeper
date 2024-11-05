#pragma once
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include "constants.h"
#include "Field.h"

class Renderer {
private:
    sf::RenderWindow window;
    int windowWidth;
    int windowHeight;
    bool hasGameStarted = false;
    bool lost = false;
public:
    Renderer(int windowWidth, int windowHeight, int fps);
    void render(Field* field);
    void processEvents(Field* field);
    void run(Field* field);
    void wantToPlayAgain();
    bool isGameOver(Field* field);
    shared_ptr<sf::Sprite> createSprite(const string& pathToPng);
    shared_ptr<sf::Text> createText(const string& msg, int fontSize, sf::Color color);
    shared_ptr<sf::RectangleShape> createRectangle(int width, int height);
    sf::Color getColor(int minesCount);
};
