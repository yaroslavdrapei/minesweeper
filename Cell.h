#pragma once
#include "constants.h"

class Cell {
    int x;
    int y;
    int isClicked=false;
public:
    Cell(int x, int y);
    virtual ~Cell() {}
    int getX();
    int getY();
    void setX(int newX);
    void setY(int newY);

    bool operator==(Cell other);
    bool operator!=(Cell other);
};
