#include "menu.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

// 显示主菜单
void showMenu(void) {
  clearScreen();
  printf("\n");
  printf("==========================================\n");
  printf("       学生成绩管理系统\n");
  printf("==========================================\n");
  printf("  1. 输入学生信息\n");
  printf("  2. 增加学生记录\n");
  printf("  3. 按学号查询\n");
  printf("  4. 按姓名查询\n");
  printf("  5. 删除学生记录\n");
  printf("  6. 修改学生记录\n");
  printf("  7. 输出学生记录\n");
  printf("  8. 按姓名排序\n");
  printf("  9. 按学号排序\n");
  printf(" 10. 按成绩升序排序\n");
  printf(" 11. 按总分降序排序\n");
  printf(" 12. 成绩统计\n");
  printf(" 13. 学生记录存盘\n");
  printf(" 14. 读取磁盘记录\n");
  printf("  0. 退出系统\n");
  printf("==========================================\n");
  printf("请选择功能：");
}

// 0. 退出系统
void exitSystem(void) {
  printf("\n感谢使用学生成绩管理系统！\n");
  printf("再见！\n");
  exit(0);
}