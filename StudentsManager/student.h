#ifndef STUDENT_H
#define STUDENT_H

#define MAX_STUDENTS 100

// 学生结构体
typedef struct {
  int id;        // 学号
  char name[20]; // 姓名
  float score;   // 成绩
  float total;   // 总分
} Student;

// 全局变量声明
extern Student students[MAX_STUDENTS];
extern int studentCount;

// 学生管理功能函数声明
void inputStudents(void);   // 1. 输入学生信息
void addStudent(void);      // 2. 增加学生记录
void searchById(void);      // 3. 按学号查询
void searchByName(void);    // 4. 按姓名查询
void deleteStudent(void);   // 5. 删除学生记录
void modifyStudent(void);   // 6. 修改学生记录
void outputStudents(void);  // 7. 输出学生记录
void sortByName(void);      // 8. 按姓名排序
void sortById(void);        // 9. 按学号排序
void sortByScoreAsc(void);  // 10. 按成绩升序排序
void sortByTotalDesc(void); // 11. 按总分降序排序
void calculateStats(void);  // 12. 成绩统计
void waitForEnter(void);
#endif