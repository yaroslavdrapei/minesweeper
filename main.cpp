//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <thread>
//#include <chrono>
//#include "constants.h"
//#include "Field.h"

//sf::RenderWindow window(sf::VideoMode(CELL_SIZE * GRID_WIDTH, CELL_SIZE * GRID_HEIGHT),
//                        "Minesweeper",
//                        sf::Style::Titlebar | sf::Style::Close);
//sf::Color ClosedField1(29, 143, 23);
//sf::Color ClosedField2(159, 184, 70);
//sf::Color ExposedField1(229, 194, 159);
//sf::Color ExposedField2(215, 184, 153);
//
//sf::Color getColor(int minesCount) {
//    switch (minesCount) {
//        case 1: return sf::Color::Blue;
//        case 2: return ClosedField1;
//        case 3: return sf::Color::Red;
//        case 4: return sf::Color::Magenta;
//        case 5: return sf::Color::Yellow;
//        case 6: return sf::Color::Cyan;
//        default: return sf::Color::White;
//    }
//}
//
//void render(Field* field) {
//    sf::Font font;
//    font.loadFromFile(R"(E:\KSE\year-2\oop\minesweeper\assets\arialbd.ttf)");
//
//    window.clear();
//
//    for (int row = 0; row < GRID_HEIGHT; row++) {
//        for (int col = 0; col < GRID_WIDTH; col++) {
//            shared_ptr<Cell> cell = field->grid[row][col];
//            sf::RectangleShape rect(sf::Vector2f((float)CELL_SIZE, (float)CELL_SIZE));
//
//            rect.setPosition((float)col*CELL_SIZE, (float)row*CELL_SIZE);
//
//            if (!cell->getIsClicked()) {
//                rect.setFillColor((row+col) % 2 == 0 ? ClosedField1 : ClosedField2);
//                window.draw(rect);
//
//                if (cell->getIsMarked()) {
//                    sf::Texture flagPng;
//                    flagPng.loadFromFile(R"(E:\KSE\year-2\oop\minesweeper\assets\flag.png)");
//
//                    sf::Sprite flag;
//                    flag.setTexture(flagPng);
//
//                    flag.setPosition(
//                            rect.getPosition().x + 4,
//                            rect.getPosition().y + 4
//                    );
//
//                    window.draw(flag);
//                }
//            } else {
//                Grass* grass = dynamic_cast<Grass*>(cell.get());
//                if (!grass) {
//                    rect.setFillColor((row+col) % 2 == 0 ? ClosedField1 : ClosedField2);
//                    window.draw(rect);
//
//                    sf::Texture flagPng;
//                    flagPng.loadFromFile(R"(E:\KSE\year-2\oop\minesweeper\assets\mine.png)");
//
//                    sf::Sprite flag;
//                    flag.setTexture(flagPng);
//
//                    flag.setPosition(
//                            rect.getPosition().x + 4,
//                            rect.getPosition().y + 4
//                    );
//
//                    window.draw(flag);
//                    continue;
//                };
//
//                rect.setFillColor((row+col) % 2 == 0 ? ExposedField1 : ExposedField2);
//                window.draw(rect);
//
//                sf::Text text;
//                sf::Color color = getColor(grass->getMinesAroundCount());
//
//                text.setFont(font);
//
//                if (grass->getMinesAroundCount()) {
//                    text.setString(to_string(grass->getMinesAroundCount()));
//                }
//
//                int size = 25;
//
//                text.setCharacterSize(size);
//                text.setFillColor(color);
//
//                text.setPosition(
//                        rect.getPosition().x + 14,
//                        rect.getPosition().y + 5
//                );
//
//                window.draw(text);
//            }
//        }
//    }
//
//    window.display();
//}
//
//int main() {
//    window.setFramerateLimit(10);
//    bool start = false;
//    bool lost = false;
//    Field* field = new Field(MINES_COUNT);
//
//    render(field);
//
//    while (window.isOpen() && !field->mapCleared() && !lost) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            switch (event.type) {
//                case sf::Event::Closed:
//                    window.close();
//                    break;
//                case sf::Event::MouseButtonPressed:
//                    int x = event.mouseButton.x;
//                    int y = event.mouseButton.y;
//
//                    int coordX = x / CELL_SIZE;
//                    int coordY = y / CELL_SIZE;
//
//                    if (event.mouseButton.button == sf::Mouse::Left) {
//                        if (!start) {
//                            field->init(Cell(coordX, coordY));
//                            start = true;
//                        }
//
//                        if (!field->dig(Cell(coordX, coordY))) {
//                            render(field);
//                            lost = true;
//                            break;
//                        }
//                    }
//
//                    if (event.mouseButton.button == sf::Mouse::Right) {
//                        field->toggleMark(Cell(coordX, coordY));
//                    }
//
//                    render(field);
//            }
//        }
//    }
//
//    this_thread::sleep_for(chrono::seconds(2));
//
//    string text = lost ? "lost" : "won";
//
//    cout << "Game over! You " << text << "!" << endl;
//
//    return 0;
//}
#include "Renderer.h"
#include "Field.h"

int main() {
    Renderer renderer = Renderer(GRID_WIDTH*CELL_SIZE, GRID_HEIGHT*CELL_SIZE, 10);
    Field* field = new Field(MINES_COUNT);
    renderer.run(field);
}
