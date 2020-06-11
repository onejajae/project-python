#include <cstring>
#include <ncurses.h>

#include "menu.h"

using namespace std;

int main(int argc, char **argv)
{
  bool debug = false;
  for (int i=0; i<argc; i++) {
    if (strcmp(argv[i], "--debug")==0) debug=true;
  }
  
  if (init() == 0) run(debug);

  endwin();

  return 0;
}
