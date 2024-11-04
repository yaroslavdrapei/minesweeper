#pragma once
#include "constants.h"

class Cell {
    int x;
    int y;
    bool isClicked=false;
public:
    Cell(int x, int y);
    virtual ~Cell() {}
    int getX();
    int getY();
    bool getIsClicked();
    void setX(int newX);
    void setY(int newY);
    void setIsClicked(bool isClicked);

    bool operator==(Cell other);
    bool operator!=(Cell other);
};
