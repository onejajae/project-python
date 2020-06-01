#include <ncurses.h>

#include "menu.h"

using namespace std;

int main(int argc, char **argv)
{
  if (init() == 0) run();

  endwin();

  return 0;
}
