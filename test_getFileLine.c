#include <stdio.h>

int main() {
    int fileSize = 0;           // 文件长度，长整型值
    char fileName[33];          // 文件名，长度不超过32个字符

    scanf("%s", fileName);      // 读入文件名

    FILE *fp;                   // 初始化文件指针
    char buffer[512];           // 缓冲区
    fp = fopen(fileName, "r+"); // 打开文件

    while(fgets(buffer, 512, fp) != NULL) {
        fileSize++;
    }

    printf("%d", fileSize);     // 输出文本总行数
}