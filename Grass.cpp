#include "Grass.h"

Grass::Grass(int x, int y, int minesAroundCount) : Cell(x, y), minesAroundCount(minesAroundCount) {}

int Grass::getMinesAroundCount() {
    return minesAroundCount;
}

void Grass::setMinesAroundCount(int newMinesAroundCount) {
    if (newMinesAroundCount < 0 || newMinesAroundCount > 8) {
      minesAroundCount = 0;
      return;
    }

    minesAroundCount = newMinesAroundCount;
}
