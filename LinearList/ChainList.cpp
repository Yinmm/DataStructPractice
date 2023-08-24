#include<string>
#include<iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
typedef int ElemType;

//定义
typedef struct LNode
{
    /* data */
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;


//初始化
Status InitChainList(LinkList &L){
    L = new LNode;
    L->next = NULL;
    return OK;
}

//取值

Status GetElem(LinkList &L,int i,ElemType &e){ //取第i个节点的值
    int j;
    LNode *p;
    p = L->next;
    j = 1;
    while (p&&j<i)
    {
        p = p->next;
        j++;
    }
    if(!p||j>i) return ERROR;
    e = p->data;
    return OK;
}


//查找
LNode* SearchElem(LinkList &L,ElemType data){ //返回该节点
    LNode *p;
    p = L->next;
    while (p && p->data != data )
    {
        p = p->next;     
    }
    return p;
}

// 插入
Status insertElem(LinkList &L, ElemType e, int i){
    //1.找到待插入的节点a
    //2.将a的next指向待插入节点的next，将待插入节点的next指向a+1
    LNode *p;
    int j =0;
    p = L;
    while (p && j<i-1)
    {
        p = p->next;
        j++;
    }
    if(!p || j>i-1) return ERROR;
    LNode *s = new LNode;
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

//删除
Status DelList(LinkList &L,int i){
    // 找到要删除的节点a的前一个节点p
    // 将P的指针域指向删除节点的指向域，销毁待删除的节点
    LNode* p;
    int j = 0;
    p = L;
    while (p->next && j<i-1)
    {
        p=p->next;
        j++;
    }
    if(!p->next || j>i-1) return ERROR;
    LNode *q = p->next;
    p->next = q->next;
    delete q; //销毁节点
    return OK;

    
}

int main(){
    //初始化
    LinkList list;
    Status result = InitChainList(list);
    if(result==OK){
        cout<<"初始化成功"<<endl;
    }
    ElemType e,e1,e2,e3,e4 ;
    e = 22;
    e1 = 23;
    e2 = 24;
    e3 = 25;
    e4 = 26;
    insertElem(list,e,1);
    insertElem(list,e1,2);
    insertElem(list,e2,3);
    insertElem(list,e3,4);
    insertElem(list,e4,5);

    ElemType test;
    Status result2 = GetElem(list,1,test);
    if(result2==OK){
        cout<< "取得的指是："<<test<<endl;
    }else{
        cout<< "取值失败"<<endl;
    }

    LNode* search_node = SearchElem(list,e4);
    cout<<"查询到的值："<<search_node;

        // 释放链表节点
    LNode* current = list->next;
    while (current) {
        LNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    delete list;  // 释放头节点

}