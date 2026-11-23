#include "bresenham.h"

int drawLineBresenham(struct Grid *grid, struct Point start, struct Point end)
{
    int deltaX;
    int deltaY;
    int stepX;
    int stepY;
    int error;
    int doubledError;
    int pixelCount;

    deltaX = start.x < end.x ? end.x - start.x : start.x - end.x;
    deltaY = start.y < end.y ? end.y - start.y : start.y - end.y;

    stepX = start.x < end.x ? 1 : -1;
    stepY = start.y < end.y ? 1 : -1;

    error = deltaX - deltaY;
    pixelCount = 0;

    while (1)
    {
        if (isPointInsideGrid(start))
        {
            grid->cells[start.y][start.x] = BORDER_PIXEL;
            pixelCount++;
        }

        if (start.x == end.x && start.y == end.y)
        {
            break;
        }

        doubledError = 2 * error;

        if (doubledError > -deltaY)
        {
            error -= deltaY;
            start.x += stepX;
        }

        if (doubledError < deltaX)
        {
            error += deltaX;
            start.y += stepY;
        }
    }

    return pixelCount;
}
