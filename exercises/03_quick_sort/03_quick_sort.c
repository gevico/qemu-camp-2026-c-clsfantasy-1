#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN     50

typedef struct {
    char name[NAME_LEN];
    int score;
} Student;

Student students[MAX_STUDENTS];

void quick_sort(int left, int right) {
    if (left >= right) {
        return;
    }

    // 选择最右边的元素作为基准 (Pivot)
    Student pivot = students[right];
    int i = left; 

    for (int j = left; j < right; j++) {
        // 从高到低排序：如果当前学生成绩大于等于基准，则交换到左边
        if (students[j].score >= pivot.score) {
            Student temp = students[i];
            students[i] = students[j];
            students[j] = temp;
            i++;
        }
    }

    // 将基准元素放到正确的位置
    students[right] = students[i];
    students[i] = pivot;

    // 递归排序左半部分和右半部分
    quick_sort(left, i - 1);
    quick_sort(i + 1, right);
}

int main(void) {
    // 优先尝试从练习目录读取，失败则尝试直接读取（适配不同运行环境）
    const char *path = "exercises/03_quick_sort/03_students.txt";
    FILE *file = fopen(path, "r");
    if (!file) {
        file = fopen("03_students.txt", "r");
        if (!file) {
            printf("错误：无法打开文件 %s 或 03_students.txt\n", path);
            return 1;
        }
    }

    int n;
    fscanf(file, "%d", &n);

    if (n <= 0 || n > MAX_STUDENTS) {
        printf("学生人数无效：%d（应为 1-%d）\n", n, MAX_STUDENTS);
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%s %d", students[i].name, &students[i].score);
    }
    fclose(file);

    quick_sort(0, n - 1);

    // 输出结果
    printf("\n快速排序后按成绩从高到低排序的学生名单：\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].name, students[i].score);
    }

    return 0;
}