# 在C语言中怎样让用户输入文件名来打开一个文件？

> 链接：[百度知道](https://zhidao.baidu.com/question/30747195.html)

## 描述

假设该文件为 D:\lj163\AOE\1.txt

## 回答1

> 答主：[mr_shj](https://zhidao.baidu.com/usercenter?uid=4b944069236f25705e798408&role=team)
> 时间：2017 / 09 / 04

    #include <stdio.h>
    int main(){
        FILE *fp;
        char filename[100];     //文件名
        char tempstr[1024];     //读文件的缓冲

        printf("请输入你要打开的文件名及路径，如c:\\temp.txt\n");
        gets(filename);         //这句要用户输入文件名

        if ((fp=fopen(filename,"r"))==NULL){        //打开文件，并判断是否有打开错误
            printf("打开文件%s出现错误\n",filename);
            return 0;
        }

        //以下显示文件内容
        while(fgets(tempstr,1024,fp)!=NULL) //读文件一行内容，最多1024字符到缓冲区，并判断是否文件已经结束 
            printf("%s",tempstr);   //显示缓冲区内容
        fclose(fp);                 //关闭文件
    }

## 回答2

> 答主：[WXD110114dccd8](https://zhidao.baidu.com/usercenter?uid=64934069236f25705e790e00&role=ugc)
> 时间：2017 / 09 / 20
> **本回答被提问者采纳**

    #include <stdio.h>
    #include <stdlib.h>
    int main()
    {
        char c[80];
        scanf("%s",&c);
        system(c);
        return 0;
    }
    // 输入要打开的文件路径，按回车。