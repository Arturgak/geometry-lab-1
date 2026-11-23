#include "flood_fill.h"

static int fillRecursive(struct Grid *grid, int x, int y, int connectivity)
{
    int pixelCount;

    if (x < 0 || x >= MAX_WIDTH || y < 0 || y >= MAX_HEIGHT)
    {
        return 0;
    }

    if (grid->cells[y][x] != EMPTY_PIXEL)
    {
        return 0;
    }

// Помечаем клетку сразу, чтобы рекурсивные вызовы не вернулись к ней повторно. 
    grid->cells[y][x] = FILLED_PIXEL;
    pixelCount = 1;

    pixelCount += fillRecursive(grid, x - 1, y, connectivity);
    pixelCount += fillRecursive(grid, x + 1, y, connectivity);
    pixelCount += fillRecursive(grid, x, y - 1, connectivity);
    pixelCount += fillRecursive(grid, x, y + 1, connectivity);

    if (connectivity == 8)
    {
        pixelCount += fillRecursive(grid, x - 1, y - 1, connectivity);
        pixelCount += fillRecursive(grid, x + 1, y - 1, connectivity);
        pixelCount += fillRecursive(grid, x - 1, y + 1, connectivity);
        pixelCount += fillRecursive(grid, x + 1, y + 1, connectivity);
    }

    return pixelCount;
}

int fillAreaFloodFill(struct Grid *grid, struct Point seed, int connectivity)
{
    if (connectivity != 4 && connectivity != 8)
    {
        return 0;
    }

    if (!isPointInsideGrid(seed))
    {
        return 0;
    }

    if (grid->cells[seed.y][seed.x] != EMPTY_PIXEL)
    {
        return 0;
    }

    return fillRecursive(grid, seed.x, seed.y, connectivity);
}
