#include <stdio.h>
#include <windows.h>
#include <conio.h>

int main() {
    system("chcp 65001");

    // 两个用于随机敌人位置的池子
    int enemy_random_x[15] = {15, 13, 9, 16, 12, 15, 18, 22, 9, 11, 17, 6, 12, 21, 3};
    int enemy_random_y[8]  = {3, 6, 8, 5, 7, 4, 11, 9};
    
    // 两个用于记录敌人位置的计数器
    int enemy_x_count = 0;
    int enemy_y_count = 0;

    int input_cache;        // 用户输入缓存

    int field_height = 37;  // 场景高度
    int field_weight = 27;  // 场景宽度

    int plane_x = 13;        // 飞船所在 x 轴
    int plane_y = 34;        // 飞船所在 y 轴

    int exitFlag = 0;       // 退出游戏标识符

    do {
        system("cls");

        printf("Space Ship Project\n\n");
        printf("[1] Start\n[2] How to Play\n[3] Credit\n[0] Exit\n\n");
        printf("Select an option to start: ");

        scanf("%d", &input_cache);

        switch (input_cache)
        {
            case 1:
                {// 这里是不希望把初始的位置弄乱，拉一个临时的值出来

                plane_x = 13;        // 飞船所在 x 轴
                plane_y = 34;        // 飞船所在 y 轴
                int plane_fireFlag = 0;             // 飞船发射标识符
                int player_score = 0;               // 玩家得分

                int enemy_alive = 1;// 敌人存活biao'ji
                int enemy_pos_x;    // 敌人所在 x 轴
                int enemy_pos_y;    // 敌人所在 y 轴

                int leaveFlag = 0;

                // 这里是画图部分，游戏的主体界面在这里绘制

                while(leaveFlag == 0) {
                    system("cls");
                    // 画图水平坐标
                    for(int draw_height = 0; draw_height <= field_height + 1; draw_height++) {
                        // 打印第一行（边界顶部）
                        if(draw_height == 0) {
                            // 顶部得分文字
                            printf("Score: %dpts\n", player_score);
                            // 上边框
                            printf("┌");
                            for(int i = 0; i < field_weight; i++) {printf("──");}
                            printf("┐\n");
                        } else if(draw_height == field_height + 1) {
                            // 下边框
                            printf("└");
                            for(int i = 0; i < field_weight; i++) {printf("──");}
                            printf("┘\n");
                            // 底部文字
                            printf("Press ESC to exit.\n");
                            printf("Press: %d, Plane: (%d,%d), Firing: %d.\n", input_cache, plane_x, plane_y, plane_fireFlag);
                        } else {
                            // 左边框
                            printf("│");
                            for(int i = 0; i < field_weight; i++) {
                                if(plane_fireFlag == 1 && i == plane_x && draw_height <= plane_y) {
                                    // 开火的激光位置
                                    printf("￤");
                                } else if(draw_height == enemy_pos_y + 1 && i == enemy_pos_x) {
                                    // 敌人所在位置
                                    printf("╳╳");
                                } else if(draw_height == plane_y + 1 && i == plane_x) {
                                    // 飞机位置
                                    printf("〇");
                                } else {
                                    // 空位
                                    printf("　");
                                }
                            }
                            // 右边框
                            printf("│\n");
                        }
                    }

                    // 按键获取 - 在按下 ESC 的时候退出画图循环
                    if(plane_fireFlag == 1) {
                        plane_fireFlag = 0;
                        Sleep(100);
                    } else {
                        input_cache = getch();
                        if(input_cache == 27) {leaveFlag = 1;}
                        else if(input_cache == 'w' && plane_y > 0) {plane_y += -1;}
                        else if(input_cache == 'a' && plane_x > 0) {plane_x += -1;}
                        else if(input_cache == 's' && plane_y < 36) {plane_y += 1;}
                        else if(input_cache == 'd' && plane_x < 26) {plane_x += 1;}
                        else if(input_cache == 13) {plane_fireFlag = 1;}
                    }
                }
                break;}
            case 2:
                {system("cls");
                printf("〇 - This is your [PLANE]\n");
                printf("╳╳ - This is your [ENEMY]\n");
                printf("Use \"←\" \"↑\" \"→\" \"↓\" to move your [PLANE].\n");
                printf("Use \"Z\" to [SHOOT] your [ENEMY].\n");
                Sleep(3000);
                break;}
            case 3:
                {system("cls");
                printf("Code By welkin.\n");
                printf("welkin's Github Profile: https://www.github.com/WelkinHere/ \n");
                Sleep(3000);
                break;}

            case 0:
                {system("cls");
                printf("Exiting.\n");
                exitFlag = 1;
                break;}
            
            default:
                {system("cls");
                printf("Invalid Input! Please try again!\n\n");
                Sleep(1000);
                break;}
        }
    } while(exitFlag == 0);
}