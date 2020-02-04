#include "screen.h"

int main() {
  Screen scr(24, 80, '-');
  scr.set('a');
  scr.move(10, 10).set('#');
  scr.display(std::cout);
}
