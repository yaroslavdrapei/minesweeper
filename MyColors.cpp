#include "MyColors.h"

sf::Color MyColors::get(MyColor color) {
    switch (color) {
        case MyColor::ClosedCellEven: return sf::Color(29, 143, 23);
        case MyColor::ClosedCellOdd: return sf::Color(159, 184, 70);
        case MyColor::ExposedCellEven: return sf::Color(229, 194, 159);
        case MyColor::ExposedCellOdd: return sf::Color(215, 184, 153);
        case MyColor::Orange: return sf::Color(232, 137, 49);
        default: return sf::Color::White;
    }
}
