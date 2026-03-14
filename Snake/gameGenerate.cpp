#include "Snake.h"
extern SNAKE s;
extern std::set<std::pair<int, int>> foodPlace;
extern std::mt19937 rnd;
extern char nowDir;
extern int score;

void PrintSnake() {
  for (auto [x, y] : s.snakePlace) {
    GotoXY(x, y);
    auto head = s.getHead()->getData();
    if (head == (std::pair<int, int>){x, y}) {
      switch (nowDir) {
      case 'w':
        printf("^");
      case 'a':
        printf("<");
      case 's':
        printf("v");
      case 'd':
        printf(">");
      }
    } else {
      printf("o");
    }
  }
}

void PrintFood() {
  for (auto [x, y] : foodPlace) {
    GotoXY(x, y);
    printf("*");
  }
}

void PrintBoader() {
  for (int i = 0; i < MAX_WIDTH; i++) {
    GotoXY(i, 0);
    printf("-");
    GotoXY(i, MAX_HEIGHT - 1);
    printf("-");
  }
  for (int i = 1; i < MAX_HEIGHT - 1; i++) {
    GotoXY(0, i);
    printf("|");
    GotoXY(MAX_WIDTH - 1, i);
    printf("|");
  }
  GotoXY(50, 5);
  printf("Score: %d",score);
}

void print() {
    PrintBoader();
    PrintSnake();
    PrintFood();
}