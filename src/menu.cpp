#include <iostream>

#include <ncurses.h>

#include <string>
#include <vector>

#include "menu.h"
#include "game.h"

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

  WINDOW* menuwin = newwin(4, 30, yMax/2+2, xMax/2-15);
  box(menuwin, 0, 0);
  refresh();
  wrefresh(menuwin);

  keypad(menuwin, true);


  std::vector<std::string> logo = { "    ____             __     __                 ",
                                    "   / __ \\   __  __  / /_   / /_   ____    ____ ",
                                    "  / /_/ /  / / / / / __/  / __ \\ / __ \\  / __ \\",
                                    " / ____/  / /_/ / / /_   / / / // /_/ / / / / /",
                                    "/_/       \\__, /  \\__/  /_/ /_/ \\____/ /_/ /_/ ",
                                    "         /____/                                "};

  for (int i=0; i<logo.size(); i++) {
    mvprintw(yMax/2 - 5 + i, xMax/2 - 24, logo[i].c_str());
  }
  refresh();


  std::vector<std::string> choices = {"Game Start", "Quit"};
  int choice;
  int highlight=0;

  while (1) {
    for (int i=0; i<choices.size(); i++) {
      if (i == highlight) wattron(menuwin, A_REVERSE);
      mvwprintw(menuwin, i+1, 2, choices[i].c_str());
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
  refresh();
  return highlight;
}

void run(bool debug)
{
  int select = menuUI();
  if (select == 0) {
    clear();
    refresh();
    Game snakeGame(debug);
    while (1){
      bool restart = snakeGame.start();
      if (!restart) break;
    }
  }
}
