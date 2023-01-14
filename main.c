#include <stdio.h>
#include <string.h>

// 自定义函数 - 内容

// 层 1 - 提示信息 - 自定义提示
void printIntro() {
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　　　　　学生信息管理系统　　　　　　　　　　　　│\n");
    printf("├────────────────────────────────────────────────────────────────┤\n");
    printf("│　　　　　　　　　　[1] - 创建一个新数据库　　　　　　　　　　　│\n");
    printf("│　　　　　　　　　　[2] - 打开一个已有数据库　　　　　　　　　　│\n");
    printf("│　　　　　　　　　　[0] - 退出程序　　　　　　　　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    printf("输入选项以继续: ");
}

// 层 1 - 退出信息 - 自定义提示
void printOutro() {
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　　　学生信息管理系统正在退出　　　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
}

// 层 2 - 新数据库创建 - 自定义提示
void printNewDB() {
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　学生信息管理系统　－　新建数据库　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    printf("请输入要新建的数据库名称（最大长度限制 32 字符）: ");
}

// 层 2 - 打开数据库 - 自定义提示
void printOpenDB() {
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　学生信息管理系统　－　打开数据库　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    printf("请输入要打开的数据库名称（最大长度限制 32 字符）: ");
}

// 层 3 - 创建数据库 成功 - 自定义提示
void printNewSuccess() {
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　创建数据库成功，请记住您的数据库名称　　　　　　　│\n");
    printf("│　　　　　请注意，该操作不会清除已存在的同名数据库内容　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
}

// 层 3 - 打开数据库 失败 - 自定义提示
void printOpenFail() {
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　打开数据库失败，请确认数据库名称是否正确　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
}

// 层 3 - 打开数据库 成功 - 自定义提示
void printOpenSuccess() {
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　　　　　 打开数据库成功 　　　　　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
}

// 层 4 - 数据库操作 - 自定义提示
void printEditHint(char name[33]) {
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　学生信息管理系统　－　数据库操作　　　　　　　　│\n");
    printf("├────────────────────────────────────────────────────────────────┤\n");
    printf("│　　　　　　　　　[1] - 向数据库末尾录入新内容　　　　　　　　│\n");
    printf("│　　　　　　　　　[2] - 查找指定项目　　　　　　　　　　　　　│\n");
    printf("│　　　　　　　　　[0] - 关闭数据库　　　　　　　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    printf("当前操作的数据库：%s\n", name);
    printf("输入选项以继续: ");
}

int main() {
    int introInput = -1;
    do{
        // 输出程序提示文字并获取用户输入
        printIntro();
        scanf("%d", &introInput);

        // 数据库名称
        char DBinput[33];

        // 根据输入输出不同的提示
        if(introInput == 1) {
            printNewDB();
            scanf("%s", DBinput);
        } else if(introInput == 2) {
            printOpenDB();
            scanf("%s", DBinput);
        }

        // 所有数据库文件都存储在程序的所在文件夹内
        // 文件路径变量为 DBinput

        // 一个测试点，文件打开成功则为 1
        int flag_openSuccess = 0;

        // 初始化文件指针
        FILE *fp;

        // 以输入的操作为判断条件来进行 创建 / 打开 操作
        if(introInput == 1) {
            // fopen 函数里，参数 w+ 可以 以读写的形式 创建 / 打开一个二进制文件
            fp = fopen(DBinput, "w+");

            // 创建完成后关闭数据库并输出提示
            fclose(fp);
            printNewSuccess();
        } else if(introInput == 2) {
            // fopen 函数里，参数 r+ 可以 以读写的形式 打开一个二进制文件
            fp = fopen(DBinput, "r+");

            // 创建和打开数据库的功能是不一样的
            // 所以这里用了 r+ 参数，在打开失败的时候会报错

            // 这个 if 用来检测打开数据库的时候有没有发生错误
            // 有发生错误的话输出错误提示
            // 没有错误的话输出进一步操作的提示
            if(fp == NULL) {
                printOpenFail();
            } else {
                printOpenSuccess();
                flag_openSuccess = 1;
            }
        }

        // 打开文件后的操作
        if(flag_openSuccess == 1) {

        }
    } while(introInput != 0);

    printOutro();
    return(0);
}