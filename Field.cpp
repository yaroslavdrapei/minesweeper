#include "Field.h"

Field::Field(int minesCount) : minesCount(minesCount) {
    for (int row = 0; row < GRID_HEIGHT; row++) {
        for (int col = 0; col < GRID_WIDTH; col++) {
            grid[row][col] = make_shared<Cell>(col, row);
        }
    }
}

void Field::init(Cell startingCell) {
    this->generateMines(startingCell);
    this->generateMap();
}

void Field::generateMines(Cell startingCell) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> randomx(0, GRID_WIDTH-1);
    uniform_int_distribution<> randomy(0, GRID_HEIGHT-1);

    vector<shared_ptr<Cell>> excludedCells = this->getNeighbors(startingCell);
    excludedCells.push_back(make_shared<Cell>(startingCell.getX(), startingCell.getY()));

    for (int i = 0; i < minesCount; i++) {
        shared_ptr<Mine> mine = make_shared<Mine>(randomx(gen), randomy(gen));

        bool isMineValid = all_of(excludedCells.begin(), excludedCells.end(), [&mine](auto m) { return *m != *mine;});

        if (isMineValid) {
            grid[mine->getY()][mine->getX()] = mine;
        }
        else {
            i--;
        }
    }
}

void Field::generateMap() {
    for (int row = 0; row < GRID_HEIGHT; row++) {
        for (int col = 0; col < GRID_WIDTH; col++) {
            shared_ptr<Cell> cell = grid[row][col];
            Mine* retrievedMine = dynamic_cast<Mine*>(cell.get());

            if (retrievedMine) continue;

            int minesAround = 0;

            vector<shared_ptr<Cell>> neighbors = this->getNeighbors(*cell);

            for (auto& neighbor : neighbors) {
                retrievedMine = dynamic_cast<Mine*>(neighbor.get());
                if (retrievedMine) minesAround++;
            }

            grid[row][col] = make_shared<Grass>(cell->getX(), cell->getY(), minesAround);
        }
    }
}

vector<shared_ptr<Cell>> Field::getNeighbors(Cell cell) {
    vector<shared_ptr<Cell>> neighbors;

    const int directions[8][2] = {
            {-1, -1},
            {-1, 0},
            {-1, 1},
            {0, -1},
            {0, 1},
            {1, -1},
            {1, 0},
            {1, 1}
    };

    for (auto& dir : directions) {
        int x = cell.getX() + dir[0];
        int y = cell.getY() + dir[1];

        if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
            if (grid[y][x]) {
                neighbors.push_back(grid[y][x]);
            }
        }
    }

    return neighbors;
}

bool Field::dig(Cell cell) {
    cellsDug++;
    Grass* grass = dynamic_cast<Grass*>(grid[cell.getY()][cell.getX()].get());

    if (!grass) {
        grid[cell.getY()][cell.getX()]->setIsClicked(true);
        return false;
    }

    grass->setIsClicked(true);
    if (grass->getMinesAroundCount() == 0) {
        vector<shared_ptr<Cell>> neighbors = this->getNeighbors(cell);
        for (auto& neighbor : neighbors) {
            if (neighbor->getIsClicked()) continue;
            this->dig(*neighbor);
        }
    }

    return true;
}

void Field::toggleMark(Cell cell) {
    shared_ptr<Cell> actualCell = grid[cell.getY()][cell.getX()];
    actualCell->setIsMarked(!actualCell->getIsMarked());
}

bool Field::mapCleared() {
    return GRID_WIDTH * GRID_HEIGHT - minesCount == cellsDug;
}

void Field::restart() {
    for (int row = 0; row < GRID_HEIGHT; row++) {
        for (int col = 0; col < GRID_WIDTH; col++) {
            grid[row][col] = make_shared<Cell>(col, row);
        }
    }
}
