#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

// 随机数
int random(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// 移动光标到指定位置
int gotoXY(int x, int y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    return 0;
}

int main() {

    /*
     *  程序初始化
     */

    // 调整窗口大小
    system("mode con cols=75 lines=35");

    // 设置窗口标题
    system("title Bricks");

    // 设置窗口背景色
    system("color 0a");

    // 设置窗口字体
    system("chcp 65001");
    system("mode con font=Lucida Console");

    // 清屏
    system("cls");

    // 设置光标不可见
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};       // 将第二个数值设置为 0 即可隐藏
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);

    /*
     *  变量初始化
     */

    // 砖块的位置
    int brick_x = 15;
    int brick_y = 7;

    // 球的位置
    int ball_x = 15;
    int ball_y = 3;

    // 球的速度
    int ball_vx = 1;
    int ball_vy = 1;

    // 球的分数
    int ball_score = 0;

    // 球的生命
    int ball_life = 5;

    // 游戏区域的大小
    int game_width = 30;
    int game_height = 30;

    // 游戏区域的边界
    int game_left = 0;
    int game_right = game_width - 1;
    int game_top = 0;
    int game_bottom = game_height - 1;

    // 游戏的状态 0: 运行 1: 结束
    int game_status = 0;

    // 挡板的位置
    int paddle_x = 9;
    int paddle_y = 25;

    // 挡板的大小
    int paddle_width = 9;

    // 挡板的移动速度
    int paddle_speed = 1;

    // 挡板的状态
    int paddle_status = 0;

    /*
     *  游戏主循环
     */
    
    while(game_status == 0) {

        /*
         *  游戏控制
         */

        // 按键检测
        if (kbhit()) {
            int key = getch();
            if (key == 224) {
                key = getch();
                if (key == 75) {
                    paddle_status = 1;
                } else if (key == 77) {
                    paddle_status = 2;
                }
            } else if (key == 27) {
                game_status = 2;
            }
        } else {
            paddle_status = 0;
        }

        /*
         *  游戏逻辑
         */

        // 挡板的移动
        if (paddle_status == 1) {
            paddle_x -= paddle_speed;
        } else if (paddle_status == 2) {
            paddle_x += paddle_speed;
        }

        // 挡板的边界检测
        if (paddle_x < game_left + 1) {
            paddle_x = game_left + 1;
        } else if (paddle_x + paddle_width > game_right) {
            paddle_x = game_right - paddle_width;
        }

        // 球的移动
        ball_x += ball_vx;
        ball_y += ball_vy;
        
        // 球的挡板检测
        if (ball_x >= paddle_x && ball_x < paddle_x + paddle_width && ball_y == paddle_y - 1) {
            ball_vy = -ball_vy;
        }

        // 球的边界检测
        if (ball_x < game_left + 2) {
            ball_vx = -ball_vx;
        } else if (ball_x > game_right - 2) {
            ball_vx = -ball_vx;
        }

        if (ball_y < game_top + 2) {
            ball_vy = -ball_vy;
        } else if (ball_y > game_bottom - 2) {
            ball_vy = -ball_vy;

            for (int i = ball_x - 1; i <= ball_x + 1; i++) {
                for (int j = ball_y - 1; j <= ball_y + 1; j++) {
                    gotoXY(i, j);
                    printf(" ");
                }
            }

            ball_x = random(game_left + 4, game_right - 4);
            ball_y = 3;

            ball_life--;
        }

        // 球的砖块检测
        if (ball_x == brick_x && ball_y == brick_y) {
            ball_vx = -ball_vx;
            ball_vy = -ball_vy;

            brick_x = random(game_left + 4, game_right - 4);
            brick_y = random(game_top + 4, game_bottom - 15);

            ball_score++;
        }

        // 游戏结束检测
        if (ball_life == 0) {
            game_status = 1;
        }

        /*
         *  游戏绘制
         */
        
        // 绘制游戏区域
        gotoXY(game_left, game_top);
        for (int i = game_left; i <= game_right; i++) {
            printf("█");
        }
        gotoXY(game_left, game_top);
        for (int i = game_top; i <= game_bottom; i++) {
            gotoXY(game_left, i);
            printf("█");
            gotoXY(game_right, i);
            printf("█");
        }
        gotoXY(game_left, game_bottom);
        for (int i = game_left; i <= game_right; i++) {
            printf("█");
        }

        // 绘制球
        for (int i = ball_x - 1; i <= ball_x + 1; i++) {
            for (int j = ball_y - 1; j <= ball_y + 1; j++) {
                gotoXY(i, j);
                if (i == brick_x && j == brick_y) {
                    printf("■");
                } else if (i < game_left + 1) {
                    printf("█");
                } else if (i > game_right - 1) {
                    printf("█");
                } else if(j < game_top + 1) {
                    printf("█");
                } else if(j > game_bottom - 1) {
                    printf("█");
                } else if(i == ball_x && j == ball_y) {
                    printf("◎");
                } else {
                    printf(" ");
                }
            }
        }

        // 绘制挡板
        gotoXY(paddle_x - 1, paddle_y);
        printf(" ");
        for (int i = 0; i < paddle_width; i++) {
            printf("▬");
        }
        printf(" ");

        // 绘制砖块
        gotoXY(brick_x, brick_y);
        printf("■");

        // 绘制分数
        gotoXY(game_right + 5, game_top);
        printf("分数: %d", ball_score);

        // 绘制生命
        gotoXY(game_right + 5, game_top + 1);
        printf("生命: %d", ball_life);

        // 绘制提示
        gotoXY(game_right + 5, game_top + 3);
        printf("操作说明：");
        gotoXY(game_right + 5, game_top + 4);
        printf("←: 左移");
        gotoXY(game_right + 5, game_top + 5);
        printf("→: 右移");
        gotoXY(game_right + 5, game_top + 6);
        printf("Esc: 退出");

        // 绘制调试信息
        gotoXY(game_right + 5, game_top + 8);
        printf("Debug:");
        gotoXY(game_right + 5, game_top + 9);
        printf("球体位置：(%d, %d)  ", ball_x, ball_y);
        gotoXY(game_right + 5, game_top + 10);
        printf("挡板位置：(%d, %d)  ", paddle_x, paddle_y);
        gotoXY(game_right + 5, game_top + 11);
        printf("砖块位置：(%d, %d)  ", brick_x, brick_y);
        gotoXY(game_right + 5, game_top + 12);
        printf("游戏状态：%d", game_status);

        gotoXY(game_right + 5, game_top + 14);
        printf("Code by welkin.");
        gotoXY(game_right + 5, game_top + 15);
        printf("https://github.com/WelkinHere/");

        // 绘制游戏结束
        if (game_status == 1) {
            gotoXY(game_right / 2 - 8, game_bottom / 2);
            printf("游戏结束--生命耗尽");
            Sleep(3000);
        } else if (game_status == 2) {
            gotoXY(game_right / 2 - 8, game_bottom / 2);
            printf("游戏结束--按键退出");
            Sleep(3000);
        }

        Sleep(50);
    }
}