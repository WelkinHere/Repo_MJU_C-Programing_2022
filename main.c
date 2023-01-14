#include <stdio.h>

// 层 1 - 自定义提示
void printIntro() {
    printf("\n");
    printf("----------------------------------------------\n");
    printf("               学生信息管理系统\n");
    printf("----------------------------------------------\n");
    printf("         [1] - 创建一个新数据库\n");
    printf("         [2] - 打开一个已有数据库\n");
    printf("         [0] - 退出程序\n");
    printf("----------------------------------------------\n");
    printf("输入选项以继续: ");
}

int main() {
    int introInput = -1;
    do{
        printIntro();
        scanf("%d", &introInput);
        if(introInput == 1) {

        } else if(introInput == 2) {

        }
    } while(introInput != 0);
}