#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

// 跨平台的清屏函数
void clearScreen(void) {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

// 等待用户按回车键
void waitForEnter(void) {
  printf("按回车键继续...");
  while (getchar() != '\n')
    ; // 清空缓冲区
  getchar();
}