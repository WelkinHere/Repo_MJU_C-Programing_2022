#include<stdio.h>
#include<conio.h>
int main()
{
    int key;
    while (1)
    {
        key = _getch();
        if (key == 27) {break;}
        else if (key == 72) {printf("按了 上 键, 键值 72 , 按 ESC退出!\n");}
        else if (key == 80) {printf("按了 下 键, 键值 80 , 按 ESC退出!\n");}
        else if (key == 75) {printf("按了 左 键, 键值 75 , 按 ESC退出!\n");}
        else if (key == 77) {printf("按了 右 键, 键值 77 , 按 ESC退出!\n");}
        else {printf("按了 %c 键, 键值 %d , 按 ESC 退出!\n", key, key);}
    }
    return 0;
}