#include "file.h"
#include "student.h"
#include "utils.h"
#include <stdio.h>

#define FILENAME "students.dat"

// 13. 保存到文件
void saveToFile(void) {
  FILE *fp = fopen(FILENAME, "wb");
  if (fp == NULL) {
    printf("无法打开文件！\n");
    waitForEnter();
    return;
  }

  fwrite(&studentCount, sizeof(int), 1, fp);
  fwrite(students, sizeof(Student), studentCount, fp);
  fclose(fp);

  printf("数据已保存到文件 %s\n", FILENAME);
  waitForEnter();
}

// 14. 从文件读取
void loadFromFile(void) {
  FILE *fp = fopen(FILENAME, "rb");
  if (fp == NULL) {
    // 首次运行，没有文件是正常的
    return;
  }

  fread(&studentCount, sizeof(int), 1, fp);
  fread(students, sizeof(Student), studentCount, fp);
  fclose(fp);

  printf("成功读取 %d 条学生记录！\n", studentCount);
  waitForEnter();
}