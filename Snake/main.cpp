#include "Snake.h"
void main_loop() {
  while (true) {
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
    case 4:
      exit(0);
    }
  }
}
int main() { main_loop(); }