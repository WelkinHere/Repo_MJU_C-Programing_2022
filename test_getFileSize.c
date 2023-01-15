#include <stdio.h>

int main() {
    long int fileSize;      // 文件长度，长整型值
    char fileName[33];      // 文件名，长度不超过32个字符

    scanf("%s", fileName);

    // 初始化文件指针
    FILE *fp;
    fp = fopen(fileName, "w+");

    fseek(fp, 0, SEEK_END);

    fileSize = ftell(fp);

    printf("%d", fileSize);
}