#pragma once
#include "Cell.h"

class Grass : public Cell {
private:
    int minesAroundCount;
public:
    Grass(int x, int y, int minesAroundCount);
    int getMinesAroundCount();
    void setMinesAroundCount(int newMinesAroundCount);
};
