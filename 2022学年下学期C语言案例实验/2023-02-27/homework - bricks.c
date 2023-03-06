/*
 *  一、反弹球消砖块
 *  目标：在界面上方增加三排砖块，能实现小球消砖块。
 */

#include <stdio.h>
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

// 主程序
int main() {

    /*
     *  程序初始化
     */

    // 调整窗口大小
    system("mode con cols=75 lines=35");

    // 设置窗口标题
    system("title Bricks");

    // 设置窗口字体颜色
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

    // 游戏相关变量

    // 游戏进行状态
    int gameState = 0;

    // 游戏场景

    // 游戏内场景大小
    int stageFieldX = 15, stageFieldY = 25;
    // 场景四边定义
    int stageEdgeLeft = 0, stageEdgeRight = stageFieldX + 1;
    int stageEdgeTop = 0, stageEdgeBottom = stageFieldY + 1;
    // 游戏内场景内容
    int stageContext[stageFieldX][stageFieldY] = {0};

    // 小球
    
    // 小球的位置
    int ballPosX, ballPosY;
    // 小球的速度
    int ballSpeedX = 1, ballSpeedY = 1;
    // 小球的生命值
    int ballHealth = 3;

    // 挡板

    // 挡板的位置
    int barPosX = 5, barPosY = 22;
    // 挡板的宽度
    int barWidth = 5;
    // 挡板的移动状态
    int barMoveState = 0;       // 1 = 向左，2 = 向右

    /*
     *  游戏场景初始化
     */

    for(int i = 1; i < 4; i++) {
        for(int j = 0; j < stageFieldX; j++) {
            stageContext[j][i] = 1;
        }
    }

    // 游戏主循环
    while(gameState == 0) {
        /*
         *  按键处理
         */
        if (kbhit()) {
            int key = getch();
            if (key == 224) {
                key = getch();
                if (key == 75) {
                    // 向左移动挡板
                    barMoveState = 1;
                } else if (key == 77) {
                    // 向右移动挡板
                    barMoveState = 2;
                }
            } else if (key == 27) {
                // 退出游戏
                gameState = 2;
            }
        } else {
            // 重置挡板状态
            barMoveState = 0;
        }

        /*
         *  游戏实现逻辑
         */

        // 挡板移动逻辑
        if(barMoveState == 1 && barPosX > stageEdgeLeft + 1) {
            barPosX--;
        } else if(barMoveState == 2 && barPosX < stageEdgeRight - barWidth - 1) {
            barPosX++;
        }

        // 小球的移动
        ballPosX += ballSpeedX;
        ballPosY += ballSpeedY;

        // 小球撞壁反弹逻辑
        if(ballPosX == stageEdgeLeft + 1 || ballPosX == stageEdgeRight - 1) {ballSpeedX = -ballSpeedX;}
        if(ballPosY == stageEdgeTop + 1) {ballSpeedY = -ballSpeedY;}
        
        // 小球触底重置逻辑 
        if(ballPosY == stageEdgeBottom - 1) {
            Sleep(1500);
            
            ballPosX = random(4, 6);
            ballPosY = random(3, 12);
            
            ballHealth--; 
        }
        
        // 小球挡板反弹逻辑
		if(ballPosX >= barPosX && ballPosX < barPosX + barWidth && ballPosY == barPosY - 1) {
			ballSpeedY = -ballSpeedY;
		}
		
		// 小球砖块反弹判定逻辑
		if(stageContext[barPosX - 1][barPosY] == 1 && ballSpeedX == -1) {stageContext[barPosX - 1][barPosY] = 0; ballSpeedX = -ballSpeedX;} 
		if(stageContext[barPosX + 1][barPosY] == 1 && ballSpeedX == 1) {stageContext[barPosX + 1][barPosY] = 0; ballSpeedX = -ballSpeedX;} 
		if(stageContext[barPosX][barPosY - 1] == 1 && ballSpeedY == -1) {stageContext[barPosX][barPosY - 1] = 0; ballSpeedY = -ballSpeedY;} 
		if(stageContext[barPosX][barPosY + 1] == 1 && ballSpeedY == 1) {stageContext[barPosX][barPosY + 1] = 0; ballSpeedY = -ballSpeedY;} 
        
        // 游戏结束逻辑
		if(ballHealth == 0) {gameState = 1;} 

        /*
         *  绘图
         */
         
        // 小球位置绘制
		gotoXY(ballPosX, ballPosY); printf(" ");
		gotoXY(ballPosX, ballPosY + 2); printf(" ");
		gotoXY(ballPosX + 1, ballPosY + 1); printf("◎");
		gotoXY(ballPosX + 2, ballPosY); printf(" ");
		gotoXY(ballPosX + 2, ballPosY + 2); printf(" ");

        // 砖块绘制
        for(int i = 0; i < stageFieldX; i++) {
            for(int j = 0; j < stageFieldY; j++) {
                gotoXY(i + 1, j + 1);
                if(stageContext[i][j] == 1) {printf("█");} else {printf(" ");}
            }
        }

        // 挡板位置绘制
        gotoXY(barPosX, barPosY + 1);
        printf(" ");
        for(int i = 0; i < barWidth; i++) {printf("▬");}
        printf(" ");
    }
}