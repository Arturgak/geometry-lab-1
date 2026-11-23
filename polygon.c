#include "polygon.h"
#include "bresenham.h"

void drawPolygon(struct Grid *grid, const struct Point vertices[], int vertexCount)
{
    int vertex;
    int nextVertex;

    for (vertex = 0; vertex < vertexCount; vertex++)
    {
        nextVertex = (vertex + 1) % vertexCount;
        drawLineBresenham(grid, vertices[vertex], vertices[nextVertex]);
    }
}
