
#include <math.h>
#include "scanline.h"

static void sortIntersections(double intersections[], int count)
{
    int current;
    int previous;
    double value;

    for (current = 1; current < count; current++)
    {
        value = intersections[current];
        previous = current - 1;

        while (previous >= 0 && intersections[previous] > value)
        {
            intersections[previous + 1] = intersections[previous];
            previous--;
        }

        intersections[previous + 1] = value;
    }
}

int fillAreaScanline(struct Grid *grid, const struct Point vertices[], int vertexCount)
{
    double intersections[MAX_VERTICES];
    double scanY;
    double intersectionX;
    double firstX;
    double secondX;

    int row;
    int edge; 
    int nextVertex;
    int intersectionCount;
    int pair;
    int startColumn;
    int endColumn;
    int column;
    int pixelCount;
    int minimumY;
    int maximumY;

    pixelCount = 0;

    for (row = 0; row < MAX_HEIGHT; row++)
    {
        scanY = row;
        intersectionCount = 0;

        for (edge = 0; edge < vertexCount; edge++)
        {
            nextVertex = (edge + 1) % vertexCount;
            minimumY = vertices[edge].y < vertices[nextVertex].y ? vertices[edge].y : vertices[nextVertex].y;
            maximumY = vertices[edge].y > vertices[nextVertex].y ? vertices[edge].y : vertices[nextVertex].y;

//Не учитываем горизонтальные рёбра и повторные пересечения в вершинах. 
            if (vertices[edge].y != vertices[nextVertex].y && scanY >= minimumY && scanY < maximumY)
            {
                intersectionX = vertices[edge].x +
                    (scanY - vertices[edge].y) * (vertices[nextVertex].x - vertices[edge].x) /(vertices[nextVertex].y - vertices[edge].y);

                if (intersectionCount < MAX_VERTICES)
                {
                    intersections[intersectionCount] = intersectionX;
                    intersectionCount++;
                }
            }
        }

        sortIntersections(intersections, intersectionCount);

        for (pair = 0; pair + 1 < intersectionCount; pair += 2)
        {
            firstX = intersections[pair];
            secondX = intersections[pair + 1];

            startColumn = (int)ceil(firstX);
            endColumn = (int)floor(secondX);

            if (startColumn < 0)
            {
                startColumn = 0;
            }

            if (endColumn >= MAX_WIDTH)
            {
                endColumn = MAX_WIDTH - 1;
            }

            for (column = startColumn; column <= endColumn; column++)
            {
                if (grid->cells[row][column] == EMPTY_PIXEL)
                {
                    grid->cells[row][column] = FILLED_PIXEL;
                    pixelCount++;
                }
            }
        }
    }

    return pixelCount;
}
