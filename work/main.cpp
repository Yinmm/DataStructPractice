#include<iostream> //输出流
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

void sort(LinkList &L){
    LinkNode *p = L->next,*pre;
    LinkNode *r = p->next; //r保持p后继节点指针，保证不断链
    p->next = nullptr; //构造只含一个节点的有序表
    p = r;
    while (p!=nullptr)
    {
        r = p->next; //保存P的后继结点
        pre = L;
        while (pre->next!=nullptr && pre->next->data<p->data)
        {
            pre = pre->next; //在有序表中查找插入p的前驱节点pre
        }
        p->next = pre->next; //将P插入到pre之后
        pre->next = p;
        p = r; // 扫描原单链表的剩余结点
    }
    
}

 
void del_value(LinkList &L,ElemType x,ElemType y){
    LinkNode *p = L->next,*pre;
    pre = L;
    while (p!=nullptr)
    {
        if(p->data >x && p->data<y){
            LinkNode *temp;
            temp = p;
            pre->next = p->next;
            pre = p;
            p = p->next;
            delete temp;
        }else{
            pre = p;
            p = p->next;
        }
    }
    
}

void get_pub(LinkList &L1, LinkList &L2){
    LinkNode *p1 = L1->next,*p2 = L2->next;
    while(p1 != nullptr)
    {
        while (p2 != nullptr)
        {
            if(p1 == p2) {
                cout<<p1<<endl;
                return;
            }else{
                p2 = p2->next;
            } 
        }
        p1 = p1->next;
    } 
}

void get_pub2(LinkList &L1,LinkList &L2){
    LinkNode *p1=L1->next,*p2=L2->next;
    int L1_len=0,L2_len=0; //获取链表长度
    while(p1 !=nullptr){
        p1 = p1->next;
        L1_len++;
    }
    while (p2 !=nullptr)
    {
        p2 = p2->next;
        L2_len++;
    }
    int d_value;

    p1=L1->next; // 重新指向链表首部
    p2=L2->next; // 重新指向链表首部
    d_value = L1_len>L2_len?L1_len-L2_len:L2_len-L1_len; //求长度差值
    if(L1_len>L2_len){
        for(int i=0;i<d_value;i++){
            p1 = p1->next;
        }
    }else{
        for(int i=0;i<d_value;i++){
            p2 = p2->next;
        }
    }

    while (p1 !=nullptr)
    {
        if(p1 == p2){
            cout<<p1<<endl; //打印出第一个结点，后续所有结点都是公共结点
            return;
        }else{
            p1 = p1->next;
            p2 = p2->next;
        }
    }
}


void sort_realese(LinkList &L){
    LinkNode *p = L->next,*pre,*minpre,*r;
    while (p !=nullptr)
    {
        minpre = pre = L;
        LinkNode *min;
        min = p;
        r = p->next;
        if(r!=nullptr) pre = p;//后驱结点存在，pre指到r的前结点p
        while (r!=nullptr)
        {
            if(r->data<min->data){
                min = r;
                minpre=pre;
                pre = r;
                r=r->next;
            }else{
                pre = r;
                r = r->next;
            }
        }
        cout<<min->data<<endl;
        minpre->next = min->next;
        delete min;
        p = L->next; //重新让P指向第一个结点
    }
}
void min_Delete(LinkList &L){
    while (L->next != nullptr) //循环到仅剩头结点
    {
        LinkNode *pre = L;
        LinkNode *p = pre->next;
        LinkNode *u;//指向被删除节点
        while (p->next !=nullptr)
        {
            if(p->next->data<pre->next->data){
                pre = p; //当前最小值的前驱
            }
            p = p->next;
        }
        cout<<pre->next->data<<endl;
        u = pre->next;
        pre->next = u->next;
        delete u;
        
    }
    delete L;//释放头结点
    
}

void del_duplicate(LinkList &L){
    LinkNode *p = L->next,*del;
    while(p->next != nullptr){
        if(p->data == p->next->data){
            del = p->next;
            p->next = del->next;
            delete del;
        }else{
            p = p->next;
        }
    }
}

void merge(LinkList &A,LinkList &B){
    LinkNode *p1 = A->next,*p2 =B->next,*q;
    A->next = nullptr; //将A表头结点作为新表的头结点
    while (p1 != nullptr && p2 !=nullptr)
    {
        if(p1->data < p2->data){
            q = p1->next;
            p1->next = A->next;
            A->next = p1;
            p1 = q;
        }else{
            q = p2->next;
            p2->next = A->next;
            A->next = p2;
            p2 = q;
        }
    }
    //处理剩余结点{
    while(p1 !=nullptr){
            q = p1->next;
            p1->next = A->next;
            A->next = p1;
            p1 = q;
    }
    while (p2 !=nullptr)
    {
            q = p2->next;
            p2->next = A->next;
            A->next = p2;
            p2 = q;
    }
}


int main(){
    //初始化
    LinkList list,list2;
    Status result = InitChainList(list);
    InitChainList(list2);
    if(result==OK){
        cout<<"初始化成功,头节点地址："<< list <<endl;
    }

    ElemType e,e1,e2,e3,e4,e5,e6,e7,e8,e9 ;
    e = 12;
    e1 = 15;
    e2 = 18;
    e3 = 19;
    e4 = 33;
    e5 = 2;
    e6 = 13;
    e7 = 14;
    e8 = 19;
    e9 = 35;
    insertElem(list,e,1);
    insertElem(list,e1,2);
    insertElem(list,e2,3);
    insertElem(list,e3,4);
    insertElem(list,e4,5);
    insertElem(list2,e5,1);
    insertElem(list2,e6,2);
    insertElem(list2,e7,3);
    insertElem(list2,e8,4);
    insertElem(list2,e9,5);
    Print(list);
    merge(list,list2);
    cout<<"-----------"<<endl;
    Print(list);

    system("pause");
}