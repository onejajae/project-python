#include <iostream>

#include <ncurses.h>

#include <string>
#include <vector>

#include "menu.h"
#include "snake.h"

int init()
{
  initscr();
  curs_set(0);
  noecho();
  cbreak();

  return 0;
}

int menuUI()
{
  int xMax, yMax;

  getmaxyx(stdscr, yMax, xMax);

  WINDOW* menuwin = newwin(4, 30, yMax/2-2, xMax/2-15);
  box(menuwin, 0, 0);
  refresh();
  wrefresh(menuwin);

  keypad(menuwin, true);

  std::vector<std::string> choices = {"Game Start", "Quit"};
  int choice;
  int highlight=0;

  while (1) {
    for (int i=0; i<choices.size(); i++) {
      if (i == highlight) wattron(menuwin, A_REVERSE);
      mvwprintw(menuwin, i+1, 1, choices[i].c_str());
      wattroff(menuwin, A_REVERSE);
    }
    choice = wgetch(menuwin);

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

    if (choice == 10) {
      break;
    }
  }
  wclear(menuwin);
  delwin(menuwin);
  return highlight;
}

void run()
{
  int select = menuUI();
  if (select == 0) {
    clear();
    snakeClass snake;
    snake.start();
  }
}
