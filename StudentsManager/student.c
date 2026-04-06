#include "student.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

// 全局变量定义
Student students[MAX_STUDENTS];
int studentCount = 0;

// 1. 输入学生信息
void inputStudents(void) {
  printf("\n--- 输入学生信息 ---\n");
  printf("请输入学生人数：");
  scanf("%d", &studentCount);

  for (int i = 0; i < studentCount; i++) {
    printf("\n第%d个学生：\n", i + 1);
    printf("学号：");
    scanf("%d", &students[i].id);
    printf("姓名：");
    scanf("%s", students[i].name);
    printf("成绩：");
    scanf("%f", &students[i].score);
    students[i].total = students[i].score;
  }
  printf("\n输入完成！共输入%d名学生。\n", studentCount);
  waitForEnter();
}

// 2. 增加学生记录
void addStudent(void) {
  if (studentCount >= MAX_STUDENTS) {
    printf("学生记录已满，无法添加！\n");
    waitForEnter();
    return;
  }

  printf("\n--- 增加学生记录 ---\n");
  printf("学号：");
  scanf("%d", &students[studentCount].id);
  printf("姓名：");
  scanf("%s", students[studentCount].name);
  printf("成绩：");
  scanf("%f", &students[studentCount].score);
  students[studentCount].total = students[studentCount].score;
  studentCount++;

  printf("\n添加成功！\n");
  waitForEnter();
}

// 3. 按学号查询
void searchById(void) {
  int id, found = 0;
  printf("\n--- 按学号查询 ---\n");
  printf("请输入要查询的学号：");
  scanf("%d", &id);

  for (int i = 0; i < studentCount; i++) {
    if (students[i].id == id) {
      printf("\n学号：%d\n", students[i].id);
      printf("姓名：%s\n", students[i].name);
      printf("成绩：%.2f\n", students[i].score);
      found = 1;
      break;
    }
  }

  if (!found) {
    printf("未找到学号为%d的学生！\n", id);
  }
  waitForEnter();
}

// 4. 按姓名查询
void searchByName(void) {
  char name[20];
  int found = 0;
  printf("\n--- 按姓名查询 ---\n");
  printf("请输入要查询的姓名：");
  scanf("%s", name);

  for (int i = 0; i < studentCount; i++) {
    if (strcmp(students[i].name, name) == 0) {
      printf("\n学号：%d\n", students[i].id);
      printf("姓名：%s\n", students[i].name);
      printf("成绩：%.2f\n", students[i].score);
      found = 1;
    }
  }

  if (!found) {
    printf("未找到姓名为%s的学生！\n", name);
  }
  waitForEnter();
}

// 5. 删除学生记录
void deleteStudent(void) {
  int id, found = 0;
  printf("\n--- 删除学生记录 ---\n");
  printf("请输入要删除的学生学号：");
  scanf("%d", &id);

  for (int i = 0; i < studentCount; i++) {
    if (students[i].id == id) {
      for (int j = i; j < studentCount - 1; j++) {
        students[j] = students[j + 1];
      }
      studentCount--;
      found = 1;
      printf("删除成功！\n");
      break;
    }
  }

  if (!found) {
    printf("未找到学号为%d的学生！\n", id);
  }
  waitForEnter();
}

// 6. 修改学生记录
void modifyStudent(void) {
  int id, found = 0;
  printf("\n--- 修改学生记录 ---\n");
  printf("请输入要修改的学生学号：");
  scanf("%d", &id);

  for (int i = 0; i < studentCount; i++) {
    if (students[i].id == id) {
      printf("\n当前信息：\n");
      printf("学号：%d\n", students[i].id);
      printf("姓名：%s\n", students[i].name);
      printf("成绩：%.2f\n", students[i].score);

      printf("\n请输入新信息：\n");
      printf("新学号：");
      scanf("%d", &students[i].id);
      printf("新姓名：");
      scanf("%s", students[i].name);
      printf("新成绩：");
      scanf("%f", &students[i].score);
      students[i].total = students[i].score;

      printf("修改成功！\n");
      found = 1;
      break;
    }
  }

  if (!found) {
    printf("未找到学号为%d的学生！\n", id);
  }
  waitForEnter();
}

