# C语言文件读写操作（详解）

> 作者：[放码过来呀！！！](https://blog.csdn.net/m0_46671092)
> 时间：2020 / 07 / 21 - 23:02:51
> 链接：[CSDN](https://blog.csdn.net/m0_46671092/article/details/107498443)

## 数据流和缓冲区是什么？文件类型和文件存取方式都有啥？

### 数据流

就C程序而言，从程序移进，移出字节，这种字节流就叫做流。程序与数据的交互是以流的形式进行的。进行C语言文件的读写时，都会先进行“打开文件”操作，这个操作就是在打开数据流，而“关闭文件”操作就是关闭数据流。

### 缓冲区

在程序执行时，所提供的额外内存，可用来暂时存放准备执行的数据。它的设置是为了提高存取效率，因为内存的存取速度比磁盘驱动器快得多。

当使用标准I/O函数(包含在头文件stdio.h中)时，系统会自动设置缓冲区，并通过数据流来读写文件。当进行文件读取时，是先打开数据流，将磁盘上的文件信息拷贝到缓冲区内，然后程序再从缓冲区中读取所需数据。事实上，当写入文件时，并不会马上写入磁盘中，而是先写入缓冲区，只有在缓冲区已满或“关闭文件”时，才会将数据写入磁盘。

### 文件类型

#### 文本文件和二进制文件

文本文件是以字符编码的方式进行保存的。

二进制文件将内存中的数据原封不动的进行保存，适用于非字符为主的数据。其实，所有的数据都可以算是二进制文件。二进制文件的优点在于存取速度快，占用空间小。

### 文件存取方式

#### 顺序存取方式和随机存取方式

顺序存取就是从上往下，一笔一笔读取文件的内容。写入数据时，将数据附加在文件的末尾。这种存取方式常用于文本文件。

随机存取方式多半以二进制文件为主。它会以一个完整的单位来进行数据的读取和写入，通常以结构为单位。

## 什么是文件呢？

文件是一段数据的集合，这些数据可以是有规则的，也可以是无序的集合。在stdio.h有一个非常重要的东西，文件指针，每个文件都会在内存中开辟一块空间，用于存放文件的相关信息，这些信息保存在一个结构体中：

    struct _iobuf {
        char *_ptr;         //指向buffer中第一个未读的字节
        int _cnt;           //记录剩余的未读字节的个数
        char *_base;        //文件的缓冲
        int _flag;          //打开文件的属性
        int _file;          //获取文件描述
        int _charbuf;       //单字节的缓冲，即缓冲大小仅为1个字节
        int _bufsiz;        //记录这个缓冲大小
        char *_tmpfname;    //临时文件名
    };
    typedef struct _iobuf FILE;

FILE是一个数据结构，用于访问一个流。每个流都会对应一个FILE结构体。

## C语言文件操作函数概览

C语言中没有输入输出语句，所有的输入输出功能都用 ANSI C提供的一组标准库函数来实现。文件操作标准库函数有：

### 文件的打开

    fopen()：打开文件

### 文件的关闭

    fclose()：关闭文件

### 文件的读写

    fgetc()：读取一个字符
    fputc()：写入一个字符
    fgets()：读取一个字符串
    fputs()：写入一个字符串
    fprintf()：写入格式化数据
    fscanf()：格式化读取数据
    fread()：读取数据
    fwrite()：写入数据

### 文件状态检查

    feof()：文件是否结束
    ferror()：文件读/写是否出错
    clearerr()：清除文件错误标志
    ftell()：文件指针的当前位置

### 文件指针定位

    rewind()：把文件指针移到开始处
    fseek()：重定位文件指针

### 参数解释

“r”：以只读的形式打开文本文件(不存在则出错)
“w”：以只写的形式打开文本文件(若不存在则新建，反之，则从文件起始位置写，覆盖原内容)
“a”：以追加的形式打开文本文件(若不存在，则新建；反之，在原文件后追加)
“r+”：以读写的形式打开文本文件(读时，从头开始；写时，新数据只覆盖所占的空间)
“wb”：以只写的形式打开二进制文件
“rb”：以只读的形式打开二进制文件
“ab”：以追加的形式打开一个二进制文件
“rb+”：以读写的形式打开二进制文件。
“w+”：首先建立一个新文件，进行写操作，然后从头开始读(若文件存在，原内容将全部消失)
“a+”：功能与”a”相同。只是在文件尾部追加数据后，可以从头开始读
“wb+”：功能与”w+”相同。只是在读写时，可以由位置函数设置读和写的起始位置
“ab+”：功能与”a+”相同。只是在文件尾部追加数据之后，可以由位置函数设置开始读的起始位置

## C语言文件操作函数详解

### 打开文件

    FILE *fopen( const char *filename, const char *mode );

- filename：文件的路径
- mode：打开模式

#### 例

    int main()
    {
        FILE* f;
        f = fopen("file.txt", "w");
        if (f != NULL)
        {
            fputs("fopen example", f);
            fclose(f);
            f=NULL;
        }
        return 0;
    }

#### 注意

- 文件是否打开成功
- 关闭文件
- 文件指针置空

### 关闭文件

    int fclose( FILE *stream );

- stream：流
#### 例

    if(fclose(f)!=0) 
    {
        printf("File cannot be closed/n"); 
        exit(1); 
    } 
    else
    {
        printf("File is now closed/n"); 
    }

### 读取字符

    int fgetc ( FILE * stream );

- stream：流

#### 例

    #include <stdio.h>
    int main ()
    {
    FILE * pFile;
    int c;
    int n = 0;
    pFile = fopen ("D:\\myfile.txt", "r");
    if (pFile == NULL) perror ("Error opening file"); // 打开失败
    else
    {
        while (c != EOF)
        {
        c = fgetc (pFile); // 获取一个字符
        if (c == '$') n++; // 统计美元符号 '$' 在文件中出现的次数
        }
        fclose (pFile); // 一定记得要关闭文件
        printf ("The file contains %d dollar sign characters ($).\n",n);
    }
    return 0;
    }

### 写入字符

    int fputc( int c, FILE *stream );

- c：要写入的字符
- stream：流

#### 例

    char ch;
    FILE* pf = fopen("file.txt", "w");
    if (pf == NULL)
    {
        perror("error opening file");
        exit(0);
    }
    ch = getchar();
    while (ch != '$')
    {
        fputc(ch, pf);
        ch = getchar();
    }
    fclose(pf);

### 读取字符串

    char * fgets ( char * str, int num, FILE * stream );

- str：将读取到的内容复制到的目标字符串
- num：一次读取的大小
- stream：流

#### 例

    char buf[10] = { 0 };
    FILE *pf = fopen("file.txt", "r");
    if (pf == NULL)
    {
        perror("open file for reading");
        exit(0);
    }
    fgets(buf, 9, stdin);
    printf("%s", buf);
    fclose(pf);

### 写入字符串

    int fputs( const char *string, FILE *stream );

- string：要写入的字符串
- stream：一次读取的大小

#### 例

    char buf[10] = { 0 };
    FILE *pf = fopen("file.txt", "r");
    if (pf == NULL)
    {
        perror("open file for reading");
        exit(0);
    }
    fgets(buf, 9, stdin);
    fputs(buf, stdout);
    fclose(pf);

### 读取数据块

    size_t fread ( void * ptr, size_t size, size_t count, FILE * stream );

- ptr：目标内存块
- size：一次读取的字节大小
- count：一次读取多少个 size
- stream：流

#### 例

    #include <stdio.h>
    #include <string.h>
    
    int main()
    {
        FILE *pFile = fopen("file.txt", "rb");
        if (pFile == NULL) 
        {
            perror ("Error opening file");
            return 0;
        }
        char buf[100] = { 0 };
        while (!feof(pFile)) //没有到文件末尾
        {
            memset(buf, 0, sizeof(buf));
            size_t len = fread(buf, sizeof(char), sizeof(buf), pFile);
            printf("buf: %s, len: %d\n", buf, len);
        }
        fclose(pFile);
    }

### 写入数据块

    size_t fwrite ( const void * ptr, size_t size, size_t count, FILE * stream );

同理，简单好理解，就不详细阐述了。

### 文件指针重定位

    int fseek ( FILE * stream, long int offset, int origin );

- stream：流
- offset：相对应 origin 位置处的偏移量，单位为字节
- origin：指针的位置
- #define SEEK_CUR 1 // 当前位置
- #define SEEK_END 2 // 末尾
- #define SEEK_SET 0 // 开头

### 获取指针位置

    long int ftell ( FILE * stream );

- stream：流

### 获取文件大小
例：

    long n;
    fseek(pf,0,SEEK_END);
    n=ftell(pf);

### 文件指针移到开始处

    void rewind( FILE *stream );

- stream：流

### 清除文件错误标志

    void clearerr( FILE *stream );

- stream：流

### 文件流是否读到了文件尾

    int feof( FILE *stream );

- stream：流

### 重命名文件

    int rename ( const char * oldname, const char * newname );

- oldname：原名
- newname：新名

### 删除文件

    int remove ( const char * filename );

- filename：文件的路径