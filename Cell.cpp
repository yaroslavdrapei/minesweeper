#include "Cell.h"

Cell::Cell(int x, int y) : x(x), y(y) {}

int Cell::getX() {
    return x;
}

int Cell::getY() {
    return y;
}

bool Cell::getIsClicked() {
    return isClicked;
}

void Cell::setX(int newX) {
    if (newX < 0 || newX > GRID_WIDTH) {
        x = 0;
        return;
    }

    x = newX;
}

void Cell::setY(int newY) {
    if (newY < 0 || newY > GRID_HEIGHT) {
        y = 0;
        return;
    }

    y = newY;
}

void Cell::setIsClicked(bool newIsClicked) {
    isClicked = newIsClicked;
}

bool Cell::operator==(Cell other) {
    if (x == other.getX() && y == other.getY()) {
        return true;
    }

    return false;
}

bool Cell::operator!=(Cell other) {
    return !(*this == other);
}
