#include <stdio.h>
#include "grid.h"

void initializeGrid(struct Grid *grid)
{
    int row;
    int column;

    for (row = 0; row < MAX_HEIGHT; row++)
    {
        for (column = 0; column < MAX_WIDTH; column++)
        {
            grid->cells[row][column] = EMPTY_PIXEL;
        }
    }
}

void printGrid(const struct Grid *grid)
{
    int row;
    int column;

    printf("\n");

    for (row = MAX_HEIGHT - 1; row >= 0; row--) // Печать сетки с верхнего ряда вниз(y-координата увеличивается снизу вверх)
    {
        printf("%2d | ", row);

        for (column = 0; column < MAX_WIDTH; column++)
        {
            printf("%c ", grid->cells[row][column]);
        }

        printf("\n");
    }

    printf("   +");

    for (column = 0; column < MAX_WIDTH; column++)
    {
        printf("--");
    }
    printf("\n     ");
    for (column = 0; column < MAX_WIDTH; column++)
    {
        printf("%d ", column % 10);
    }

    printf("\n\n");
}

//255 - белый, 0 - черный, 150 - серый
void saveToPGM(const struct Grid *grid, const char *filename)
{
    FILE *file;
    int row;
    int column;
    int pixelValue;

    file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("Не удалось создать файл.\n");
        return;
    }
    //fprintf выводит в файл, а не на экран
    fprintf(file, "P2\n");
    fprintf(file, "%d %d\n", MAX_WIDTH, MAX_HEIGHT);
    fprintf(file, "255\n");

    for (row = MAX_HEIGHT - 1; row >= 0; row--)
    {
        for (column = 0; column < MAX_WIDTH; column++)
        {
            if (grid->cells[row][column] == EMPTY_PIXEL)
            {
                pixelValue = 255;
            }
            else if (grid->cells[row][column] == BORDER_PIXEL)
            {
                pixelValue = 0;
            }
            else
            {
                pixelValue = 150;
            }

            fprintf(file, "%d ", pixelValue);
        }

        fprintf(file, "\n");
    }

    fclose(file);
    printf("Изображение сохранено в файл %s.\n", filename);
}

int isPointInsideGrid(struct Point point)
{
    return point.x >= 0 && point.x < MAX_WIDTH && point.y >= 0 && point.y < MAX_HEIGHT;
}
