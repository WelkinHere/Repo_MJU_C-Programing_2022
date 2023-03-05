# C语言获取文件长度方法汇总

> 作者：[ffashion](https://blog.csdn.net/qq_44212821)
> 时间：于 2021-01-11 12:43:46 发布
> 来源：[CSDN](https://blog.csdn.net/qq_44212821/article/details/112465452)

## 方法1 使用 stat.h

    #include <sys/stat.h>
    #include <stdio.h>

    long get_file_size(char *file_name){
        struct stat sb = {0}; 
        int fd = open(file_name,O_RDONLY);
        fstat(fd,&sb);
        return sb.st_size;
    }

    int main(int argc, char *args[]){
        printf("%d",get_file_size("./filename.txt"));//获取文件的长度
    }

## 方法2 只使用stdio

    #include <stdio.h>

    long get_file_size(char *file_name){
        FILE *fp = NULL;
        if((fp = fopen(file_name,"r")) == NULL){
            printf("获取文件失败");
            return -1;
        }

        //从文件末尾偏移，偏移0位
        fseek(fp,0,SEEK_END);

        long file_size = ftell(fp);//ftell()存储当前文件描述符的读取的偏移位置，这里就是文件末尾
        fclose(fp);
        return file_size;
    }
    
    int main(int argc, char *args[]){
        printf("%ld",get_file_size("./filename.txt"));
    }
