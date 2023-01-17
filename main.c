#include <stdio.h>
#include <string.h>

// 结构体 - 用于学生信息存储
struct example {
    int DB_ID;          // 数据库的编号
    char STU_ID[33];    // 学生的学号
    char STU_name[65];  // 学生的姓名
    int STU_score;      // 学生的成绩
};

// 自定义函数

// 文件长度获取
// 参数：文件指针
long int getFileSize(FILE *fp) {
    long int fileSize;          // 文件长度

    fseek(fp, 0, SEEK_END);     // 移动指针到达最后一行
    fileSize = ftell(fp);       // 获取文件长度
    fseek(fp, 0, SEEK_SET);     // 还原指针到文件开头

    return fileSize;            // 返回文件长度
}

// [Y/N] 过滤器
// 参数：要过滤的字符变量
void filter_YN(char userInput) {
    int flag_InputValid = 0;    // 默认值为 0 ，用户输入合法的话就会变为 1

    do{
        scanf("%c", &userInput);

        if(userInput == "Y") {
            flag_InputValid = 1;
        } else if (userInput == "N") {
            flag_InputValid = 1;
        } else {
            printInputInvalid(1);
        }
    } while(flag_InputValid == 1);
}

// 自定义输出 - 提示信息

// 通用 - 输入不合法 - 自定义提示
// 参数： 0 - 正常输入提示 / 1 - 确定[Y/N]输入提示
void printInputInvalid(int tipStatus) {
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　　　 输入不合法，请重新输入 　　　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    if(tipStatus == 0) {
        printf("输入选项以继续: ");
    } else if (tipStatus == 1) {
        printf("输入选项以继续[Y/N]: ");
    }
}

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

// 层 4 - 数据库为空 - 自定义提示
void printEditWarn() {
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　学生信息管理系统　－　数据库操作　　　　　　　　│\n");
    printf("├────────────────────────────────────────────────────────────────┤\n");
    printf("│　　　　　　　　　　　　检测到数据库为空　　　　　　　　　　　　│\n");
    printf("│　　　　　　　　　　　　是否进入数据录入　　　　　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    printf("┌───────────────────────────────┐┌───────────────────────────────┐\n");
    printf("│　　　　　　[Y]  是　　　　　　││　　　　　　[N]  否　　　　　　│\n");
    printf("└───────────────────────────────┘└───────────────────────────────┘\n");
    printf("输入选项以继续[Y/N]: ");
}

// 层 4 - 数据库操作 - 自定义提示
void printEditHint(char name[33]) {
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　学生信息管理系统　－　数据库操作　　　　　　　　│\n");
    printf("├────────────────────────────────────────────────────────────────┤\n");
    printf("│　　　　　　　　 [1] - 向数据库末尾录入新内容 　　　　　　　　│\n");
    printf("│　　　　　　　　 [2] - 查找或修改指定项目 　　　　　　　　　　│\n");
    printf("│　　　　　　　　 [3] - 数据库统计信息 　　　　　　　　　　　　│\n");
    printf("│　　　　　　　　 [0] - 关闭数据库 　　　　　　　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    printf("当前操作的数据库：%s\n", name);
    printf("输入选项以继续: ");
}

// 层 5 - 数据库录入 - 学生数量 - 自定义提示
void printInputSum(char name[33]) {
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　学生信息管理系统　－　数据库录入　　　　　　　　│\n");
    printf("├────────────────────────────────────────────────────────────────┤\n");
    printf("│　　　　　　　　　　 请输入要录入的学生总数 　　　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    printf("当前操作的数据库：%s\n", name);
    printf("输入数量以继续: ");
}

int main() {
    // 层 1 - 用户输入
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
            // 没有发生错误的话输出成功提示
            if(fp == NULL) {
                printOpenFail();
            } else {
                printOpenSuccess();
                flag_openSuccess = 1;
            }
        }

        // 打开文件后的操作
        if(flag_openSuccess == 1) {
            // 层 4 - 用户输入
            int editInput = -1;

            // 这里套个 do while 循环，来实现操作结束后重复返回编辑界面的能力
            do {
                // 检测文件长度，如果文件为空的话直接进入数据录入
                // 不为空的话输出编辑提示
                if(getFileSize(fp) == 0) {
                    char userInput;                 // 用户在确认进入数据录入环节的输入

                    printEditWarn();
                    filter_YN(userInput);           // 过滤确定和取消

                    // 如果用户输入的是 Y 则进入数据录入（直接修改用户的输入进入编辑模式）
                    // 用户输入的是 N 的话手动补充一个界面提示
                    if(userInput == "Y") {
                        editInput = 1;
                    } else {
                        printEditHint(DBinput);
                        scanf("%d", &editInput);
                    }
                } else {
                    printEditHint(DBinput);
                    scanf("%d", &editInput);
                }

                // 根据不同的用户输入，我们进入不同的功能
                if(editInput == 1) {
                    // 录入数据

                    // 变量
                    int studentSum = 0;

                    // 提示操作并获取要录入的学生总数
                    printInputSum(DBinput);
                    scanf("%d", &studentSum);

                    // 初始化结构体数组
                    struct example student[studentSum];

                    // 如果数据库为空则录入一下格式模板
                    if(getFileSize(fp) == 0) {
                        fprintf(fp, "- Start -\n");     // 文件开头
                        fprintf(fp, "%d", studentSum);  // 数据总数
                        fprintf(fp, "-  End  -");       // 文件结尾
                    }

                    // 循环获取录入的学生数据
                    
                } else if(editInput == 2) {
                    // 查找数据
                } else if(editInput == 3) {
                    // 统计数据
                }
            } while (editInput != 0);
        }
    } while(introInput != 0);

    printOutro();
    return(0);
}