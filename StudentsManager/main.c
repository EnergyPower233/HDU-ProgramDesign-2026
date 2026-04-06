#include "file.h"
#include "menu.h"
#include "student.h"
#include <stdio.h>

int main() {
  int choice;

  // 尝试加载已有数据
  loadFromFile();

  while (1) {
    showMenu();
    scanf("%d", &choice);

    // 清空输入缓冲区
    while (getchar() != '\n')
      ;

    switch (choice) {
    case 1:
      inputStudents();
      break;
    case 2:
      addStudent();
      break;
    case 3:
      searchById();
      break;
    case 4:
      searchByName();
      break;
    case 5:
      deleteStudent();
      break;
    case 6:
      modifyStudent();
      break;
    case 7:
      outputStudents();
      break;
    case 8:
      sortByName();
      break;
    case 9:
      sortById();
      break;
    case 10:
      sortByScoreAsc();
      break;
    case 11:
      sortByTotalDesc();
      break;
    case 12:
      calculateStats();
      break;
    case 13:
      saveToFile();
      break;
    case 14:
      loadFromFile();
      break;
    case 0:
      exitSystem();
      break;
    default:
      printf("无效选择，请重新输入！\n");
      waitForEnter();
      break;
    }
  }

  return 0;
}