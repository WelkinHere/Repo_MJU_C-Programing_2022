#include <stdio.h>
#include <windows.h>
#include <conio.h>

int main() {
    int input_cache;                    // 输入缓存

    int field_height = 15;              // 场景高度
    int field_weight = 10;              // 场景宽度

    int ball_start_height = 1;          // 球体起始位置 - x
    int ball_start_weight = 0;          // 球体起始位置 - y

    int ball_movement_x = 1;            // 球体水平动量
    int ball_movement_y = 1;            // 球体垂直动量

    int sleepTime = 100;                // 刷新时间间隔（单位为毫秒）

    int exitFlag = 0;                   // 退出程序标识符

    system("chcp 65001");
    do {
        system("cls");

        printf("Bounce Ball Project\n\n");
        printf("[1] Start\n");
        printf("[2] Setting\n");
        printf("[3] Credit\n");
        printf("[0] Exit\n\n");
        printf("[Details]\n");
        printf("Field: %dx%d\n", field_height, field_weight);
        printf("Ball Position: (%d, %d)\n", ball_start_height, ball_start_weight);
        printf("Ball Movement: %d(x), %d(y)\n", ball_movement_x, ball_movement_y);
        printf("Refresh Delay: %dms\n\n", sleepTime);
        printf("Select an option to start: ");

        scanf("%d", &input_cache);

        switch (input_cache) {
        case 1:
            {
            // 创建新的小球数据 - 用于画图使用
            // 其实只是不想修改起始值
            int ball_height = ball_start_height;        // 画图用小球水平位置
            int ball_weight = ball_start_weight;        // 画图用小球垂直位置
            int ball_move_x = 1;                        // 画图用小球水平动量方向
            int ball_move_y = -1;                       // 画图用小球垂直动量方向

            // 画图循环部分
            while (1) {
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
                        printf("Press ESC to exit.\nPress \"+\" to increase the speed,\nPress \"-\" to decrease the speed.\n");
                    } else {
                        printf("│");
                        for(int i = 0; i < field_weight; i++) {
                            if(draw_height == ball_height + 1 && i == ball_weight) {
                                printf("〇");
                            } else {
                                printf("　");
                            }
                        }
                        printf("│\n");
                    }
                }

                // 绘制完成后对小球做处理，更新小球位置

                // 水平方向检测边界、转向和移动
                for(int i = 0; i < ball_movement_x; i++) {
                    if(ball_height == 0 && ball_move_x < 0) {
                        ball_move_x = -ball_move_x;
                        printf("\a");
                    } else if (ball_height == field_height - 1 && ball_move_x > 0) {
                        ball_move_x = -ball_move_x;
                        printf("\a");
                    }
                    9
                }

                // 垂直方向检测边界、转向和移动
                for(int i = 0; i < ball_movement_y; i++) {
                    if(ball_weight == 0 && ball_move_y < 0) {
                        ball_move_y = -ball_move_y;
                        printf("\a");
                    } else if (ball_weight == field_weight - 1 && ball_move_y > 0) {
                        ball_move_y = -ball_move_y;
                        printf("\a");
                    }
                    ball_weight += ball_move_y;
                }

                // 按键获取 - 在按下 ESC 的时候退出画图循环
                if(kbhit()){
                    input_cache = getch();
                    if(input_cache == 27) {break;}
                    if(input_cache == 95 || input_cache == 45 && sleepTime < 2000) {sleepTime += 10;}
                    if(input_cache == 43 || input_cache == 61 && sleepTime > 10) {sleepTime -= 10;}
                }

                // 画图延迟
                Sleep(sleepTime);
            }
            break;}
        case 2:
            {int leaveFlag = 0;
            do {
                system("cls");
                printf("Bounce Ball Project\n\n");
                printf("[Settings]\n");
                printf("[1] Field\n[2] Ball Start Position\n[3] Ball Move Speed\n[4] Refresh Delay\n[0] Exit Settings\n\n");
                printf("Select an option to start: ");

                scanf("%d", &input_cache);

                    switch (input_cache) {
                    case 1:
                        printf("Editing Field Height.\n");
                        printf("Field Height is 15 set in default.\n");
                        printf("Field Height now is %d.\n", field_height);
                        printf("Please input the value: ");
                        scanf("%d", &field_height);
                        printf("Editing Field Weight.\n");
                        printf("Field Weight is 10 set in default.\n");
                        printf("Field Weight now is %d.\n", field_weight);
                        printf("Please input the value: ");
                        scanf("%d", &field_weight);
                        break;
                    case 2:
                        printf("Editing Ball Start Position (x).\n");
                        printf("Ball Start Position (x) is 1 set in default.\n");
                        printf("Ball Start Position (x) now is %d.\n", ball_start_height);
                        printf("Please input the value: ");
                        scanf("%d", &ball_start_height);
                        printf("Editing Ball Start Position (y).\n");
                        printf("Ball Start Position (y) is 0 set in default.\n");
                        printf("Ball Start Position (y) now is %d.\n", ball_start_weight);
                        printf("Please input the value: ");
                        scanf("%d", &ball_start_weight);
                        break;
                    case 3:
                        printf("Editing Ball Moving Speed (x).\n");
                        printf("Ball Moving Speed (x) is 1 set in default.\n");
                        printf("Ball Moving Speed (x) now is %d.\n", ball_movement_x);
                        printf("Please input the value: ");
                        scanf("%d", &ball_movement_x);
                        printf("Editing Ball Moving Speed (y).\n");
                        printf("Ball Moving Speed (y) is 1 set in default.\n");
                        printf("Ball Moving Speed (y) now is %d.\n", ball_movement_y);
                        printf("Please input the value: ");
                        scanf("%d", &ball_movement_y);
                        break;
                    case 4:
                        printf("Editing Refresh Delay.\n");
                        printf("Refresh Delay is 200 set in default.\n");
                        printf("Refresh Delay now is %d.\n", sleepTime);
                        printf("Please input the value: ");
                        scanf("%d", &sleepTime);
                        break;
                    
                    case 0:
                        system("cls");
                        printf("Exiting Settings.\n");
                        leaveFlag = 1;
                        break;
                
                    default:
                        system("cls");
                        printf("Invalid Input! Please try again!\n\n");
                        break;
                    }
            } while(leaveFlag == 0); }
            break;
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
            break;}
        }
    } while(exitFlag == 0);
}