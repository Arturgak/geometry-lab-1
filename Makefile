app: main.o grid.o bresenham.o dda.o polygon.o flood_fill.o scanline.o
	gcc main.o grid.o bresenham.o dda.o polygon.o flood_fill.o scanline.o -o app -lm

main.o: main.c grid.h bresenham.h dda.h polygon.h flood_fill.h scanline.h
	gcc -c main.c

grid.o: grid.c grid.h
	gcc -c grid.c

bresenham.o: bresenham.c bresenham.h grid.h
	gcc -c bresenham.c

dda.o: dda.c dda.h grid.h
	gcc -c dda.c

polygon.o: polygon.c polygon.h bresenham.h grid.h
	gcc -c polygon.c

flood_fill.o: flood_fill.c flood_fill.h grid.h
	gcc -c flood_fill.c

scanline.o: scanline.c scanline.h grid.h
	gcc -c scanline.c

run: app
	./app

clean:
	rm -f *.o app result.pgm
