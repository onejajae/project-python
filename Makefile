CC = g++
CCFLAGS = -g

SnakeGame: bin/main.o 
	$(CC) $(CCFLAGS) -o SnakeGame src/main.cpp src/menu.cpp src/snake.cpp -lncursesw

bin/main.o: src/main.cpp