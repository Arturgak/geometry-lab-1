#include <stdlib.h>
#include "dda.h"

int drawLineDDA(struct Grid *grid, struct Point start, struct Point end)
{
    int deltaX;
    int deltaY;
    int stepCount;
    int step;
    int pixelX;
    int pixelY;
    int pixelCount;
    double currentX;
    double currentY;
    double incrementX;
    double incrementY;

    deltaX = end.x - start.x;
    deltaY = end.y - start.y;

    stepCount = abs(deltaX) > abs(deltaY) ? abs(deltaX) : abs(deltaY);
    pixelCount = 0;
// Если шагов нет, значит начальная и конечная точки совпадают
    if (stepCount == 0)
    {
        grid->cells[start.y][start.x] = BORDER_PIXEL;
        return 1;
    }

    incrementX = (double)deltaX / stepCount;
    incrementY = (double)deltaY / stepCount;
    currentX = start.x;
    currentY = start.y;

    for (step = 0; step <= stepCount; step++)
    {
        pixelX = (int)(currentX + 0.5);
        pixelY = (int)(currentY + 0.5);

        if (pixelX >= 0 && pixelX < MAX_WIDTH && pixelY >= 0 && pixelY < MAX_HEIGHT)
        {
            grid->cells[pixelY][pixelX] = BORDER_PIXEL;
            pixelCount++;
        }

        currentX += incrementX;
        currentY += incrementY;
    }

    return pixelCount;
}
