#include<stdio.h>
int main()
{
    int h,l;
    scanf("%d %d",&h,&l);
    int t = h+l-1;
    printf("%d %d", t-h, t-l);


    return 0;
}
