#ifndef GRID_H
#define GRID_H

#define MAX_WIDTH 40
#define MAX_HEIGHT 20
#define MAX_PIXELS (MAX_WIDTH * MAX_HEIGHT)
#define MAX_VERTICES 8 //максималное количество вершин многоугольника

#define EMPTY_PIXEL '.'
#define BORDER_PIXEL '#'
#define FILLED_PIXEL '*'

struct Point
{
    int x;
    int y;
};

struct Grid
{
    char cells[MAX_HEIGHT][MAX_WIDTH];
};

void initializeGrid(struct Grid *grid);
void printGrid(const struct Grid *grid);
void saveToPGM(const struct Grid *grid, const char *filename);
int isPointInsideGrid(struct Point point);

#endif
