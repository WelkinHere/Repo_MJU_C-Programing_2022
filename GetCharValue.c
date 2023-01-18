#include <stdio.h>
int main() {
    char a;
    do{
    a = getchar();
    printf("%d\n", a);
    } while(a != 10);
}