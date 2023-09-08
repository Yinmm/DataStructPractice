#include<string> 
#include<iostream> //输出流
#include<vector> // 动态创建数组
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
typedef int ElemType;


//定义双向链表
typedef struct DuLNode
{
    /* data */
    ElemType data;
    struct DuLNode *next;
    struct DuLNode *prior;
}DuLNode,*DuLinkList;



//初始化空的双向链表
Status InitDuList_L(DuLinkList &L){
    L = new DuLNode;
    L->next = NULL;
    L->prior = NULL;
    return OK;
}

DuLNode *GetElemP_DuL(DuLinkList L, int i) {
	//在带头结点的双向链表L中查找第i个元素，返回结点的地址
	int j;
	DuLinkList p;
	p = L->next;
	j = 1; //初始化，p指向第一个结点，j为计数器
	while (j < i && p) { //顺链域向后扫描，直到p指向第i个元素或p为空
		p = p->next;
		++j;
	}
	if (!p || j > i)
		return NULL; //第i个元素不存在
	return p;
} //GetElemP_DuL

// 双向链表的插入
Status ListInsert_Du(DuLinkList &L, int i,ElemType e){
    //在双向链表的第i个位置插入元素
    DuLNode *p,*s;
    p = GetElemP_DuL(L,i); //获取位于i位置的节点
    if(!p){
        return ERROR;
    }
    s = new DuLNode;
    s->data = e;
    p->next->prior = s;
    s->next = p->next->next;
    p->next = s;
    s->prior = p;
}