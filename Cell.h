#pragma once
#include "constants.h"

class Cell {
    int x;
    int y;
    bool isClicked=false;
    bool isMarked=false;
public:
    Cell(int x, int y);
    virtual ~Cell() {}
    int getX();
    int getY();
    bool getIsClicked();
    bool getIsMarked();
    void setX(int newX);
    void setY(int newY);
    void setIsClicked(bool isClicked);
    void setIsMarked(bool newIsMarked);

    bool operator==(Cell other);
    bool operator!=(Cell other);
};
