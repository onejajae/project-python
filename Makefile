CC = g++
CCFLAGS = -g

SnakeGame: main.o 
	$(CC) $(CCFLAGS) -o SnakeGame src/main.cpp src/menu.cpp src/snake.cpp src/game.cpp -lncursesw

main.o: src/main.cpp

