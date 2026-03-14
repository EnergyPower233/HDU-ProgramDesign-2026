#include "Snake.h"
#include <cassert>
void main_loop() {
  while (true) {
    printBlank();
    int result = menu();
    switch (result) {
    case 1:
      init();
      begin();
      break;
    case 2:
      help();
      break;
    case 3:
      about();
      break;
    case 0:
      assert(0);
    }
  }
}
int main() { main_loop(); }