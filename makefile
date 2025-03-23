all: build run clean

build:
	gcc -I include -L lib -o game src/main.c -mwin32 -lSDL3

run:
	./game

clean:
	del game.exe