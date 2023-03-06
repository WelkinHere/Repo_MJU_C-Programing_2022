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
     * 程序初始化
     */

    // 调整窗口大小
    system("mode con cols=70 lines=35");

    // 设置窗口标题
    system("title Space Invader");

    // 设置窗口背景色
    system("color 0b");

    // 设置窗口字体
    system("chcp 65001");
    system("mode con font=Lucida Console");

    // 清屏
    system("cls");

    // 设置光标不可见
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};       // 将第二个数值设置为 0 即可隐藏
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);

    /*
     * 变量初始化
     */

    // 场景的大小
    int scene_width = 30;
    int scene_height = 30;

    // 玩家的位置
    int player_x = scene_width / 2;
    int player_y = scene_height - 2;

    // 玩家的移动状态
    int player_move_state = 0;

    // 玩家的速度
    int player_vx = 0;
    int player_vy = 0;

    // 玩家的分数
    int player_score = 0;

    // 玩家的生命值
    int player_life = 3;

    // 敌人状态计时器
    int enemy_state_timer = 0;

    // 敌人的移动状态
    int enemy_move_state = 0;

    // 敌人的位置
    int enemy_x = 35;
    int enemy_y = 3;

    // 敌人的速度
    int enemy_vx = 0;
    int enemy_vy = 1;

    // 子弹的位置
    int bullet_x = 0;
    int bullet_y = 0;

    // 子弹的速度
    int bullet_vy = -1;

    // 子弹的状态
    int bullet_state = 0;

    // 游戏状态
    int game_state = 0;

    /*
     * 游戏循环
     */

    while(game_state == 0) {
        /*
         * 事件处理
         */

        // 处理键盘事件
        if(_kbhit()) {
            // 获取按键
            char key = _getch();

            // 玩家移动回应
            switch(key) {
                case 'a':
                    player_move_state = 1;
                    break;
                case 'd':
                    player_move_state = 2;
                    break;
                case 'w':
                    player_move_state = 3;
                    break;
                case 's':
                    player_move_state = 4;
                    break;
                case ' ':
                    if(bullet_state == 0) {
                        bullet_x = player_x;
                        bullet_y = player_y - 1;
                        bullet_state = 1;
                    }
                    break;
                case 'q':
                    game_state = 2;
                    break;
            }
        } else {
            player_move_state = 0;
        }

        /*
         * 逻辑处理
         */

        // 玩家的移动
        switch(player_move_state) {
            case 1:
                player_vx = -1;
                player_vy = 0;
                break;
            case 2:
                player_vx = 1;
                player_vy = 0;
                break;
            case 3:
                player_vx = 0;
                player_vy = -1;
                break;
            case 4:
                player_vx = 0;
                player_vy = 1;
                break;
            default:
                player_vx = 0;
                player_vy = 0;
                break;
        }
        
        // 敌人的移动
        enemy_state_timer++;
        if(enemy_state_timer == 10 || enemy_state_timer == 20 || enemy_state_timer == 30 || enemy_state_timer == 40) {
            enemy_move_state = 4;
        } else if(enemy_state_timer == 50) {
            enemy_state_timer = 0;
            enemy_move_state = random(1, 4);
        }

        switch(enemy_move_state) {
            case 1:
                enemy_vx = -1;
                enemy_vy = 0;
                enemy_move_state = 0;
                break;
            case 2:
                enemy_vx = 1;
                enemy_vy = 0;
                enemy_move_state = 0;
                break;
            case 3:
                enemy_vx = 0;
                enemy_vy = 1;
                enemy_move_state = 0;
                break;
            case 4:
                enemy_vx = 0;
                enemy_vy = 1;
                enemy_move_state = 0;
                break;
            default:
                enemy_vx = 0;
                enemy_vy = 0;
                break;
        }

        // 子弹的移动
        if(bullet_state == 1) {
            bullet_y += bullet_vy;
            if(bullet_y == 0) {
                bullet_state = 0;
                gotoXY(bullet_x, bullet_y + 1);
                printf(" ");
            }
        }

        // 玩家的移动
        player_x += player_vx;
        player_y += player_vy;

        // 敌人的移动
        enemy_x += enemy_vx;
        enemy_y += enemy_vy;

        // 玩家的边界检测
        if(player_x < 1) {
            player_x = 1;
        }
        if(player_x > scene_width - 1) {
            player_x = scene_width - 1;
        }
        if(player_y < 1) {
            player_y = 1;
        }
        if(player_y > scene_height - 1) {
            player_y = scene_height - 1;
        }
        
        // 敌人的边界检测
        if(enemy_x < 1) {
            enemy_x = 1;
        }
        if(enemy_x > scene_width - 1) {
            enemy_x = scene_width - 1;
        }
        if(enemy_y < 1) {
            enemy_y = 1;
        }
        if(enemy_y > scene_height - 1) {
            enemy_y = scene_height - 1;
        }

        // 游戏结束检测
        if(player_life == 0) {
            game_state = 1;
        }
        
        // 延迟
        Sleep(5);

        /*
         * 渲染
         */

        // 场景的渲染
        for(int i = 0; i < scene_width; i++) {
            gotoXY(i, 0);
            printf("█");
        }
        for(int i = 0; i < scene_height; i++) {
            gotoXY(0, i);
            printf("█");
        }
        for(int i = 0; i < scene_height; i++) {
            gotoXY(scene_width, i);
            printf("█");
        }
        for(int i = 0; i < scene_width + 1; i++) {
            gotoXY(i, scene_height);
            printf("█");
        }

        // 分数的渲染
        gotoXY(scene_width + 3, 2); printf("分数：%d", player_score);

        // 生命值的渲染
        gotoXY(scene_width + 3, 3); printf("生命值：%d", player_life);

        // 按键提示的渲染
        gotoXY(scene_width + 3, 5); printf("按键提示：");
        gotoXY(scene_width + 3, 6); printf("W：上");
        gotoXY(scene_width + 3, 7); printf("S：下");
        gotoXY(scene_width + 3, 8); printf("A：左");
        gotoXY(scene_width + 3, 9); printf("D：右");
        gotoXY(scene_width + 3, 10); printf("空格：射击");
        gotoXY(scene_width + 3, 11); printf("Q：退出");

        // 调试信息的渲染
        gotoXY(scene_width + 3, 13); printf("调试信息：");
        gotoXY(scene_width + 3, 14); printf("玩家坐标：(%d, %d)   ", player_x, player_y);
        gotoXY(scene_width + 3, 15); printf("敌人坐标：(%d, %d)   ", enemy_x, enemy_y);
        gotoXY(scene_width + 3, 16); printf("子弹坐标：(%d, %d)   ", bullet_x, bullet_y);
        gotoXY(scene_width + 3, 17); printf("子弹状态：%d", bullet_state);
        gotoXY(scene_width + 3, 18); printf("敌人状态：%d", enemy_move_state);
        gotoXY(scene_width + 3, 19); printf("敌人状态计时：%d / 250ms   ", enemy_state_timer * 5);

        // 其他信息的渲染
        gotoXY(scene_width + 3, 21); printf("Code by welkin.");
        gotoXY(scene_width + 3, 21); printf("https://github.com/WelkinHere/");

        // 敌人的渲染
        gotoXY(enemy_x, enemy_y); printf("●");
        gotoXY(enemy_x - 1, enemy_y); if(enemy_x - 1 != 0) {printf(" ");}
        gotoXY(enemy_x + 1, enemy_y); if(enemy_x + 1 != scene_width) {printf(" ");}
        gotoXY(enemy_x, enemy_y - 1); if(enemy_y - 1 != 0) {printf(" ");}
        gotoXY(enemy_x, enemy_y + 1); if(enemy_y + 1 != scene_height) {printf(" ");}

        // 玩家的渲染
        gotoXY(player_x, player_y); printf("◎");
        gotoXY(player_x - 1, player_y); if(player_x - 1 != 0) {printf(" ");}
        gotoXY(player_x + 1, player_y); if(player_x + 1 != scene_width) {printf(" ");}
        gotoXY(player_x, player_y - 1); if(player_y - 1 != 0) {printf(" ");}
        gotoXY(player_x, player_y + 1); if(player_y + 1 != scene_height) {printf(" ");}

        // 子弹的渲染
        if(bullet_state == 1) {
            gotoXY(bullet_x, bullet_y); printf("△");
            gotoXY(bullet_x, bullet_y + 1); printf(" ");
        }

        // 子弹与敌人的碰撞检测
        if(bullet_state == 1 && bullet_x == enemy_x && bullet_y == enemy_y) {
            bullet_state = 0;

            enemy_x = random(1, scene_width - 1);
            enemy_y = random(1, scene_height - 15);

            gotoXY(bullet_x, bullet_y);
            printf(" ");

            player_score++;
        }

        // 玩家与敌人的碰撞检测
        if(player_x == enemy_x && player_y == enemy_y) {
            Sleep(1000);

            player_life--;

            enemy_x = random(1, scene_width - 1);
            enemy_y = random(1, scene_height - 15);

            gotoXY(player_x, player_y);
            printf(" ");

            player_x = scene_width / 2;
            player_y = scene_height - 2;
        }

        // 敌人与下边界的碰撞检测
        if(enemy_y == scene_height - 1) {
            Sleep(1000);

            gotoXY(enemy_x, enemy_y);
            printf(" ");

            enemy_x = random(1, scene_width - 1);
            enemy_y = random(1, scene_height - 15);

            player_life--;
        }
    }

    // 绘制游戏结束
    if (game_state == 1) {
        gotoXY(scene_width / 2 - 8, scene_height / 2);
        printf("游戏结束--生命耗尽");
        Sleep(3000);
    } else if (game_state == 2) {
        gotoXY(scene_width / 2 - 8, scene_height / 2);
        printf("游戏结束--按键退出");
        Sleep(3000);
    }

}