#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// 全局变量
int high,width; // 游戏画面大小
int ball_x,ball_y; // 小球的坐标
int ball_vx,ball_vy; // 小球的速度
int position_x,position_y; // 挡板中心坐标
int radius; //挡板的半径大小
int left,right; //挡板左右边界
int block_x,block_y; //砖块位置

void gotoxy(int x,int y) //光标移动到(x,y)位置
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

void HideCursor() // 用于隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};  // 第二个值为0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void startup()  // 数据初始化
{
	HideCursor();
	
	high = 13;   //画布大小初始化
	width = 20;
	
	ball_x = 0;  //小球位置初始化
	ball_y = width/2;
	
	ball_vx = 1;  //小球速度初始化
	ball_vy = 1;
	
	position_x = high; //挡板位置初始化
	position_y = width/2;
	radius = 5;
	left = position_y - radius;
	right = position_y + radius;
	
	block_x = 0;   //方块位置初始化
	block_y = 4;

}

void show()  // 显示画面
{
	gotoxy(0,0);    // 光标移动到原点位置，以下重画清屏	
	int i,j;
	for (i=0;i<=high+1;i++)
	{
		for (j=0;j<=width;j++)
		{
			if ((i== ball_x) && (j== ball_y))
				printf("0");  //   输出小球
			else if (j==width)
				printf("|");  //   输出右边框
			else if (i==high+1)
				printf("-");  //   输出下边框
			else if ((i==high)&&(j>left)&&(j<right))
				printf("*");
			else if ((i==block_x)&&(j==block_y))  //输出砖块
				printf("C");
			else
				printf(" ");  //   输出空格
		}
		printf("\n");
	}
}	

void updateWithoutInput()  // 与用户输入无关的更新
{
	if (ball_x == high-1)
	{
		if((ball_y>=left)&&(ball_y<=right))  //被挡板挡住
		{
			printf("\a");
		}
		else
		{
			printf("游戏失败\n");
			system("pause");
			exit(0);
		}
	}	
	//小球击中方块
	if((ball_x==block_x)&&(ball_y==block_y))
		block_y = rand() % width;	
	// 根据速度更新小球的位置
	ball_x = ball_x + ball_vx;
	ball_y = ball_y + ball_vy;
	
	// 碰到边界后，改变速度的方向，实现反弹
	if ((ball_x==0)||(ball_x==high-1))
		ball_vx = -ball_vx;
	if ((ball_y==0)||(ball_y==width-1))
		ball_vy = -ball_vy;		
	
	Sleep(80);
	
}

void updateWithInput()  // 与用户输入有关的更新
{	
	char input;
	if(kbhit())  // 判断是否有输入
	{
		input = getch();  // 根据用户的不同输入来移动，不必输入回车
		if (input == 'a')   
		{
			position_y--;
			left = position_y-radius;
			right = position_y+radius;
		}
		if (input == 'd')
		{
			position_y++;
			left = position_y-radius;
			right = position_y+radius;
		}
	}
}

int main()
{
	startup();  // 数据初始化	
	while (1)  //  游戏循环执行
	{
		show();  // 显示画面
		updateWithoutInput();  // 与用户输入无关的更新
		updateWithInput();     // 与用户输入有关的更新
	}
	return 0;
}
