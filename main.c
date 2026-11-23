
#include <stdio.h>
#include "grid.h"
#include "bresenham.h"
#include "dda.h"
#include "polygon.h"
#include "flood_fill.h"
#include "scanline.h"

int readPoint(struct Point *point)
{
    printf("Введите координаты x и y: ");
    scanf("%d %d", &point->x, &point->y);

    if (!isPointInsideGrid(*point))
    {
        printf("Ошибка: точка находится за пределами сетки.\n");
        return 0;
    }

    return 1;
}

int readPolygon(struct Point vertices[], int *vertexCount)
{
    int i;

    printf("Введите количество вершин (3-%d): ", MAX_VERTICES);
    scanf("%d", vertexCount);

    if (*vertexCount < 3 || *vertexCount > MAX_VERTICES)
    {
        printf("Неверное количество вершин.\n");
        return 0;
    }

    for (i = 0; i < *vertexCount; i++)
    {
        printf("Вершина %d:\n", i + 1);

        if (!readPoint(&vertices[i]))
        {
            return 0;
        }
    }

    return 1;
}

void drawSingleLine(struct Grid *grid)
{
    struct Point start, end;
    int pixelCount;

    printf("Начальная точка:\n");
    if (!readPoint(&start)) return;

    printf("Конечная точка:\n");
    if (!readPoint(&end)) return;

    initializeGrid(grid);
    pixelCount = drawLineBresenham(grid, start, end);

    printGrid(grid);
    printf("Количество пикселей: %d\n", pixelCount);
}

void compareLineAlgorithms(void)
{
    struct Grid grid1, grid2;
    struct Point start, end;

    printf("Начальная точка:\n");
    if (!readPoint(&start)) return;

    printf("Конечная точка:\n");
    if (!readPoint(&end)) return;

    initializeGrid(&grid1);
    initializeGrid(&grid2);

    drawLineBresenham(&grid1, start, end);
    drawLineDDA(&grid2, start, end);

    printf("\nАлгоритм Брезенхэма:\n");
    printGrid(&grid1);

    printf("\nАлгоритм DDA:\n");
    printGrid(&grid2);
}

void buildPolygonWithFloodFill(struct Grid *grid)
{
    struct Point vertices[MAX_VERTICES];
    struct Point seed;
    int vertexCount;
    int connectivity;
    int filledCount;

    if (!readPolygon(vertices, &vertexCount)) return;

    initializeGrid(grid);
    drawPolygon(grid, vertices, vertexCount);

    printf("\nКонтур многоугольника:\n");
    printGrid(grid);

    printf("Введите точку-затравку:\n");
    if (!readPoint(&seed)) return;

    printf("Выберите связность (4 или 8): ");
    scanf("%d", &connectivity);

    filledCount = fillAreaFloodFill(grid, seed, connectivity);

    printf("Закрашено пикселей: %d\n", filledCount);
    printGrid(grid);
}

void buildPolygonWithScanline(struct Grid *grid)
{
    struct Point vertices[MAX_VERTICES];
    int vertexCount;
    int filledCount;

    if (!readPolygon(vertices, &vertexCount)) return;

    initializeGrid(grid);
    drawPolygon(grid, vertices, vertexCount);

    filledCount = fillAreaScanline(grid, vertices, vertexCount);

    printf("Закрашено пикселей: %d\n", filledCount);
    printGrid(grid);
}

int main(void)
{
    struct Grid grid;
    int choice;

    initializeGrid(&grid);

    while (1)
    {
        printf("\nЛАБОРАТОРНАЯ РАБОТА\n");
        printf("1. Алгоритм Брезенхэма\n");
        printf("2. Сравнение Брезенхэма и DDA\n");
        printf("3. Flood Fill\n");
        printf("4. Scanline Fill\n");
        printf("5. Показать сетку\n");
        printf("6. Сохранить сетку в PGM\n");
        printf("0. Выход\n");

        printf("Ваш выбор: ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice)
        {
            case 1:
                drawSingleLine(&grid);
                break;

            case 2:
                compareLineAlgorithms();
                break;

            case 3:
                buildPolygonWithFloodFill(&grid);
                break;

            case 4:
                buildPolygonWithScanline(&grid);
                break;

            case 5:
                printGrid(&grid);
                break;

            case 6:
                saveToPGM(&grid, "result.pgm");
                break;

            case 0:
                return 0;

            default:
                printf("Такого пункта меню нет.\n");
        }
    }

    return 0;
}
