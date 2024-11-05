#include "Renderer.h"
#include <iostream>

Renderer::Renderer(int windowWidth, int windowHeight, int fps) : windowWidth(windowWidth), windowHeight(windowHeight) {
    window.create(sf::VideoMode(windowWidth, windowHeight),
                  "Minesweeper",
                  sf::Style::Titlebar | sf::Style::Close);

    window.setFramerateLimit(fps);
}

void Renderer::render(Field *field) {
    sf::Font font;
    font.loadFromFile(R"(E:\KSE\year-2\oop\minesweeper\assets\arialbd.ttf)");
    sf::Color ClosedField1(29, 143, 23);
    sf::Color ClosedField2(159, 184, 70);
    sf::Color ExposedField1(229, 194, 159);
    sf::Color ExposedField2(215, 184, 153);
    sf::Color ColorOrange(232, 137, 49);

    window.clear();

    for (int row = 0; row < GRID_HEIGHT; row++) {
        for (int col = 0; col < GRID_WIDTH; col++) {
            float newX = (float)col*CELL_SIZE;
            float newY = (float)row*CELL_SIZE;

            shared_ptr<Cell> cell = field->grid[row][col];

            shared_ptr<sf::RectangleShape> rect = createRectangle(CELL_SIZE, CELL_SIZE);

            rect->setPosition(newX, newY);

            if (cell->getIsMarked()) {
                shared_ptr<sf::Sprite> flag = createSprite("E:/KSE/year-2/oop/minesweeper/assets/flag.png");

                flag->setPosition(
                rect->getPosition().x + 4,
                rect->getPosition().y + 4
                );

                window.draw(*flag);
            }

            if (cell->getIsClicked()) {
                Grass* grass = dynamic_cast<Grass*>(cell.get());

                if (!grass) {
                    rect->setFillColor((row+col) % 2 == 0 ? ClosedField1 : ClosedField2);
                    window.draw(*rect);

                    shared_ptr<sf::Sprite> mine = createSprite("E:/KSE/year-2/oop/minesweeper/assets/mine.png");

                    mine->setPosition(
                    rect->getPosition().x + 4,
                    rect->getPosition().y + 4
                    );

                    window.draw(*mine);
                    continue;
                };

                rect->setFillColor((row+col) % 2 == 0 ? ExposedField1 : ExposedField2);
                window.draw(*rect);

                string message = grass->getMinesAroundCount() ? to_string(grass->getMinesAroundCount()) : "";
                shared_ptr<sf::Text> text = createText(message, 25, getColor(grass->getMinesAroundCount()));

                text->setPosition(
                rect->getPosition().x + 14,
                rect->getPosition().y + 5
                );

                window.draw(*text);
            } else {
                rect->setFillColor((row+col) % 2 == 0 ? ClosedField1 : ClosedField2);
                window.draw(*rect);
            }
        }
    }

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
                    delete field;
                    field = new Field(MINES_COUNT);
                }
                break;
            case sf::Event::MouseButtonPressed:
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
        if (isGameOver(field)) {
            cout << "Modal appeared!" << endl;
            wantToPlayAgain();
        }
    }
}

void Renderer::wantToPlayAgain() {
    this_thread::sleep_for(chrono::seconds(2));

    string winOrLoseText = lost ? "lost" : "won";
    string message = "Game over! You " + winOrLoseText + "! Play again? (F5)";

    shared_ptr<sf::RectangleShape> block = createRectangle(windowWidth / 5, windowHeight / 10);

    block->setPosition(windowWidth-20-block->getSize().x, windowHeight-20-block->getSize().y);

    window.draw(*block);

    shared_ptr<sf::Text> text = createText(message, 30, sf::Color::White);

    text->setPosition(
        block->getSize().x + 40,
        block->getSize().y + 20
    );

    window.draw(*text);
}

bool Renderer::isGameOver(Field* field) {
    if (lost) return true;
    if (field->mapCleared()) return true;
    return false;
}

shared_ptr<sf::Sprite> Renderer::createSprite(const string &pathToPng) {
    auto spriteImg = std::make_shared<sf::Texture>();
    spriteImg->loadFromFile(pathToPng);

    auto sprite = std::make_shared<sf::Sprite>();
    sprite->setTexture(*spriteImg);

    return sprite;
}

shared_ptr<sf::Text> Renderer::createText(const string &msg, int fontSize, sf::Color color) {
    auto font = std::make_shared<sf::Font>();
    font->loadFromFile("E:/KSE/year-2/oop/minesweeper/assets/arialbd.ttf");
    auto text = std::make_shared<sf::Text>();

    text->setFont(*font);
    text->setString(msg);
    text->setCharacterSize(fontSize);
    text->setFillColor(color);

    return text;
}

shared_ptr<sf::RectangleShape> Renderer::createRectangle(int width, int height) {
    return make_shared<sf::RectangleShape>(sf::Vector2f((float)width, (float)height));
}

sf::Color Renderer::getColor(int minesCount) {
    switch (minesCount) {
        case 1: return sf::Color::Blue;
//        case 2: return ClosedField1;
        case 2: return sf::Color::Green;
        case 3: return sf::Color::Red;
        case 4: return sf::Color::Magenta;
        case 5: return sf::Color::Yellow;
        case 6: return sf::Color::Cyan;
        default: return sf::Color::White;
    }
}
