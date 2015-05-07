CC = gcc
SOURCES = src/perihelion.c src/camera.c
FLAGS = -framework GLUT -framework OpenGL -framework Cocoa -Wall
OUT = perihelion

all:
	$(CC) $(FLAGS) $(SOURCES) -o $(OUT)
