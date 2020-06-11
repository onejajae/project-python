#ifndef SNAKE_GAME
#define SNAKE_GAME

#include <ncurses.h>
#include "snake.h"

class Game
{
  private:
    WINDOW* mainBoard;
    WINDOW* stageBoard;
    WINDOW* scoreBoard;
    WINDOW* missionBoard;
    WINDOW* debugBoard;
    WINDOW* fpsBoard;
    snakeClass snake;
    bool debug;

  public:
    Game(bool debug=false);
    ~Game();

    bool start(); // main game loop
    void render(); //draw game screen
    void drawPoint(int, int, int); // x, y are indexes of snake array
    void debug_snake();

    void updateBoard();

    const char WALL_CHAR = (char)219;
};

#endif