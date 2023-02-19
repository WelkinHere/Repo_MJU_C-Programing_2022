#include <stdio.h>
#include <windows.h>
#include <conio.h>

int main() {
    system("chcp 65001");

    int input_cache;        // 用户输入缓存

    int field_height = 36;  // 场景高度
    int field_weight = 25;  // 场景宽度

    int plane_start_x = 13; // 飞机起始位置（x）
    int plane_start_y = 34; // 飞机起始位置（y）

    int exitFlag = 0;       // 退出游戏标识符

    do {
        system("cls");

        printf("Space Ship Project\n\n");
        printf("[1] Start\n[2] How to Play\n[3] Credit\n[0] Exit\n\n");
        printf("Select an option to start: ");

        scanf("%c", &input_cache);

        switch (input_cache)
        {
            case 49:
                // 画图循环部分
                while (1) {
                    int plane_x = 13;
                    int plane_y = 34;

                    // 画图部分
                    system("cls");

                    // 画图水平坐标
                    for(int draw_height = 0; draw_height <= field_height + 1; draw_height++) {
                        // 打印第一行（边界顶部）
                        if(draw_height == 0) {
                            printf("┌");
                            for(int i = 0; i < field_weight; i++) {printf("──");}
                            printf("┐\n");
                        } else if(draw_height == field_height + 1) {
                            printf("└");
                            for(int i = 0; i < field_weight; i++) {printf("──");}
                            printf("┘\n");
                        } else {
                            printf("│");
                            for(int i = 0; i < field_weight; i++) {
                                if(draw_height == plane_y + 1 && i == plane_x) {
                                    printf("<>");
                                } else {
                                    printf("　");
                                }
                            }
                            printf("│\n");
                        }
                    }
                    printf("Press: %d\n", input_cache);
                    printf("Plane: (%d, %d)", plane_x, plane_y);

                    input_cache = getch();

                    // 按 ESC 退出
                    if(input_cache == 27) {break;}

                    // 移动
                    if(input_cache == 72 && plane_x >= 0)  {plane_x = plane_x - 1;}
                    if(input_cache == 80 && plane_x <= 35) {plane_x = plane_x + 1;}
                    if(input_cache == 75 && plane_y >= 0)  {plane_y = plane_y - 1;}
                    if(input_cache == 77 && plane_y <= 24) {plane_y = plane_y + 1;}
                }
                break;
            case 50:
                {system("cls");
                printf("<> - This is your [PLANE]\n");
                printf("╳ - This is your [ENEMY]\n");
                printf("Use \"←\" \"↑\" \"→\" \"↓\" to move your [PLANE].\n");
                printf("Use \"Z\" to [SHOOT] your [ENEMY].\n");
                Sleep(3000);
                break;}
            case 51:
                {system("cls");
                printf("Code By welkin.\n");
                printf("welkin's Github Profile: https://www.github.com/WelkinHere/ \n");
                Sleep(3000);
                break;}

            case 48:
                {system("cls");
                printf("Exiting.\n");
                exitFlag = 1;
                break;}
            
            default:
                {system("cls");
                printf("Invalid Input! Please try again!\n\n");
                break;}
        }
    } while(exitFlag == 0);
}