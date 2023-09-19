#include<string> 
#include<iostream> //输出流
#include<vector> // 动态创建数组
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
}LNode,LinkNode,*LinkList;


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
    p = L; //赋值头节点
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


// 前插法创建单链表
Status CreatPriorList(LinkList &L,vector<int> elemlist){ 
    L = new LNode;
    L->next =NULL;
    int Length = elemlist.size();
    for(int i=0;i<Length;i++){
        LNode* p =new LNode;
        p->data = elemlist[Length-1-i]; //新节点插入到头结点之后，需要倒序插入数据，越后插入的数据越在前面
        p->next = L->next;
        L->next = p;
    }
    return OK;
}

//尾插法创建单链表
Status CreatTailList(LinkList &L,vector<int> elemlist){
    L = new LNode; //生成头结点
    L->next = NULL; 
    LNode* r; //尾指针
    r=L;
    for(int i=0;i<elemlist.size();i++){
        LNode *p = new LNode;
        p->data = elemlist[i];
        r->next = p; //尾指针的指针域指向p
        p->next = NULL; // 因为P是最后一个,所以P的指针域设为空
        r = p; //r指向新的尾结点;
    }
    return OK;
}




// 释放链表
void releaseList(LinkList &L){
        // 释放链表节点
    LNode* current = L->next;
    while (current) {
        LNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    delete L;  // 释放头节点
}

// 打印链表
void Print(LinkList &L){
    //打印链表
    LNode* node = L->next; //跳过头结点
    while (node != nullptr)
    {
        cout << "链表的值："<<node->data<< endl;
        node = node->next;
    }
}


void del_min(LinkList &L){
    LinkNode *p = L->next,*pre = L,*minp,*minpre;
    if(p == nullptr) return;
    minp = p; //使用第一个数作为最小值
    minpre = pre;
    while (p!=nullptr)
    {
        if(p->data<minp->data){
            minp = p;
            minpre = pre;
        }
        pre = p;
        p = p->next;
    }
    //del
    minpre->next = minp->next;
    delete minp;

}

void reverseRecursive(LinkNode* current,LinkNode* prev,LinkList &newHead){
    if (current == nullptr) {
        newHead = prev;
        return;
    }
    LinkNode* next = current->next;
    current->next = prev;
    
    reverseRecursive(next, current, newHead);

}


void reverse_head_insert(LinkList &L){
    LinkNode *p,*r;
    p = L->next;L->next = nullptr;
    if(p == nullptr || p->next == nullptr) return;
    while (p!=nullptr)
    {
        r = p->next;
        p->next = L->next;
        L->next = p;
        p = r;
    } 
}


int main(){
    //初始化
    LinkList list;
    Status result = InitChainList(list);
    if(result==OK){
        cout<<"初始化成功,头节点地址："<< list <<endl;
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
    Print(list);
    reverse_head_insert(list);
    cout<<"-----------"<<endl;
    Print(list);


    // ElemType test;
    // Status result2 = GetElem(list,1,test);
    // if(result2==OK){
    //     cout<< "取得的指是："<<test<<endl;
    // }else{
    //     cout<< "取值失败"<<endl;
    // }

    // LNode* search_node = SearchElem(list,e4);
    // cout<<"查询到的值："<<search_node<< endl;

    // DelList(list,-6);

    // search_node = SearchElem(list,e4);
    // cout<<"查询到的值："<<search_node<<endl;
    // // releaseList(list);

    // // 定义动态数组
    // vector<int> elemlist = {e,e1,e2,99,90};
    // Print(list);
    // CreatTailList(list,elemlist); 
    // Print(list);
    // releaseList(list);



    system("pause");
}