// 7. 输出学生记录
void outputStudents(void) {
  printf("\n--- 所有学生记录 ---\n");
  if (studentCount == 0) {
    printf("暂无学生记录！\n");
    waitForEnter();
    return;
  }

  printf("==========================================\n");
  printf("学号\t姓名\t成绩\t总分\n");
  printf("==========================================\n");
  for (int i = 0; i < studentCount; i++) {
    printf("%d\t%s\t%.2f\t%.2f\n", students[i].id, students[i].name,
           students[i].score, students[i].total);
  }
  printf("==========================================\n");
  printf("共%d名学生。\n", studentCount);
  waitForEnter();
}

// 8. 按姓名排序（冒泡排序）
void sortByName(void) {
  Student temp;
  for (int i = 0; i < studentCount - 1; i++) {
    for (int j = 0; j < studentCount - 1 - i; j++) {
      if (strcmp(students[j].name, students[j + 1].name) > 0) {
        temp = students[j];
        students[j] = students[j + 1];
        students[j + 1] = temp;
      }
    }
  }
  printf("\n已按姓名排序！\n");
  outputStudents();
}

// 9. 按学号排序
void sortById(void) {
  Student temp;
  for (int i = 0; i < studentCount - 1; i++) {
    for (int j = 0; j < studentCount - 1 - i; j++) {
      if (students[j].id > students[j + 1].id) {
        temp = students[j];
        students[j] = students[j + 1];
        students[j + 1] = temp;
      }
    }
  }
  printf("\n已按学号排序！\n");
  outputStudents();
}

// 10. 按成绩升序排序
void sortByScoreAsc(void) {
  Student temp;
  for (int i = 0; i < studentCount - 1; i++) {
    for (int j = 0; j < studentCount - 1 - i; j++) {
      if (students[j].score > students[j + 1].score) {
        temp = students[j];
        students[j] = students[j + 1];
        students[j + 1] = temp;
      }
    }
  }
  printf("\n已按成绩升序排序！\n");
  outputStudents();
}

// 11. 按总分降序排序
void sortByTotalDesc(void) {
  Student temp;
  for (int i = 0; i < studentCount - 1; i++) {
    for (int j = 0; j < studentCount - 1 - i; j++) {
      if (students[j].total < students[j + 1].total) {
        temp = students[j];
        students[j] = students[j + 1];
        students[j + 1] = temp;
      }
    }
  }
  printf("\n已按总分降序排序！\n");
  outputStudents();
}

// 12. 成绩统计
void calculateStats(void) {
  if (studentCount == 0) {
    printf("暂无学生记录，无法统计！\n");
    waitForEnter();
    return;
  }

  float sum = 0, average, maxScore, minScore;
  int passCount = 0, failCount = 0;

  maxScore = minScore = students[0].score;

  for (int i = 0; i < studentCount; i++) {
    sum += students[i].score;

    if (students[i].score > maxScore) {
      maxScore = students[i].score;
    }
    if (students[i].score < minScore) {
      minScore = students[i].score;
    }

    if (students[i].score >= 60) {
      passCount++;
    } else {
      failCount++;
    }
  }

  average = sum / studentCount;

  printf("\n========== 成绩统计 ==========\n");
  printf("学生总数：%d\n", studentCount);
  printf("总分：%.2f\n", sum);
  printf("平均分：%.2f\n", average);
  printf("最高分：%.2f\n", maxScore);
  printf("最低分：%.2f\n", minScore);
  printf("及格人数：%d (%.1f%%)\n", passCount,
         (float)passCount / studentCount * 100);
  printf("不及格人数：%d (%.1f%%)\n", failCount,
         (float)failCount / studentCount * 100);
  printf("==============================\n");
  waitForEnter();
}