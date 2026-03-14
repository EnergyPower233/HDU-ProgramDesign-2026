#include "Snake.h"
extern SNAKE s;
extern std::set<std::pair<int, int>> foodPlace;
extern std::mt19937 rnd;

static void createFood() {
  int cnt = rnd() % s.nullPlace.size();
  auto tmp = s.nullPlace.begin();
  while (cnt) {
    ++tmp;
    --cnt;
  }
  foodPlace.insert(*tmp);
  auto [x, y] = *tmp;
  s.nullPlace.erase(tmp);
  GotoXY(x, y);
  printf("*");
}

static void initializeSnake() {}

extern void PrintBoader();
// Initialization
void init() {
  system("cls");
  Hide();
  for (int i = 0; i < MAX_HEIGHT; ++i)
    for (int j = 0; j < MAX_WIDTH; ++j)
      s.nullPlace.insert({i, j});

  // 在地图中间生成蛇头，并随机一个方向
  initializeSnake();
  // 随机生成食物
  createFood();

  PrintBoader();
}