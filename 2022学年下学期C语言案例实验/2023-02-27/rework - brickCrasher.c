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
        system("mode con cols=75 lines=45");
    
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
    
        // 场景大小
        int scene_width = 30;
        int scene_height = 25;

        // 砖块的位置
        int brick_map[scene_height][scene_width];

        // 球的位置
        int ball_x = 15;
        int ball_y = 6;

        // 球的速度
        int ball_vx = 1;
        int ball_vy = 1;

        // 挡板的位置
        int paddle_x = 15;
        int paddle_y = scene_height - 2;

        // 挡板的长度
        int paddle_width = 7;

        // 玩家的生命值
        int player_life = 3;

        // 玩家的分数
        int player_score = 0;

        // 玩家的等级
        int player_level = 1;

        // 延迟
        int delay = 100;

        // 游戏是否结束
        int game_over = 0;

        // 初始化砖块
        for(int i = 0; i < scene_height; i++) {
            for(int j = 0; j < scene_width; j++) {
                if(i > 1 && i <= 4 && j > 0 && j < scene_width - 1) {
                    brick_map[i][j] = 1;
                } else {
                    brick_map[i][j] = 0;
                }   
            }
        }
        
        // 绘制砖块
        for(int i = 0; i < scene_height; i++) {
            for(int j = 0; j < scene_width; j++) {
                if(brick_map[i][j] == 1) {
                    gotoXY(j, i);
                    printf("■");
                }
            }
        }

        /*
         *  游戏主循环
         */
        while(game_over == 0) {
            /*
             *  输入处理
             */
            if(kbhit()) {
                char key = getch();
                if(key == 'a' && paddle_x > 1) {
                    paddle_x--;
                }
                if(key == 'd' && paddle_x + paddle_width < scene_width - 1) {
                    paddle_x++;
                }
            }

            /*
             *  场景绘制
             */

            // 绘制小球
            gotoXY(ball_x, ball_y);
            printf("●");

            // 消除轨迹
            gotoXY(ball_x - ball_vx, ball_y - ball_vy);
            printf(" ");

            // 绘制挡板
            gotoXY(paddle_x - 1, paddle_y);
            printf(" ");
            for(int i = 0; i < paddle_width; i++) {
                printf("▬");
            }
            printf(" ");

            // 绘制边界
            for(int i = 0; i < scene_width; i++) {
                gotoXY(i, 0);
                printf("█");
                gotoXY(i, scene_height - 1);
                printf("█");
            }
            for(int i = 0; i < scene_height; i++) {
                gotoXY(0, i);
                printf("█");
                gotoXY(scene_width - 1, i);
                printf("█");
            }

            // 绘制信息
            gotoXY(scene_width + 2, 2);
            printf("剩余生命： %d", player_life);
            gotoXY(scene_width + 2, 3);
            printf("得分： %d", player_score);
            gotoXY(scene_width + 2, 4);
            printf("等级： %d", player_level);

            // 绘制调试信息
            gotoXY(scene_width + 2, 6);
            printf("ball_x: %d, ball_y: %d", ball_x, ball_y);
            gotoXY(scene_width + 2, 7);
            printf("ball_vx: %d, ball_vy: %d", ball_vx, ball_vy);
            gotoXY(scene_width + 2, 8);
            printf("paddle_x: %d, paddle_y: %d", paddle_x, paddle_y);
            gotoXY(scene_width + 2, 9);
            printf("paddle_width: %d", paddle_width);
            gotoXY(scene_width + 2, 10);
            printf("delay: %d", delay);

            // 绘制游戏操作提示
            gotoXY(scene_width + 2, 12);
            printf("按 A 键向左移动");
            gotoXY(scene_width + 2, 13);
            printf("按 D 键向右移动");

            /*
             *  逻辑处理
             */

            // 移动小球
            ball_x += ball_vx;
            ball_y += ball_vy;

            // 小球碰撞检测
            if(ball_x <= 1 || ball_x >= scene_width - 2) {
                gotoXY(ball_x - ball_vx, ball_y - ball_vy);
                printf(" ");
                ball_vx = -ball_vx;
            }
            if(ball_y <= 2) {
                gotoXY(ball_x - ball_vx, ball_y - ball_vy);
                printf(" ");
                ball_vy = -ball_vy;
            }
            if(ball_y >= scene_height - 2) {
                gotoXY(ball_x - ball_vx, ball_y - ball_vy);
                printf(" ");

                player_life--;

                ball_x = 15;
                ball_y = 6;
                ball_vx = 1;
                ball_vy = 1;

                delay = 100;

                if(player_life == 0) {
                    game_over = 1;
                }
            }

            // 小球与挡板的碰撞检测
            if(ball_y == paddle_y - 1) {
                if(ball_x >= paddle_x && ball_x <= paddle_x + paddle_width) {
                    gotoXY(ball_x - ball_vx, ball_y - ball_vy);
                    printf(" ");
                    ball_vy = -ball_vy;
                }
            }

            // 小球与砖块的碰撞检测
            for(int i = 0; i < scene_height; i++) {
                for(int j = 0; j < scene_width; j++) {
                    if(brick_map[i][j] == 1) {
                        if(ball_y == i + 1 && ball_x == j) {
                            gotoXY(ball_x - ball_vx, ball_y - ball_vy);
                            printf(" ");
                            ball_vy = -ball_vy;
                            brick_map[i][j] = 0;
                            player_score++;
                        }
                        if(ball_y == i - 1 && ball_x == j) {
                            gotoXY(ball_x - ball_vx, ball_y - ball_vy);
                            printf(" ");
                            ball_vy = -ball_vy;
                            brick_map[i][j] = 0;
                            player_score++;
                        }
                        if(ball_y == i && ball_x == j + 1) {
                            gotoXY(ball_x - ball_vx, ball_y - ball_vy);
                            printf(" ");
                            ball_vx = -ball_vx;
                            brick_map[i][j] = 0;
                            player_score++;
                        }
                        if(ball_y == i && ball_x == j - 1) {
                            gotoXY(ball_x - ball_vx, ball_y - ball_vy);
                            printf(" ");
                            ball_vx = -ball_vx;
                            brick_map[i][j] = 0;
                            player_score++;
                        }
                    }
                }
            }

            // 等级提升
            if(player_score == 10) {
                player_level = 2;
                delay = 95;
            }
            if(player_score == 20) {
                player_level = 3;
                delay = 90;
            }
            if(player_score == 30) {
                player_level = 4;
                delay = 85;
            }
            if(player_score == 40) {
                player_level = 5;
                delay = 80;
            }
            if(player_score == 50) {
                player_level = 6;
                delay = 75;
            }
            if(player_score == 60) {
                player_level = 7;
                delay = 70;
            }
            if(player_score == 70) {
                player_level = 8;
                delay = 65;
            }
            if(player_score == 80) {
                player_level = 9;
                delay = 60;
            }
            if(player_score == 90) {
                player_level = 10;
                delay = 55;
            }

            // 游戏胜利
            if(player_score == 100) {
                gotoXY(scene_width / 2 - 4, scene_height / 2);
                printf("游戏胜利");
                Sleep(2000);

                game_over = 1;
                break;
            }

            // 游戏结束
            if(game_over == 1) {
                gotoXY(scene_width / 2 - 4, scene_height / 2);
                printf("游戏结束");
                Sleep(2000);
            }

            // 延时
            Sleep(delay);
        }
}