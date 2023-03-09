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

// 主函数
int main() {
    /*
     *  程序初始化
     */
     
    // 调整窗口大小
    system("mode con cols=60 lines=30");

    // 设置窗口标题
    system("title Bouncy Balls");

    // 设置窗口背景色
    system("color 06");

    // 设置窗口字体
    system("chcp 65001");
    system("mode con font=Fira Code");

    // 清屏
    system("cls");
    
    // 设置光标不可见
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};       // 将第二个数值设置为 0 即可隐藏
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);

    /*
     *  变量初始化
     */

    // 场景的大小
    int scene_width = 28;
    int scene_height = 17;

    // 第一个小球
    int ball1_x = 7;
    int ball1_y = 2;
    int ball1_vx = 1;
    int ball1_vy = 1;

    // 第二个小球
    int ball2_x = 5;
    int ball2_y = 12;
    int ball2_vx = 1;
    int ball2_vy = -1;

    // 第三个小球
    int ball3_x = 13;
    int ball3_y = 4;
    int ball3_vx = -1;
    int ball3_vy = 1;

    // 计时器
    int timer = -1;

    /*
     *  游戏循环
     */

    while(1) {
        /*
         *  游戏逻辑
         */

        // 第一个小球的碰撞逻辑
        if(ball1_x <= 1 || ball1_x >= scene_width - 2) {
            ball1_vx = -ball1_vx;
        }
        if(ball1_y <= 1 || ball1_y >= scene_height - 2) {
            ball1_vy = -ball1_vy;
        }

        // 第二个小球的碰撞逻辑
        if(ball2_x <= 1 || ball2_x >= scene_width - 2) {
            ball2_vx = -ball2_vx;
        }
        if(ball2_y <= 1 || ball2_y >= scene_height - 2) {
            ball2_vy = -ball2_vy;
        }

        // 第三个小球的碰撞逻辑
        if(ball3_x <= 1 || ball3_x >= scene_width - 2) {
            ball3_vx = -ball3_vx;
        }
        if(ball3_y <= 1 || ball3_y >= scene_height - 2) {
            ball3_vy = -ball3_vy;
        }
        
        if(timer == 20) {
            gotoXY(scene_width + 2, 1);
            printf("                               ");

            timer = -1;
        }

        if(timer != -1) {
            timer++;
        }

        // 第一个小球和第二个小球的碰撞逻辑
        if(ball1_x == ball2_x && ball1_y == ball2_y) {
            ball1_vx = -ball1_vx;
            ball1_vy = -ball1_vy;
            ball2_vx = -ball2_vx;
            ball2_vy = -ball2_vy;

            gotoXY(scene_width + 2, 1);
            printf("第一个球和第二个球产生了碰撞！");
            timer = 0;
        }

        // 第一个小球和第三个小球的碰撞逻辑
        if(ball1_x == ball3_x && ball1_y == ball3_y) {
            ball1_vx = -ball1_vx;
            ball1_vy = -ball1_vy;
            ball3_vx = -ball3_vx;
            ball3_vy = -ball3_vy;

            gotoXY(scene_width + 2, 1);
            printf("第一个球和第三个球产生了碰撞！");
            timer = 0;
        }

        // 第二个小球和第三个小球的碰撞逻辑
        if(ball2_x == ball3_x && ball2_y == ball3_y) {
            ball2_vx = -ball2_vx;
            ball2_vy = -ball2_vy;
            ball3_vx = -ball3_vx;
            ball3_vy = -ball3_vy;

            gotoXY(scene_width + 2, 1);
            printf("第二个球和第三个球产生了碰撞！");
            timer = 0;
        }

        // 小球的移动逻辑
        ball1_x += ball1_vx;
        ball1_y += ball1_vy;
        ball2_x += ball2_vx;
        ball2_y += ball2_vy;
        ball3_x += ball3_vx;
        ball3_y += ball3_vy;

        /*
         *  游戏绘制
         */

        // 绘制小球
        gotoXY(ball1_x, ball1_y);
        printf("●");
        gotoXY(ball2_x, ball2_y);
        printf("●");
        gotoXY(ball3_x, ball3_y);
        printf("●");

        // 清除残影
        gotoXY(ball1_x - ball1_vx, ball1_y - ball1_vy);
        printf(" ");
        gotoXY(ball2_x - ball2_vx, ball2_y - ball2_vy);
        printf(" ");
        gotoXY(ball3_x - ball3_vx, ball3_y - ball3_vy);
        printf(" ");

        // 绘制调试信息
        gotoXY(0, scene_height + 3);
        printf("Debug:");
        gotoXY(0, scene_height + 4);
        printf("ball1_x: %d, ball1_y: %d, ball1_vx: %d, ball1_vy: %d     ", ball1_x, ball1_y, ball1_vx, ball1_vy);
        gotoXY(0, scene_height + 5);
        printf("ball2_x: %d, ball2_y: %d, ball2_vx: %d, ball2_vy: %d     ", ball2_x, ball2_y, ball2_vx, ball2_vy);
        gotoXY(0, scene_height + 6);
        printf("ball3_x: %d, ball3_y: %d, ball3_vx: %d, ball3_vy: %d     ", ball3_x, ball3_y, ball3_vx, ball3_vy);
        gotoXY(0, scene_height + 7);
        printf("scene_width: %d, scene_height: %d     ", scene_width, scene_height);

        gotoXY(0, scene_height + 1);
        printf("Code by welkin(https://github.com/WelkinHere/).");

        // 绘制边框
        gotoXY(0, 0);
        for(int i = 0; i < scene_width; i++) {
            printf("█");
        }
        for(int i = 1; i < scene_height - 1; i++) {
            gotoXY(0, i);
            printf("█");
            gotoXY(scene_width - 1, i);
            printf("█");
        }
        gotoXY(0, scene_height - 1);
        for(int i = 0; i < scene_width; i++) {
            printf("█");
        }

        // 延时
        Sleep(50);
    }
}