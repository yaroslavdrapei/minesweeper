#pragma once
#include <SFML/Graphics.hpp>

enum class MyColor {
    ClosedCellEven,
    ClosedCellOdd,
    ExposedCellEven,
    ExposedCellOdd,
    Orange
};

class MyColors {
public:
    static sf::Color get(MyColor color);
};
