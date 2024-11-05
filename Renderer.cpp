#include "Renderer.h"
#include <iostream>

Renderer::Renderer(int windowWidth, int windowHeight, int fps) : windowWidth(windowWidth), windowHeight(windowHeight) {
    window.create(sf::VideoMode(windowWidth, windowHeight),
                  "Minesweeper",
                  sf::Style::Titlebar | sf::Style::Close);

    window.setFramerateLimit(fps);
    
    font.loadFromFile(R"(E:\KSE\year-2\oop\minesweeper\assets\arialbd.ttf)");
    flagTexture.loadFromFile(R"(E:\KSE\year-2\oop\minesweeper\assets\flag.png)");
    mineTexture.loadFromFile(R"(E:\KSE\year-2\oop\minesweeper\assets\mine.png)");
}

void Renderer::render(Field *field) {
    window.clear();

    for (int row = 0; row < GRID_HEIGHT; row++) {
        for (int col = 0; col < GRID_WIDTH; col++) {
            float newX = (float)col*CELL_SIZE;
            float newY = (float)row*CELL_SIZE;

            shared_ptr<Cell> cell = field->grid[row][col];

            sf::RectangleShape rect(sf::Vector2f((float)CELL_SIZE, (float)CELL_SIZE));

            rect.setPosition(newX, newY);

            if (cell->getIsClicked()) {
                Grass* grass = dynamic_cast<Grass*>(cell.get());

                if (!grass) {
                    sf::Color color = (row+col) % 2 == 0 ? MyColors::get(MyColor::ClosedCellEven) : MyColors::get(MyColor::ClosedCellOdd);
                    rect.setFillColor(color);
                    window.draw(rect);

                    sf::Sprite mine;

                    mine.setTexture(mineTexture);
                    mine.setPosition(
                            rect.getPosition().x + 4,
                            rect.getPosition().y + 4
                    );

                    window.draw(mine);
                    continue;
                };

                sf::Color rectColor = (row+col) % 2 == 0 ? MyColors::get(MyColor::ExposedCellEven) : MyColors::get(MyColor::ExposedCellOdd);

                rect.setFillColor(rectColor);
                window.draw(rect);

                string message = grass->getMinesAroundCount() ? to_string(grass->getMinesAroundCount()) : "";

                sf::Text text;
                sf::Color textColor = getNumberColor(grass->getMinesAroundCount());

                if (grass->getMinesAroundCount()) {
                    text.setString(to_string(grass->getMinesAroundCount()));
                }

                text.setFont(font);
                text.setCharacterSize(25);
                text.setFillColor(textColor);
                text.setPosition(
                rect.getPosition().x + 14,
                rect.getPosition().y + 5
                );

                window.draw(text);
            } else {
                sf::Color color = (row+col) % 2 == 0 ? MyColors::get(MyColor::ClosedCellEven) : MyColors::get(MyColor::ClosedCellOdd);
                rect.setFillColor(color);
                window.draw(rect);
            }

            if (cell->getIsMarked()) {
                sf::Sprite flag;

                flag.setTexture(flagTexture);
                flag.setPosition(
                        rect.getPosition().x + 4,
                        rect.getPosition().y + 4
                );

                window.draw(flag);
            }
        }
    }

    if (isGameOver(field)) {
        wantToPlayAgain();
    };

    window.display();
}

void Renderer::processEvents(Field *field) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::F5) {
                    field->restart();
                    hasGameStarted = false;
                    lost = false;
                }
            case sf::Event::MouseButtonPressed:
                if (isGameOver(field)) break;
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;

                int coordX = x / CELL_SIZE;
                int coordY = y / CELL_SIZE;

                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (!hasGameStarted) {
                        field->init(Cell(coordX, coordY));
                        hasGameStarted = true;
                    }

                    bool dugGrass = field->dig(Cell(coordX, coordY));

                    if (!dugGrass) {
                        lost = true;
                    }
                }

                if (event.mouseButton.button == sf::Mouse::Right) {
                    field->toggleMark(Cell(coordX, coordY));
                }
        }
    }
}

void Renderer::run(Field *field) {
    while (window.isOpen()) {
        processEvents(field);
        render(field);
    }
}

void Renderer::wantToPlayAgain() {
    string winOrLoseText = lost ? "lost" : "won";
    string message = "Game over! You " + winOrLoseText + "! Play again? (F5)";

    sf::Text text;

    text.setFont(font);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::White);
    text.setString(message);

    text.setPosition(
        (windowWidth-text.getGlobalBounds().width)/2,
        (windowHeight-text.getGlobalBounds().height)/2
    );

    window.draw(text);
}

bool Renderer::isGameOver(Field* field) {
    if (lost) return true;
    if (field->mapCleared()) return true;
    return false;
}

sf::Color Renderer::getNumberColor(int minesCount) {
    switch (minesCount) {
        case 1: return sf::Color::Blue;
        case 2: return MyColors::get(MyColor::ClosedCellEven);
        case 3: return sf::Color::Red;
        case 4: return sf::Color::Magenta;
        case 5: return sf::Color::Yellow;
        case 6: return sf::Color::Cyan;
        default: return sf::Color::White;
    }
}
