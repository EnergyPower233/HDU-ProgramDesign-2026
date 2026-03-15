#include "Snake.h"
#include <cassert>
extern SNAKE s;
extern std::set<std::pair<int, int>> foodPlace;
extern std::mt19937 rnd;
extern char nowDir;
extern int score,foodType;

void createFood() {
    foodType=rnd()%3;
  int cnt = rnd() % s.nullPlace.size();
  auto tmp = s.nullPlace.begin();
  assert(cnt<s.nullPlace.size());
  while (cnt) {
    ++tmp;
    --cnt;
  }
  foodPlace.insert(*tmp);
  auto [x, y] = *tmp;
  s.nullPlace.erase(tmp);
}

static void initializeSnake() {
  s.pushBack(MAX_WIDTH / 2, MAX_HEIGHT / 2);
  int tmp = rnd() % 4;
  if (tmp == 0)
    nowDir = 'w';
  if (tmp == 1)
    nowDir = 'a';
  if (tmp == 2)
    nowDir = 's';
  if (tmp == 3)
    nowDir = 'd';
}

extern void PrintBoader();
// Initialization
void init() {
  system("cls");
  foodPlace.clear();

  Hide();
  // std::cout<<'a'<<std::endl;
  // Sleep(20000);
  s.clear();
  score = 0;
  for (int i = 1; i < MAX_WIDTH-1; ++i)
    for (int j = 1; j < MAX_HEIGHT-1; ++j)
      s.nullPlace.insert({i, j});
    PrintBoader();
  // 在地图中间生成蛇头，并随机一个方向
  initializeSnake();
  // 随机生成食物
  createFood();

  print();
}