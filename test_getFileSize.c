#include <stdio.h>

int main() {
    long int fileSize;          // 文件长度，长整型值
    char fileName[33];          // 文件名，长度不超过32个字符

    scanf("%s", fileName);      // 读入文件名

    FILE *fp;                   // 初始化文件指针
    fp = fopen(fileName, "w+"); // 打开文件

    fseek(fp, 0, SEEK_END);     // 移动文件指针到文件末尾

    fileSize = ftell(fp);       // 将文件末尾处的指针位置输出到变量

    printf("%d", fileSize);     // 输出指针位置
}