#include<stdio.h>
#include<iostream>
int main()
{
  int a[10];
  int i,*p;
  printf("please enter 10 integer numbers:");
  for(i=0;i<10;i++)
      scanf("%d",&a[i]);
  for(p=a;p<(a+10);p++)
      printf("%d ",*p);    //通过数组名和元素序号计算元素地址，再找到该元素
  printf("\n");
  
  system("pause");
  return 0;
}