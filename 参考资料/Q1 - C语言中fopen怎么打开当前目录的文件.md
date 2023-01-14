# C中fopen怎么打开当前文件夹目录下的文件?

> 提问：[基数科技](https://blog.csdn.net/cuibo1123)
> 时间：2005 / 12 / 21 - 10:42:33
> 链接：[CSDN](https://bbs.csdn.net/topics/80255896)

## 描述

? 他只能打开当前目录中的文件 怎么打开当前目录以外的目录中的文件??

## 回复

> 楼 7  - 基数科技  - 2005 / 12 / 27

    p=fopen(".//aa//aa.txt","w");

将会在当前程序（．exe文件）目录下的aa文件夹（已存在）下建立一个aa.txt并且以w方式打开给p

5楼的"..\\..\\a.bin"是不行的！
6楼的程序不错,不过好象和这个问题没什么关系。这个问题其实可以转化成“你这个程序怎么用”的问题

> 楼 6  - DF_4B - 2005 / 12 / 23

参照这个程序就行了(文件复制)：

    #include <stdio.h>
    #include <stdlib.h>

    int main(int argc,char *argv[]){
    int ch;
    FILE *fpinPtr,*fpoutPtr;
    if (argc!=3){
    printf("File copy program.\n\n");
    printf("Usage: command source_file target_file \n");
    printf("Usage example: \"copy src.txt obj.txt\"\n");
    exit(EXIT_FAILURE);
    }
    if ((fpinPtr=fopen(argv[1],"rb"))==NULL){
    printf("Input file \"%s\" could not be opened \n",argv[1]);
    exit(EXIT_FAILURE);
    }
    if ((fpoutPtr=fopen(argv[2],"wb"))==NULL){
    printf("Outout file \"%s\" could not be opened \n",argv[2]);
    exit(EXIT_FAILURE);
    }
    while(!feof(fpinPtr)){
    ch=fgetc(fpinPtr);
    if(ch>-1)
    fputc(ch,fpoutPtr);
    }
    fclose(fpinPtr);
    fclose(fpoutPtr);
    return 0;
    }

> 楼 5 - sdhp - 2005 / 12 / 23

"..\\..\\a.bin"只能在Windows下使用