#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// 结构体 - 用于学生信息存储
struct example {
    int DB_ID;          // 数据库的编号
    char STU_ID[33];    // 学生的学号
    char STU_name[65];  // 学生的姓名
    int STU_score;      // 学生的成绩
};

// 自定义函数

// 更换开启状态
// 用途：把 0 变成 1，把除了 1 以外的数都变成 0.
void toggle(int value) {
    if(value == 0) {
        value = 1;
    } else {
        value = 0;
    }
}

// 文件行数获取
// 参数：文件指针
int getFileLine(FILE *fp) {
    int fileSize = 0;           // 文件长度，整型值
    char buffer[512];           // 缓冲区

    while(fgets(buffer, 512, fp) != NULL) {
        fileSize++;
    }

    return fileSize;
}

// 文件长度获取
// 参数：文件指针
long int getFileSize(FILE *fp) {
    long int fileSize;          // 文件长度

    fseek(fp, 0, SEEK_END);     // 移动指针到达最后一行
    fileSize = ftell(fp);       // 获取文件长度
    fseek(fp, 0, SEEK_SET);     // 还原指针到文件开头

    return fileSize;            // 返回文件长度
}

// 自定义输出 - 提示信息

// 通用 - 输入不合法 - 自定义提示
// 参数： 0 - 正常输入提示 / 1 - 确定[Y/N]输入提示
void printInputInvalid(int tipStatus) {
    // system("cls");
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　　　 输入不合法，请重新输入 　　　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    Sleep(1000);
}

// 层 1 - 提示信息 - 自定义提示
void printIntro() {
    // system("cls");
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
    // system("cls");
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　　　学生信息管理系统正在退出　　　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    Sleep(1000);
}

// 层 2 - 新数据库创建 - 自定义提示
void printNewDB() {
    // system("cls");
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　学生信息管理系统　－　新建数据库　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    printf("请输入要新建的数据库名称（最大长度限制 32 字符）: ");
}

// 层 2 - 打开数据库 - 自定义提示
void printOpenDB() {
    // system("cls");
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　学生信息管理系统　－　打开数据库　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    printf("请输入要打开的数据库名称（最大长度限制 32 字符）: ");
}

// 层 3 - 创建数据库 失败 - 自定义提示
void printNewFail() {
    // system("cls");
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　创建数据库失败，请更换您的数据库名称　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    Sleep(1000);
}

