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
  stageBoard = newwin(4, 30, 2, 62);
  scoreBoard = newwin(7, 30, 7, 62);
  missionBoard = newwin(7, 30, 16, 62);
  fpsBoard = newwin(1,30, 0, 62);
  
  //box(mainBoard, 0, 0);
  box(stageBoard, 0, 0);
  box(scoreBoard, 0, 0);
  box(missionBoard, 0, 0);

  wrefresh(mainBoard);
  wrefresh(stageBoard);
  wrefresh(scoreBoard);
  wrefresh(missionBoard);
  wrefresh(fpsBoard);

  if (debug) {
    debugBoard = newwin(32, 32, 1, 93);
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
  int stageNum = 1;
  render();

  clock_t start_time = clock();
  clock_t end_time = clock();
  clock_t wait_time = clock();
  unsigned long long loop_count = 0;
  double FPS = 0;

  while (!snake.collision()) {
    nodelay(stdscr, !debug);
    int input = getch();
    switch (input)
    {
      case KEY_LEFT:
        snake.movesnake(TURN_LEFT);
          wait_time = clock();
        break;
      case KEY_UP:
        snake.movesnake(TURN_UP);
          wait_time = clock();
        break;
      case KEY_DOWN:
        snake.movesnake(TURN_DOWN);
        wait_time = clock();
        break;
      case KEY_RIGHT:
        snake.movesnake(TURN_RIGHT);
          wait_time = clock();
        break;
      case KEY_BACKSPACE:
        if (askResume()) nodelay(stdscr, true);
        else return false;
        break;
      default:
        if (clock()-wait_time > 500000) {
          snake.movesnake();
          wait_time = clock();
        }
        break;
    }
    render(); 
    updateBoard();

    end_time = clock();
    loop_count++;
    FPS = 1.0/((((double)(end_time-start_time))/((double)loop_count))/(double)(CLOCKS_PER_SEC));
    mvwprintw(fpsBoard, 0, 5, "FPS: %.2f", FPS);
    wrefresh(fpsBoard);

    // if (snake.isMissionComplete()) {
    //   stageNum++;
    //   snake.newStage(stageNum);
    // }
  } // end of game loop

  return askRestart();
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
  mvwprintw(stageBoard, 2, 4, "SCORE: %d", snake.points);

  mvwprintw(scoreBoard, 1, 10, "Score Board");
  mvwprintw(scoreBoard, 2, 4, "B: %d / %d", 3, 20);
  mvwprintw(scoreBoard, 3, 4, "+: %d", 5);
  mvwprintw(scoreBoard, 4, 4, "-: %d", 5);
  mvwprintw(scoreBoard, 5, 4, "G: %d", 5);

  mvwprintw(missionBoard, 1, 11, "Missions");
  mvwprintw(missionBoard, 2, 4, "B: %d", 3/20);
  mvwprintw(missionBoard, 3, 4, "+: %d", 5);
  mvwprintw(missionBoard, 4, 4, "-: %d", 5);
  mvwprintw(missionBoard, 5, 4, "G: %d", 5);

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

bool Game::askRestart()
{
  WINDOW* gameoverWin = newwin(4, 21, 13, 20);
  box(gameoverWin, 0, 0);
  wrefresh(gameoverWin);

  std::vector<std::string> choices = {"Restart", "Quit"};
  int choice;
  int highlight=0;

  mvwprintw(gameoverWin, 0, 3, "GAME OVER");

  while (1) {
    for (int i=0; i<choices.size(); i++) {
      if (i == highlight) wattron(gameoverWin, A_REVERSE);
      mvwprintw(gameoverWin, i+1, 2, choices[i].c_str());
      wattroff(gameoverWin, A_REVERSE);
    }
    wrefresh(gameoverWin);
    nodelay(stdscr, false);
    choice = getch();

    switch(choice) {
      case KEY_UP:
        highlight--;
        if (highlight < 0) highlight = 0;
        break;
      case KEY_DOWN:
        highlight++;
        if (highlight > choices.size()-1) highlight = choices.size()-1;
        break;
      default:
        break;
    }

    if (choice == 10) break;
  }
  wclear(gameoverWin);
  wrefresh(gameoverWin);
  delwin(gameoverWin);
  refresh();

  if (highlight == 0) return true;
  else return false;
}

bool Game::askResume()
{
  WINDOW* resumeWin = newwin(4, 21, 13, 20);
  box(resumeWin, 0, 0);
  wrefresh(resumeWin);

  std::vector<std::string> choices = {"Resume", "Quit"};
  int choice;
  int highlight=0;

  mvwprintw(resumeWin, 0, 3, "PAUSED");

  while (1) {
    for (int i=0; i<choices.size(); i++) {
      if (i == highlight) wattron(resumeWin, A_REVERSE);
      mvwprintw(resumeWin, i+1, 2, choices[i].c_str());
      wattroff(resumeWin, A_REVERSE);
    }
    wrefresh(resumeWin);
    nodelay(stdscr, false);
    choice = getch();

    switch(choice) {
      case KEY_UP:
        highlight--;
        if (highlight < 0) highlight = 0;
        break;
      case KEY_DOWN:
        highlight++;
        if (highlight > choices.size()-1) highlight = choices.size()-1;
        break;
      default:
        break;
    }

    if (choice == 10) break;
  }
  wclear(resumeWin);
  wrefresh(resumeWin);
  delwin(resumeWin);

  if (highlight == 0) return true;
  else return false;
}