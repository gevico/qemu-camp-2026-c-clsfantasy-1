#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
    int score;
} Student;

Student students[MAX_STUDENTS];
Student temp[MAX_STUDENTS];

void merge(int left, int mid, int right) {
    int i = left;      // 左半部分起始索引
    int j = mid + 1;   // 右半部分起始索引
    int k = left;      // 临时数组 temp 的起始索引

    // 比较并合并两个有序子序列到临时数组 temp 中
    while (i <= mid && j <= right) {
        // 目标是从高到低排序，所以成绩大的优先放入
        if (students[i].score >= students[j].score) {
            temp[k++] = students[i++];
        } else {
            temp[k++] = students[j++];
        }
    }

    // 将左半部分剩余的元素放入 temp
    while (i <= mid) {
        temp[k++] = students[i++];
    }

    // 将右半部分剩余的元素放入 temp
    while (j <= right) {
        temp[k++] = students[j++];
    }

    // 将排序好的 temp 数组内容复制回原数组 students
    for (int p = left; p <= right; p++) {
        students[p] = temp[p];
    }
}

void merge_sort(int left, int right) {
    // 递归终止条件：子序列只有一个元素时自然有序
    if (left >= right) {
        return;
    }

    // 找到中间位置，防止 (left+right)/2 在极端情况下溢出
    int mid = left + (right - left) / 2;

    // 分：递归地对左右两半进行排序
    merge_sort(left, mid);
    merge_sort(mid + 1, right);

    // 治：合并两个有序序列
    merge(left, mid, right);
}

int main(void) {
    FILE *file = fopen("02_students.txt", "r");
    if (!file) {
        printf("错误：无法打开文件 02_students.txt\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);

    if (n <= 0 || n > MAX_STUDENTS) {
        printf("学生人数无效：%d\n", n);
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%s %d", students[i].name, &students[i].score);
    }
    fclose(file);

    merge_sort(0, n - 1);

    printf("\n归并排序后按成绩从高到低排序的学生名单：\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].name, students[i].score);
    }

    return 0;
}