// 层 3 - 创建数据库 成功 - 自定义提示
void printNewSuccess() {
    // system("cls");
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　创建数据库成功，请记住您的数据库名称　　　　　　　│\n");
    printf("│　　　　　 请注意，该操作会清除已存在的同名数据库内容 　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    Sleep(3000);
}

// 层 3 - 打开数据库 失败 - 自定义提示
void printOpenFail() {
    // system("cls");
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　打开数据库失败，请确认数据库名称是否正确　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    Sleep(1000);
}

// 层 3 - 打开数据库 成功 - 自定义提示
void printOpenSuccess() {
    // system("cls");
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　　　　　 打开数据库成功 　　　　　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
}

// 层 4 - 数据库为空 - 自定义提示
void printEditWarn() {
    // system("cls");
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　　　　　检测到数据库为空　　　　　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
}

// 层 4 - 数据库操作 - 自定义提示
void printEditHint(char name[33]) {
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　学生信息管理系统　－　数据库操作　　　　　　　　│\n");
    printf("├────────────────────────────────────────────────────────────────┤\n");
    printf("│　　　　　　　　 [1] - 向数据库末尾录入新内容 　　　　　　　　　│\n");
    printf("│　　　　　　　　 [2] - 查找或修改指定项目 　　　　　　　　　　　│\n");
    printf("│　　　　　　　　 [3] - 数据库统计信息 　　　　　　　　　　　　　│\n");
    printf("│　　　　　　　　 [0] - 关闭数据库 　　　　　　　　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    printf("当前操作的数据库：%s\n", name);
}

// 层 5 - 数据库录入 - 学生数量 - 自定义提示
void printInputSum(char name[33]) {
    // system("cls");
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　学生信息管理系统　－　数据库录入　　　　　　　　│\n");
    printf("├────────────────────────────────────────────────────────────────┤\n");
    printf("│　　　　　　　　　　 请输入要录入的学生总数 　　　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    printf("当前操作的数据库：%s\n", name);
    printf("输入数量以继续: ");
}

// 层 5 - 数据库录入 开始 - 自定义提示
void printInputStart() {
    // system("cls");
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　　　　　 数据库录入开始 　　　　　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
}

// 层 5 - 数据库录入 提示 - 自定义提示
void printInputTip(char id[33], char name[65], int score) {
    // system("cls");
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　　　　　请确认录入的数据　　　　　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    printf("当前操作的学生学号：%s\n", id);
    printf("当前操作的学生姓名：%s\n", name);
    printf("当前操作的学生成绩：%d\n", score);
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　　　　　是否录入本次数据　　　　　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    printf("┌───────────────────────────────┐┌───────────────────────────────┐\n");
    printf("│　　　　　　[1]  是　　　　　　││　　　　　　[0]  否　　　　　　│\n");
    printf("└───────────────────────────────┘└───────────────────────────────┘\n");
    printf("输入选项以继续[1/0]: ");

}

// 层 5 - 数据库录入 成功 - 自定义提示
void printInputSuccess() {
    // system("cls");
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　　　　　　录入数据成功　　　　　　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    Sleep(1000);
}

// 层 5 - 数据库录入 结束 - 自定义提示
void printInputFinish() {
    // system("cls");
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　　　　　 数据库录入结束 　　　　　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    Sleep(1000);
}

// 层 5 - 数据库查询 - 自定义提示
void printSearchTips(char name[33]) {
    // system("cls");
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　学生信息管理系统　－　数据库查询　　　　　　　　│\n");
    printf("├────────────────────────────────────────────────────────────────┤\n");
    printf("│　　　　　　　　　　　　请选择查询的方式　　　　　　　　　　　　│\n");
    printf("├────────────────────────────────────────────────────────────────┤\n");
    printf("│　　　　　　　　　 [1] - 通过学号查询 　　　　　　　　　　　　 │\n");
    printf("│　　　　　　　　　 [2] - 通过姓名查询 　　　　　　　　　　　　 │\n");
    printf("│　　　　　　　　　 [3] - 通过数据库编号查询 　　　　　　　　　 │\n");
    printf("│　　　　　　　　　 [0] - 退出查询 　　　　　　　　　　　　　　 │\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    printf("当前操作的数据库：%s\n", name);
    printf("输入选项以继续: ");
}

// 层 5 - 数据库查询方式 - 自定义提示
// 参数：1 - 学号查询内容 / 2 - 姓名查询内容 / 3 - 数据库编号查询
void printSearchInput(int type) {
    // system("cls");
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　学生信息管理系统　－　数据库查询　　　　　　　　│\n");
    printf("├────────────────────────────────────────────────────────────────┤\n");

    if(type == 1) {
        printf("│　　　　　　　　　　　　　通过学号查询　　　　　　　　　　　　　　│\n");
        printf("└────────────────────────────────────────────────────────────────┘\n");
    } else if (type == 2) {
        printf("│　　　　　　　　　　　　　通过姓名查询　　　　　　　　　　　　　　│\n");
        printf("└────────────────────────────────────────────────────────────────┘\n");
    } else if (type == 3) {
        printf("│　　　　　　　　　　　 通过数据库编号查询 　　　　　　　　　　　　│\n");
        printf("└────────────────────────────────────────────────────────────────┘\n");
    }

    printf("输入查询内容以继续: ");
}

// 层 5 - 数据库查询结果 - 自定义提示
// 参数：整形值，用于显示搜索结果数目
void printSearchResult(int count) {
    // system("cls");
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　学生信息管理系统　－　数据库查询　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    printf("查询完毕，共计 %d 条匹配的项目。\n", count);

    if(count > 1) {
        printf("是否显示详细查询结果 [Y/N] ：");
    }
}

// 层 5 - 数据库查询详细 - 自定义提示
// 参数：传入要展示的 数据库编号 / 学号 / 姓名 / 成绩
void printSearchDetail(int PrintNum, int PrintSum, int DBnum, char STU_ID[33], char STU_name[65], int STU_score) {
    printf("\n查询结果 %d / %d : \n", PrintNum, PrintSum);
    printf("━┳━　数据库编号：%d\n", DBnum);
    printf("　┣━　学生学号：%s\n", STU_ID);
    printf("　┣━　学生姓名：%s\n", STU_name);
    printf("　┗━　学生成绩：%d\n", STU_score);
}

// 层 5 - 数据库查询结束提示 - 自定义提示
void printSearchEnd() {
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　学生信息管理系统　－　数据库查询　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    printf("查询结束，如需修改维护指定学生信息请使用 数据库编号 进行精确定位修改。\n");
}

// 层 6 - 数据库编辑进入提示
void printEditEntry() { 
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　学生信息管理系统　－　数据库查询　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    printf("查询结束，数据已定位。\n");
    printf("是否进入编辑模式 [Y/N] ：\n");
}

// 层 6 - 数据库编辑 - 自定义提示
void printEditTips(char name[33]) {
    // system("cls");
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　学生信息管理系统　－　数据库编辑　　　　　　　　│\n");
    printf("├────────────────────────────────────────────────────────────────┤\n");
    printf("│　　　　　　　　　 [1] - 修改学生信息 　　　　　　　　　　　　│\n");
    printf("│　　　　　　　　　 [2] - 删除学生信息 　　　　　　　　　　　　│\n");
    printf("│　　　　　　　　　 [3] - 查看选中的学生信息 　　　　　　　　　│\n");
    printf("│　　　　　　　　　 [0] - 退出修改 　　　　　　　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    printf("当前操作的数据库：%s\n", name);
    printf("输入选项以继续: ");
}

// 层 6 - 数据库编辑 - 自定义提示
void printEditContent(int EditID, int EditName, int EditScore) {
    // system("cls");
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│　　　　　　　　学生信息管理系统　－　数据库编辑　　　　　　　　│\n");
    printf("├────────────────────────────────────────────────────────────────┤\n");
    printf("│　　　　　　　　　　　　请选择修改的内容　　　　　　　　　　　　│\n");
    printf("├────────────────────────────────────────────────────────────────┤\n");

    if(EditID == 0){
        printf("│　　　　　　　　　　 [1] - 修改学生学号 　　　　　　　　　　　│\n");
    } else {
        printf("│　　　　　　　 [1] - 修改学生学号 - [已选中] 　　　　　　　　│\n");
    }
    
    if(EditName == 0){
        printf("│　　　　　　　　　　 [2] - 修改学生姓名 　　　　　　　　　　　│\n");
    } else {
        printf("│　　　　　　　 [2] - 修改学生姓名 - [已选中] 　　　　　　　　│\n");
    }
    
    if(EditScore == 0){
        printf("│　　　　　　　　　　 [3] - 修改学生成绩 　　　　　　　　　　　│\n");
    } else {
        printf("│　　　　　　　 [3] - 修改学生成绩 - [已选中] 　　　　　　　　│\n");
    }
    
    printf("│　　　　　　　　　　 [4] - 开始信息修改 　　　　　　　　　　　│\n");
    printf("│　　　　　　　　　　 [0] - 退出修改 　　　　　　　　　　　　　│\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    printf("输入选项以继续: ");
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
            // 一个标识符，如果这个名字可以被创建则为 1 反之为 0
            int flag_new = 0;
            do{
                printNewDB();
                scanf("%s", DBinput);

                if(DBinput == "DBcache") {
                    printNewFail();
                } else {
                    flag_new = 1;
                }
            } while(flag_new != 1);
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
                // 检测文件长度，如果文件为空的话输出警告
                if(getFileSize(fp) == 0) {
                    printEditWarn();
                    printEditHint(DBinput);
                    scanf("%d", &editInput);
                } else {
                    // system("cls");
                    printEditHint(DBinput);
                    scanf("%d", &editInput);
                }

                // 根据不同的用户输入，我们进入不同的功能
                if(editInput == 1) {
                    // 录入数据

                    // 变量
                    int studentSum = 0;     // 学生总数
                    int DBSum = 0;          // 数据库条目总数

                    // 提示操作并获取要录入的学生总数
                    printInputSum(DBinput);

                    int flag_studentCountValid = 0;

                    do {
                        scanf("%d", &studentSum);

                        if (studentSum > 0) {
                            flag_studentCountValid = 1;
                        } else {
                            printInputInvalid(0);
                        }
                    } while(flag_studentCountValid != 1);

                    printInputStart();

                    // 获取数据库已有内容数量
                    // 获取文件行数
                    int fileLine = -1;
                    if(getFileSize(fp) != 0) {
                        fileLine = getFileLine(fp);
                        printf("当前数据库内含有 %d 条数据。\n");
                    }

                    // 循环获取录入的学生数据
                    int i = 0; // 循环计数器
                    do {
                        // 变量
                        int DB_ID;          // 数据库编号
                        char STU_ID[33];    // 学生学号
                        char STU_name[65];  // 学生姓名
                        int STU_score = -1;      // 学生成绩

                        // 先把数据库录入到内存中
                        DB_ID = i + 1;
                        printf("请输入第 %d / %d 个学生的 学号 [长度限制32字符]：", i + 1, studentSum);
                        scanf("%s", STU_ID);
                        printf("请输入第 %d / %d 个学生的 姓名 [长度限制64字符]：", i + 1, studentSum);
                        scanf("%s", STU_name);
                        do {
                            printf("请输入第 %d / %d 个学生的 成绩 [成绩应为整数]：", i + 1, studentSum);
                            scanf("%d", &STU_score);
                            if(STU_score < 0) {
                                printInputInvalid(0);
                            }
                        } while (STU_score < 0);

                        // 然后再输出录入的结果
// 不止这里出问题
                        printInputTip(STU_ID, STU_name, STU_score);

                        // 询问用户是否保留此次数据
                        int userInput;
                        scanf("%d", &userInput);

                        if(userInput == 1) {
                            fseek(fp, 0, SEEK_END);
                            fprintf(fp, "[%d] - <%s> {%s} [%d]\n", i + DBSum + 1, STU_ID, STU_name, STU_score);

                            // 成功后输出提示并给循环计数器 +1
                            printInputSuccess();
                            i++;
                        } else {
                            STU_score = -1;
                        }
                    } while(i < studentSum);

                    // 录入结束的时候输出消息
                    printInputFinish();
                    fclose(fp);
                    fp = fopen(DBinput, "r+");
                } else if(editInput == 2) {
                    // 查找数据

                    // 第一步，获取这个数据库有多少东西
                    int DBSum;
                    DBSum = getFileLine(fp) - 2;

                    // 第二步，告诉用户要输入什么
                    int userInput;
                    printSearchTips(DBinput);
                    scanf("%d", &userInput);

                    // 第三步，根据用户输入来进行对应的操作
                    if(userInput == 1) {
                        // 变量 - 搜索输入
                        char searchInput[33];

                        // 第一步，提醒用户你要输入什么
                        printSearchInput(1);
                        scanf("%s", searchInput);

                        // 第二步，遍历所有信息并标记匹配项目
                        fseek(fp, 0, SEEK_SET);            // 移动指针到数据库的第一条内容
                        struct example temp;                // 作为临时存储的变量
                        int searchResultPos[DBSum];         // 结果位置标记。有结果则为 1
                        int searchResultSum = 0;            // 搜索结果数量存储
                        int loopCount = 0;                  // 循环计数器

                        // 通过这个循环来遍历所有的数据条目
                        while(fscanf(fp, "[%d] - <%s> - {%s} - [%d]\n", temp.DB_ID, temp.STU_ID, temp.STU_name, temp.STU_score) != EOF) {
                            // 如果这个数据条目和查询的条目重合则对条目进行标记
                            if(temp.STU_ID == searchInput) {
                                searchResultSum++;
                                searchResultPos[loopCount] = 1;
                            }
                            loopCount++;
                        }

                        // 第三步，输出粗略的结果
                        printSearchResult(searchResultSum);

                        // 第四步，如果查询数量不为 0 的话询问是否展示详细信息
                        // 如果只有一条信息则直接展示

                        fseek(fp, 0, SEEK_SET);            // 指针定位到数据库开头

                        if(searchResultSum == 1) {
                            for(int i = 0; i <= DBSum; i++) {
                                fscanf(fp, "[%d] - <%s> - {%s} - [%d]\n", temp.DB_ID, temp.STU_ID, temp.STU_name, temp.STU_score);
                                if(searchResultPos[i] == 1) {
                                    printSearchDetail(i + 1, searchResultSum, temp.DB_ID, temp.STU_ID, temp.STU_name, temp.STU_score);
                                }
                            }
                        } else if(searchResultSum > 1) {
                            int searchDetailInput;
                            scanf("%d", &searchDetailInput);

                            if(searchDetailInput == 1) {
                                for(int i = 0; i <= DBSum; i++) {
                                    fscanf(fp, "[%d] - <%s> - {%s} - [%d]\n", temp.DB_ID, temp.STU_ID, temp.STU_name, temp.STU_score);
                                    if(searchResultPos[i] == 1) {
                                        printSearchDetail(i + 1, searchResultSum, temp.DB_ID, temp.STU_ID, temp.STU_name, temp.STU_score);
                                    }
                                }
                            }
                        }

                        // 最后给个提示，修改数据请转到数据库编号查询
                        printSearchEnd();
                    } else if(userInput == 2) {
                        // 变量 - 搜索输入
                        char searchInput[65];

                        // 第一步，提醒用户你要输入什么
                        printSearchInput(2);
                        scanf("%s", searchInput);

                        // 第二步，遍历所有信息并标记匹配项目
                        fseek(fp, 0, SEEK_SET);            // 移动指针到数据库的第一条内容
                        struct example temp;                // 作为临时存储的变量
                        int searchResultPos[DBSum];         // 结果位置标记。有结果则为 1
                        int searchResultSum = 0;            // 搜索结果数量存储
                        int loopCount = 0;                  // 循环计数器

                        // 通过这个循环来遍历所有的数据条目
                        while(fscanf(fp, "[%d] - <%s> - {%s} - [%d]\n", temp.DB_ID, temp.STU_ID, temp.STU_name, temp.STU_score) != EOF) {
                            // 如果这个数据条目和查询的条目重合则对条目进行标记
                            if(temp.STU_name == searchInput) {
                                searchResultSum++;
                                searchResultPos[loopCount] = 1;
                            }
                            loopCount++;
                        }

                        // 第三步，输出粗略的结果
                        printSearchResult(searchResultSum);

                        // 第四步，如果查询数量不为 0 的话询问是否展示详细信息
                        // 如果只有一条信息则直接展示

                        fseek(fp, 0, SEEK_SET);            // 指针定位到数据库开头

                        if(searchResultSum == 1) {
                            for(int i = 0; i <= DBSum; i++) {
                                fscanf(fp, "[%d] - <%s> - {%s} - [%d]\n", temp.DB_ID, temp.STU_ID, temp.STU_name, temp.STU_score);
                                if(searchResultPos[i] == 1) {
                                    printSearchDetail(i + 1, searchResultSum, temp.DB_ID, temp.STU_ID, temp.STU_name, temp.STU_score);
                                }
                            }
                        } else if(searchResultSum > 1) {
                            int searchDetailInput;
                            scanf("%d", &searchDetailInput);

                            if(searchDetailInput == 1) {
                                for(int i = 0; i <= DBSum; i++) {
                                    fscanf(fp, "[%d] - <%s> - {%s} - [%d]\n", temp.DB_ID, temp.STU_ID, temp.STU_name, temp.STU_score);
                                    if(searchResultPos[i] == 1) {
                                        printSearchDetail(i + 1, searchResultSum, temp.DB_ID, temp.STU_ID, temp.STU_name, temp.STU_score);
                                    }
                                }
                            }
                        }

                        // 最后给个提示，修改数据请转到数据库编号查询
                        printSearchEnd();
                    } else if(userInput == 3) {
                        // 这里是通过数据库 ID 进行精准定位，可以确保数据库 ID 唯一
                        // 所以我们这里就只需要把指针归位
                        // 然后根据用户输入指定读取多少次就可以了

                        // 变量 - 搜索输入
                        int searchInput;

                        // 第一步，提醒用户你要输入什么
                        printSearchInput(3);
                        scanf("%d", &searchInput);

                        // 第二步，指针归位并转到指定的行
                        for(int i = 0; i < searchInput; i++) {
                            char buffer[256];
                            fgets(buffer, 256, fp);
                        }

                        // 第三步，读入并输出数据
                        struct example temp;
                        if(fscanf(fp, "[%d] - <%s> - {%s} - [%d]\n", temp.DB_ID, temp.STU_ID, temp.STU_name, temp.STU_score) != EOF) {
                            printSearchDetail(1, 1, temp.DB_ID, temp.STU_ID, temp.STU_name, temp.STU_score);

                            // 第四步，读入用户操作
                            int editEntryInput;
                            printEditEntry();
                            scanf("%d", &editEntryInput);

                            if(editEntryInput == 1) {
                                // 进入对指定项目的编辑
                                // 使用 do 循环达到每次操作完成后回到操作界面的能力

                                int DBEditInput = -1;
                                do {
                                    // 打印提示并获取用户输入
                                    printEditTips(DBinput);
                                    scanf("%d", &DBEditInput);

                                    if(DBEditInput == 1) {
                                        // 修改指定的内容

                                        // 输出修改提示（循环）
                                        int DBEditContentInput = -1;    // 用户输入
                                        int EditID = 0;                 // 修改学号的标识符
                                        int EditName = 0;               // 修改姓名的标识符
                                        int EditScore = 0;              // 修改成绩的标识符

                                        do {
                                            printEditContent(EditID, EditName, EditScore);

                                            scanf("%d", &DBEditContentInput);

                                            if (DBEditContentInput == 1) {
                                                toggle(EditID);
                                            } else if (DBEditContentInput == 2) {
                                                toggle(EditName);
                                            } else if (DBEditContentInput == 3) {
                                                toggle(EditScore);
                                            } else if (DBEditContentInput == 4) {
                                                // 进入编辑模式

                                                // 思路是把要修改的东西先放到 temp 里面
                                                // 然后在创建一个全新的 DBcache 文件（一开始创建文件保留的那个关键字）
                                                // 向 DBcache 里面写入其他不用修改的内容
                                                // 在写入时把修改的那一个插入进去
                                                // 就可以完成这个修改的操作

                                                // 首先我们创建一个文件
                                                FILE *DBcache;
                                                DBcache = fopen("DBcache", "w+");

                                                // 然后把原先文件的内容给加载到新的缓存文件内
                                                for(int i = 0; i < searchInput; i++) {
                                                    
                                                }
                                            }
                                        } while(DBEditContentInput != 0);
                                    } else if(DBEditInput == 2) {
                                        // 删除指定的内容
                                    } else if(DBEditInput == 3) {
                                        // 查看当前选中的学生信息
                                        printSearchDetail(1, 1, temp.DB_ID, temp.STU_ID, temp.STU_name, temp.STU_score);
                                    }
                                } while(DBEditInput != 0);
                            }
                        }
                    }
                } else if(editInput == 3) {
                    // 统计数据
                }
            } while (editInput != 0);
        }
    } while(introInput != 0);

    printOutro();
    return(0);
}