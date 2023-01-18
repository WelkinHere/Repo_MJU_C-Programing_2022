# C语言修改文件某部分内容

> 作者：[小时候挺菜](https://blog.csdn.net/z735640642)
> 时间：2018-11-22 21:20:00
> 链接：[CSDN](https://blog.csdn.net/z735640642/article/details/84351454)

两种方法

1.全部读入内存，修改后重新存入文件

2.边读边写到另一新建文件，要修改的部分修改后存入新建文件，其他部分原封不动写入

写完删掉原先文件，将这个新的改为删掉那个的名字

## 方法一

读入内存修改 然后重新写入文件

    #include <stdio.h>
    #include <string.h>
    main()
    {
        int i=0,num;
        char str[10][50]={0},linedata[100]={0};
        FILE *fp=fopen("data.txt","r");
        FILE *fpw;
        while (fgets(linedata,sizeof(linedata)-1,fp))
        {
            if (strcmp(linedata,"bbb\n")==0)
            {
                strcpy(str[i],"ModContent\n");
            }else
            {
                strcpy(str[i],linedata);
            }
            i++;
        }
        fclose(fp);
        num=i;
        fpw = fopen("data.txt","w");
        for (i=0;i<num;i++)
        {
            fputs(str[i],fpw);
        }
        fclose(fpw);
    }

## 方法二

逐行写入临时文件，遇到修改部分 修改后写入临时文件 完成后删除data.txt 然后将临时文件改名为data.txt

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    main()
    {
        char linedata[100]={0};
        FILE *fp=fopen("data.txt","r");
        FILE *fpw=fopen("tmp.txt","w");
        while (fgets(linedata,sizeof(linedata)-1,fp))
        {
            if (strcmp(linedata,"bbb\n")==0)
            {
                fputs("ModContent\n",fpw);
            }else
                fputs(linedata,fpw);            
        }
        fclose(fp);
        fclose(fpw);
        system("del data.txt");
        system("rename tmp.txt data.txt");
    }
