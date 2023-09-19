#include<iostream> //输出流
using namespace std;


typedef int Element ;
//定义一个链表

typedef struct LinkNode
{
    Element data;
    struct LinkNode *next;
}LinkNode,*LinkList;



// 1。设计一个递归算法，删除不带头节点的单链表L中所有值为X的结点
// 分析，1）算法写法：递归 2）执行操作：查找到为X的节点，删除该节点 
int del_x(LinkList &L,Element x){
    LinkNode *p ;
    if(L==nullptr) return 0; //空链表或者到最后一个结点，需要注意的是不带头结点
    if(L->data == x){
        p = L;
        L = L->next;
        delete p;
        del_x(L,x);
    }else{
        L = L->next;
        del_x(L,x);
    }

}
// 性能分析：时间复杂度O(n),空间复杂度，只是声明了一个临时节点来使用，O(1)

// 2.在带头结点的单链表L中，删除所有值为X的节点，并释放其空间，假设值为X的节点不唯一
// 分析：1，带头结点，2，x的结点不唯一，需要完全遍历完链表
// 思考1：使用上面的递归算法，需要两个函数，一个处理头结点函数，一个用于递归（直接用第一题的就行）

void ignore_head(LinkList &L,Element x){
    if(L->next!=nullptr) del_x(L->next,x);
}


// 思考2：使用非递归算法，判断节点是否为空为跳出循环的条件，如果节点值为x时，前节点指向该节点的后节点，释放该节点
void del_x2(LinkList &L,Element x){
    LinkNode *pre = L,*p= L->next,*temp;
    while (p!=nullptr)
    {
        if(p->data == x){
            temp = p;
            p = p->next;
            pre->next = p; //前结点链接到删除结点的后结点
            delete temp;
        }else{
            pre = p;
            p = p->next;
        }
    }
    
}
// 思考3：根据尾插法链表的性质，用P指针扫描链表L，当P对应的值不为X时，尾指针指向该节点，否则将其释放：
void del_x3(LinkList &L,Element x){
    LinkNode *p = L->next,*r = L,*temp;
    while (p!=nullptr)
    {
        if(p->data ==x){
            temp = p;
            p = p->next;
            delete p;
        }else{
            r->next =p;
            r = p;
            p = p->next;
            
        }
    }
    r->next = nullptr; //尾插指向null
    
}

// 3.设 L为带头结点的单链表，编写算法实现从尾到头反向输出每个结点的值。
//思考：1，链表带头结点 2，倒序 3，需要输出结点的值,使用头插法，构建一个新链表，最后再依次输出新链表的值
//思考2：递归用法
void reverse(LinkList &L){
    LinkNode *p = L->next,*newList,*p2;
    newList->next = nullptr;
    while (p!=nullptr)
    {
        LinkNode *temp = new LinkNode;
        temp->data = p->data;
        p = p->next;
        temp->next = newList->next;
        newList->next = temp;
    }
    p2 = newList->next;
    while (p2!= nullptr)
    {
        cout<<p2->data<<endl;
        p2 = p2->next;
    }
}
//时间复杂度O(2N),空间复杂度O（N）


// 递归用法
void R_Print(LinkList L){
    if(L->next!=NULL){
        R_Print(L->next);
    }
    if(L!=NULL) cout<<L->data<<endl;
}

void R_Ignore_Head(LinkList L){
    if(L->next!=NULL) R_Print(L->next);
}




// 4. 试编写在带头结点的单链表L中删除一个最小值结点的高效算法(假设最小值结点是唯一)
// 思考：需要先寻找最小的结点，删除节点：辅助节点p，pre,minp，将pre.next = p.next,delete p;
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
    
    pre = p;
    p = p->next;
    //del
    minpre->next = minp->next;
    delete minp;

}

//  性能分析，时间复杂度O(n)；空间复杂度O（1）
// 5..有一个带头结点的单链表 L，就地逆置，空间复杂度为O（1）; 反转
//思路分析：要求空间复杂度为O(1),无法使用新建栈、链表来进行逆置
//思路1：递归，前一个和后一个更换位置，实现还有问题
void reverse(LinkList &L){
    if(L == nullptr || L->next == nullptr) return; //为空或者只有一个节点直接返回
    //递归反转剩余部分
    LinkNode *newhead= nullptr;
    reverseRecursive(L,L,newhead);
    L = newhead;
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

// 思路二，头插法思路（先插入的数据在最后）
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

// 6 .在一个带头结点的链表L，设计一个算法使其元素递增有序 
// 思路分析：链表排序，考虑排序算法

// 7.设在一个带表头结点的单链表中所有元素结点的数据值无序，试编写一个函数，删除表中所有介于给定的两个值(作为函数参数给出)之间的元素的元素 (若存在).
// 8.给定两个单链表，编写算法找出两个链表的公共结点。
// 9.给定一个带表头结点的单链表，设 head 为头指针，结点结构为(data,next)，data
// 为整型元素，next 为指针，试写出算法: 按递增次序输出单链表中各结点的数据元素
// 并释放结点所占的存储空间 (要求:不允许使用数组作为辅助空间 ).
// 10.将一个带头结点的单链表 A分解为两个带头结点的单链表 A和 B，使得A 表中含有原表
// 中序号为奇数的元素,而 B表中含有原表中序号为偶数的元素,且保持其相对顺序不变
// 11.设 C={a, bi,a2,b2,”,an, b3为线性表，采用带头结点的单链表存放，设计一个就地算
// 法，将其拆分为两个线性表，使得 A={ar,a2,·,a，B=n,b2,b}。
