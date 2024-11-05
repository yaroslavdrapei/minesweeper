#include "Renderer.h"
#include "Field.h"

int main() {
    Renderer renderer = Renderer(GRID_WIDTH*CELL_SIZE, GRID_HEIGHT*CELL_SIZE, 30);
    Field field = Field(MINES_COUNT);
    renderer.run(&field);
}
