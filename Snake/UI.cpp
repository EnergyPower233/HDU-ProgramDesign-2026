#include "Snake.h"
#include <Windows.h>
#include <conio.h>
#include <stdio.h>

static void GotoXY(int x, int y) {
  HANDLE hout;
  COORD cor;
  hout = GetStdHandle(STD_OUTPUT_HANDLE);
  cor.X = x;
  cor.Y = y;
  SetConsoleCursorPosition(hout, cor);
}

static void Hide() {
  HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cor_info = {1, 0};
  SetConsoleCursorInfo(hout, &cor_info);
}

static void generateMenu() {
  GotoXY(40, 12);
  printf("   Welcome to Snake Game");
  GotoXY(43, 14);
  printf("   1. Start Game");
  GotoXY(43, 16);
  printf("   2. Help");
  GotoXY(43, 18);
  printf("   3. About");
  GotoXY(43, 20);
  printf("   4. Exit");
  Hide();
}

static void Select(int selection) {
  generateMenu();
  switch (selection) {
    break;
  case '1':
    GotoXY(43, 14);
    printf("-> 1. Start Game");
    break;
  case '2':
    GotoXY(43, 16);
    printf("-> 2. Help");
    break;
  case '3':
    GotoXY(43, 18);
    printf("-> 3. About");
    break;
  case '0':
    GotoXY(43, 20);
    printf("-> 4. Exit");
    break;
  }
}

static char Down(char &selection) {
  char previous_selection = selection - '0';
  char next_selection = (previous_selection + 1) % 4;
  return selection = next_selection + '0';
}

static char Up(char &selection) {
  char previous_selection = selection - '0';
  char next_selection = (previous_selection - 1 + 4) % 4;
  return selection = next_selection + '0';
}

int menu() {
  char selection = '1';
  Select(selection);
  while (true) {
    char input = _getch();
    switch (input) {
    case '1':
      selection = '1';
      Select('1');
      break;
    case '2':
      selection = '2';
      Select('2');
      break;
    case '3':
      selection = '3';
      Select('3');
      break;
    case '4':
      selection = '0';
      Select('0');
      break;
    case 's':
      Select(Down(selection));
      break;
    case 'w':
      Select(Up(selection));
      break;
    case '\r':
      system("cls");
      return selection - '0';
    }
  }
}

static void help() {
  system("cls");
  GotoXY(40, 12);
  printf("W - Up");
  GotoXY(40, 14);
  printf("S - Down");
  GotoXY(40, 16);
  printf("A - Left");
  GotoXY(40, 18);
  printf("D - Right");
  GotoXY(40, 20);
  printf("Game Over when hit wall or itself");
  GotoXY(45, 22);
  printf("Press any key to return");
  Hide();

  char ch = _getch();
  system("cls");
}

void about() {
  system("cls");
  GotoXY(30, 12);
  printf("Hangzhou Dianzi University");
  GotoXY(35, 14);
  printf("Snake Game - Console Application");
  GotoXY(43, 16);
  printf("Press any key to return");
  Hide();

  char ch = _getch();
  system("cls");
}
