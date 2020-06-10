#include <ctime>
#include <ncurses.h>

#include "game.h"

Game::Game(bool debug) : debug(debug)
{
  curs_set(0);
  noecho();
  cbreak();
  
  nodelay(stdscr,true);
  keypad(stdscr,true);

  mainBoard = newwin(32, 62, 1, 1);
  stageBoard = newwin(4, 30, 2, 65);
  scoreBoard = newwin(7, 30, 7, 65);
  missionBoard = newwin(7, 30, 16, 65);
  
  //box(mainBoard, 0, 0);
  box(stageBoard, 0, 0);
  box(scoreBoard, 0, 0);
  box(missionBoard, 0, 0);

  wrefresh(mainBoard);
  wrefresh(stageBoard);
  wrefresh(scoreBoard);
  wrefresh(missionBoard);

  if (debug) {
    debugBoard = newwin(32, 32, 1, 95);
    box(debugBoard, 0, 0);
    wrefresh(debugBoard);
  }

  updateBoard();

  refresh();

  start_color();
  init_pair(8, COLOR_BLACK, COLOR_BLACK); //blank
  init_pair(WALL, COLOR_WHITE, COLOR_WHITE);
  init_pair(SNAKE_HEAD, COLOR_CYAN, COLOR_CYAN);
  init_pair(SNAKE_BODY, COLOR_BLUE, COLOR_BLUE);
  init_pair(GROWTH_ITEM, COLOR_GREEN, COLOR_GREEN);
  init_pair(POISON_ITEM, COLOR_RED, COLOR_RED);
  init_pair(GATE, COLOR_MAGENTA, COLOR_MAGENTA);

}

Game::~Game()
{
  wclear(mainBoard);
  wclear(stageBoard);
  wclear(scoreBoard);
  wclear(missionBoard);
  
  wrefresh(mainBoard);
  wrefresh(stageBoard);
  wrefresh(scoreBoard);
  wrefresh(missionBoard);

  delwin(mainBoard);
  delwin(stageBoard);
  delwin(scoreBoard);
  delwin(missionBoard);

  nodelay(stdscr, false);

  refresh();
}

bool Game::start()
{
  render();
  while (!snake.collision()) {
    
        nodelay(stdscr, false);
    int input = getch();
    switch (input)
    {
      case KEY_LEFT:
        snake.movesnake(TURN_LEFT);
        break;
      case KEY_UP:
        snake.movesnake(TURN_UP);
        break;
      case KEY_DOWN:
        snake.movesnake(TURN_DOWN);
        break;
      case KEY_RIGHT:
        snake.movesnake(TURN_RIGHT);
        break;
      case KEY_BACKSPACE:
        nodelay(stdscr, false);
        getch();
        nodelay(stdscr, true);
        break;
      default:
        snake.movesnake();
        break;
    }
    render();
    updateBoard();
  }
}

void Game::drawPoint(int y, int x, int TYPE)
{
  wattron(mainBoard, COLOR_PAIR(TYPE));
  mvwaddch(mainBoard, y, x*2, ACS_CKBOARD);
  mvwaddch(mainBoard, y, x*2+1, ACS_CKBOARD);
  wattroff(mainBoard, COLOR_PAIR(TYPE));
}

void Game::render()
{
  if(debug) debug_snake();
  for (int y=0; y<30; y++) {
    for (int x=0; x<30; x++) {
      switch (snake.snakemap[y][x])
      {
        case BLANK:
          drawPoint(y, x, 8);
          break;
        case WALL:
        case IMMNUNE_WALL:
          drawPoint(y, x, WALL);
          break;
        case SNAKE_HEAD:
          drawPoint(y, x, SNAKE_HEAD);
          break;
        case SNAKE_BODY:
          drawPoint(y, x, SNAKE_BODY);
          break;
        case GROWTH_ITEM:
          drawPoint(y, x, GROWTH_ITEM);
          break;
        case POISON_ITEM:
          drawPoint(y, x, POISON_ITEM);
          break;
        case GATE:
          drawPoint(y, x, GATE);
          break;
      }
    }
  }
  wrefresh(mainBoard);
}

void Game::debug_snake()
{
  for (int y=0; y<30; y++) {
    for (int x=0; x<30; x++) {
      switch (snake.snakemap[y][x])
      {
        case BLANK:
          mvwaddch(debugBoard, y+1, x+1, '0');
          break;
        case WALL:
          mvwaddch(debugBoard, y+1, x+1, '1');
          break;
        case IMMNUNE_WALL:
          mvwaddch(debugBoard, y+1, x+1, '2');
          break;
        case SNAKE_HEAD:
          mvwaddch(debugBoard, y+1, x+1, '3');
          break;
        case SNAKE_BODY:
          mvwaddch(debugBoard, y+1, x+1, '4');
          break;
        case GROWTH_ITEM:
          mvwaddch(debugBoard, y+1, x+1, '5');
          break;
        case POISON_ITEM:
          mvwaddch(debugBoard, y+1, x+1, '6');
          break;
        case GATE:
          mvwaddch(debugBoard, y+1, x+1, '7');
          break;
      }
    }
  }
  wrefresh(debugBoard);
}


void Game::updateBoard()
{
  mvwprintw(stageBoard, 1, 4, "STAGE %d", 1);
  mvwprintw(stageBoard, 2, 4, "SCORE: %d", 100);

  mvwprintw(scoreBoard, 1, 1, "Score Board");
  mvwprintw(scoreBoard, 2, 1, "B: %d / %d", 3, 20);
  mvwprintw(scoreBoard, 3, 1, "+: %d", 5);
  mvwprintw(scoreBoard, 4, 1, "-: %d", 5);
  mvwprintw(scoreBoard, 5, 1, "G: %d", 5);

  mvwprintw(missionBoard, 1, 1, "Missions");
  mvwprintw(missionBoard, 2, 1, "B: %d", 3/20);
  mvwprintw(missionBoard, 3, 1, "+: %d", 5);
  mvwprintw(missionBoard, 4, 1, "-: %d", 5);
  mvwprintw(missionBoard, 5, 1, "G: %d", 5);

  wrefresh(stageBoard);
  wrefresh(scoreBoard);
  wrefresh(missionBoard);

  // mvwprintw(stageBoard, 1, 4, "STAGE %d", stage);
  // mvwprintw(stageBoard, 2, 4, "SCORE: %d", score);

  // mvwprintw(scoreBoard, 1, 1, "Score Board");
  // mvwprintw(scoreBoard, 2, 1, "B: %d / %d", currentLength, maxLength);
  // mvwprintw(scoreBoard, 3, 1, "+: %d", grows);
  // mvwprintw(scoreBoard, 4, 1, "-: %d", poisons);
  // mvwprintw(scoreBoard, 5, 1, "G: %d", gates);

  // mvwprintw(missionBoard, 1, 1, "Missions");
  // mvwprintw(missionBoard, 2, 1, "B: %d", currentLength/maxLength);
  // mvwprintw(missionBoard, 3, 1, "+: %d", grows);
  // mvwprintw(missionBoard, 4, 1, "-: %d", poisons);
  // mvwprintw(missionBoard, 5, 1, "G: %d", gates);

  // wrefresh(stageBoard);
  // wrefresh(scoreBoard);
  // wrefresh(missionBoard);
}