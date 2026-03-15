#include "Snake.h"
extern SNAKE s;
extern std::set<std::pair<int, int>> foodPlace, barrierPlace;
extern std::mt19937 rnd;
extern char nowDir;
extern int score, foodType;
std::multiset<int> ScoreList;

void PrintSnake() {
  auto head = s.getHead()->getData();
  for (auto [x, y] : s.snakePlace) {
    GotoXY(x, y);
    if (head.first == x && head.second == y) {
      switch (nowDir) {
      case 'w':
        printf("^");
        break;
      case 'a':
        printf("<");
        break;
      case 's':
        printf("v");
        break;
      case 'd':
        printf(">");
        break;
      }
    } else {
      printf("o");
    }
  }
}

void PrintFood() {
  for (auto [x, y] : foodPlace) {
    GotoXY(x, y);
    if (foodType == 0)
      printf("*");
    if (foodType == 1)
      printf("0");
    if (foodType == 2)
      printf("@");
  }
}

void PrintBoader() {
  for (int i = 0; i < MAX_WIDTH; i++) {
    GotoXY(i, 0);
    printf("-");
    GotoXY(i, MAX_HEIGHT - 1);
    printf("-");
  }
  for (int i = 1; i < MAX_HEIGHT; i++) {
    GotoXY(0, i);
    printf("|");
    GotoXY(MAX_WIDTH - 1, i);
    printf("|");
  }
  int tmpx = 18;
  for (int i = 2; i < 25; ++i) {
    GotoXY(i, tmpx);
    printf("-");
    barrierPlace.insert({i, tmpx});
    s.nullPlace.erase({i, tmpx});
  }
  tmpx = 25;
  for (int i = 10; i < 24; ++i) {
    GotoXY(tmpx, i);
    printf("|");
    barrierPlace.insert({tmpx, i});
    s.nullPlace.erase({tmpx, i});
  }
  tmpx = 24;
  for (int i = 14; i <= 25; ++i) {
    GotoXY(i, tmpx);
    printf("-");
    barrierPlace.insert({i, tmpx});
    s.nullPlace.erase({i, tmpx});
  }
}
void printBlank() {
  for (int i = 0; i < MAX_HEIGHT; ++i)
    for (int j = 0; j < MAX_WIDTH; ++j) {
      GotoXY(i, j);
      printf(" ");
    }
}
void print() {
  PrintSnake();
  PrintFood();
  GotoXY(50, 5);
  printf("Score: %d", score);
  GotoXY(50, 6);
  printf("Score List:");
  int tmp = 6 + ScoreList.size();
  for (auto x : ScoreList) {
    GotoXY(50, tmp--);
    printf("%d. %d", tmp - 5, x);
  }
}