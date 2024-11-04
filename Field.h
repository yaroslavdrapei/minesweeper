#pragma once
#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include "constants.h"
#include "Cell.h"
#include "Mine.h"
#include "Grass.h"
using namespace std;

class Field {
private:
    int cellsDug=0;
    int minesCount;
public:
    shared_ptr<Cell> grid[GRID_HEIGHT][GRID_WIDTH];
    Field(int minesCount);
    void init(Cell startingCell);
    void generateMines(Cell startingCell);
    void generateMap();
    vector<shared_ptr<Cell>> getNeighbors(Cell cell);
    bool dig(Cell cell);
    void toggleMark(Cell cell);
    bool mapCleared();
};
