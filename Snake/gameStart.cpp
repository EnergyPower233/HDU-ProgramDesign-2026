#include"Snake.h"
#include <random>
SNAKE s;
std::set<std::pair<int,int>> snakePlace,foodPlace,nullPlace;
std::mt19937 rnd(time(nullptr));
char nowDir;