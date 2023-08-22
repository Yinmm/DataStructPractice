//头文件包含
#include <stdio.h>
#include <stdlib.h>
//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
//Status 是函数的类型，其值是函数结果状态代码
typedef int Status;
typedef char ElemType;
//顺序表的定义
#define MAXSIZE 100
typedef struct {
	ElemType* elem;
	int length;
} SqList;

//顺序表的初始化函数
Status InitList_Sq(SqList* L)
{
	L->elem = (ElemType*)malloc(MAXSIZE * sizeof(ElemType));
	if (!L->elem)
		exit(OVERFLOW);
	L->length = 0;
	return OK;
}
//销毁线性表
void DestroyList_Sq(SqList* L)
{
	if (L->elem)
		free(L->elem);
	L = NULL;
}
//清空线性表
void ClearList(SqList* L)
{
	L->length = 0;
}
//求线性表的长度
int GetLength(const SqList* L)
{
	return L->length;
}
//判断线性表是否为空
Status IsEmpty(const SqList* L)
{
	if (L->length == 0)
		return TRUE;
	else
		return FALSE;
}
//线性表取第i个值
Status GetElem(const SqList* L, int i, ElemType e)
{
	if (i<1 || i>L->length)
		return ERROR;
	else
	{
		e = L->elem[i - 1];
		return OK;
	}
}
//线性表按值顺序查找
Status LocateElem(const SqList* L, const ElemType e)
{
	int i;
	for (i = 0; i <= L->length - 1; i++)
	{
		if (L->elem[i] == e)
			return i + 1;		//查找成功返回元素位置
	}
	return 0;		//查找失败返回0
}
//顺序表的插入
Status InsertList_Sq(SqList* L, int n, const ElemType e)
{
	int i;
	if (n >= 1 && n <= L->length + 1)	//判断插入位置是否合法
	{
		if (L->length == MAXSIZE)		//判断存储空间是否已满
			return ERROR;
		for(i=L->length-1; i>=n-1; i--)		//插入位置及之后元素后移
		{
			L->elem[i+1] = L->elem[i];
		}
		L->elem[n - 1] = e;
		L->length += 1;
		return OK;
	}
	return ERROR;
}
//顺序表删除
Status DeleteElem(SqList* L, int n)
{
	int i;
	if (n >= 1 && n <= L->length)
	{
		L->elem[n - 1] = 0;		//删除指定元素
		for (i = n - 1; i <= L->length - 1; i++)		//剩余元素移位
		{
			L->elem[i] = L->elem[i + 1];
		}

		L->length--;		//顺序表长度-1
		return OK;
	}
	return ERROR;
}
//顺序表显示
void ShowList_Sq(const SqList* L)
{

	if (L->length == 0)
		puts("The SqList is empty!");
	
	else
	{
	int i;
	for (i = 0; i < L->length; i++)
	{
		printf("%d ", L->elem[i]);
	}
	putchar('\n');
	printf("The length of SqList is %d\n", L->length);

	}
}
//合并两个顺序表,将L2合并到L1中
Status MergeList_Sq(SqList* L1, const SqList* L2)
{
	if (L1->length == 0 || L2->length == 0)
	{
		puts("Length must be non-zero!");
		return ERROR;
	}
	else if (L1->length + L2->length > MAXSIZE)
	{
		puts("Overflow");
		return OVERFLOW;
	}
	else 
	{
		int i;
		for (i = 0; i <= L2->length - 1; i++)
		{
			L1->elem[i + L1->length] = L2->elem[i];
		}
		L1->length += L2->length;
		return OK;
	}
}
