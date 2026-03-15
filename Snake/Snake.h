#include <conio.h>
#include <ctime>
#include <iostream>
#include <memory>
#include <process.h>
#include <random>
#include <set>
#include <windows.h>

#define MAX_WIDTH 40
#define MAX_HEIGHT 30
class NODE {
private:
  int x, y;

public:
  NODE(int xVal, int yVal) : x(xVal), y(yVal) {}
  std::pair<int, int> getData() const { return {x, y}; }
  bool operator==(const NODE &a) const { return a.x == x && a.y == y; }
  bool operator!=(const NODE &a) const { return !(*this == a); }
};
using FOOD = NODE;
using node = NODE;
class snake : public std::enable_shared_from_this<snake> {
private:
  node x;
  std::shared_ptr<snake> nxt;
  std::weak_ptr<snake> pre;

public:
  snake(node xVal) : x(xVal) {}
  std::pair<int, int> getData() const { return x.getData(); }
  void setData(node xVal) { x = xVal; }
  std::shared_ptr<snake> getNxt() const { return nxt; }
  std::shared_ptr<snake> getPre() const { return pre.lock(); }
  void setNxt(std::shared_ptr<snake> next) { nxt = next; }
  void setPre(std::shared_ptr<snake> prev) { pre = prev; }
};
void GotoXY(int, int);
class SNAKE : public std::enable_shared_from_this<snake> {
private:
  std::shared_ptr<snake> head, tail;
  int size, speed;

public:
  std::set<std::pair<int, int>> snakePlace, nullPlace;
  SNAKE() : size(0), speed(600), head(nullptr), tail(nullptr) {}
  std::shared_ptr<snake> getHead() const { return head; }
  std::shared_ptr<snake> getTail() const { return tail; }
  int getSpeed() const { return speed; }
  void clear() {
    size = 0, speed = 600;
    snakePlace.clear();
    nullPlace.clear();
    if (!head)
      return;
    auto tmp = head->getNxt();
    while (tmp != head) {
      auto temp = tmp->getNxt();
      tmp->setNxt(nullptr);
      tmp->setPre(nullptr);
      tmp = temp;
    }
    head->setNxt(nullptr);
    head->setPre(nullptr);
    head = tail = nullptr;
  }
  void setSpeed(int x) { speed = x; }
  void pushBack(int x, int y) {
    nullPlace.erase({x, y});
    snakePlace.insert({x, y});
    auto newNode = std::make_shared<snake>(node(x, y));
    if (!head) {
      head = tail = newNode;
      newNode->setNxt(newNode);
      newNode->setPre(newNode);
    } else {
      newNode->setNxt(head);
      newNode->setPre(tail);
      tail->setNxt(newNode);
      head->setPre(newNode);
      tail = newNode;
    }
    ++size;
  }
  void rotate() {
    if (!head || head == tail)
      return;
    head = head->getPre();
    tail = tail->getPre();
  }
  void replaceHead(int x, int y) {
    if (head) {
      auto [tx, ty] = head->getData();
      GotoXY(tx, ty);
      printf(" ");
      nullPlace.insert(head->getData());
      snakePlace.erase(head->getData());
      head->setData(node(x, y));
      nullPlace.erase(head->getData());
      snakePlace.insert(head->getData());
    }
  }
  void moveSnake(int x, int y) {
    rotate();
    replaceHead(x, y);
  }
  void cut(int x, int y) {
    auto tmp = head;
    int cnt = 0;
    while (tmp->getData() != (std::pair<int, int>){x, y}) {
      tmp = tmp->getNxt();
      ++cnt;
    }
    tail = tmp->getPre();
    head->setPre(tail);
    tail->setNxt(head);
    size = cnt;
    while (tmp != head) {
      snakePlace.erase(tmp->getData());
      nullPlace.insert(tmp->getData());
      auto [tx, ty] = tmp->getData();
      GotoXY(tx, ty);
      printf(" ");
      auto temp = tmp->getNxt();
      tmp->setNxt(nullptr);
      tmp->setPre(nullptr);
      tmp = temp;
    }
  }
  void getFood(FOOD food) {
    auto [x, y] = food.getData();
    pushBack(x, y);
    rotate();
  }
};
int menu();
void init();
void print();
int check(int, int);
void begin();
void main_loop();
void createFood();
void gameOver();
void Hide();
void help();
void about();
void printBlank();