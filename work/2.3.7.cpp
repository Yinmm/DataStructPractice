#include<iostream> //输出流
using namespace std;

typedef int ElemType ;
//定义一个链表

typedef struct LinkNode
{
    ElemType data;
    struct LinkNode *next;
}LinkNode,*LinkList;



// 1。设计一个递归算法，删除不带头节点的单链表L中所有值为X的结点
// 分析，1）算法写法：递归 2）执行操作：查找到为X的节点，删除该节点 
int del_x(LinkList &L,ElemType x){
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

void ignore_head(LinkList &L,ElemType x){
    if(L->next!=nullptr) del_x(L->next,x);
}


// 思考2：使用非递归算法，判断节点是否为空为跳出循环的条件，如果节点值为x时，前节点指向该节点的后节点，释放该节点
void del_x2(LinkList &L,ElemType x){
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
void del_x3(LinkList &L,ElemType x){
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
// 思路分析：链表排序，考虑插入排序算法
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

// 7.设在一个带表头结点的单链表中所有元素结点的数据值无序，试编写一个函数，删除表中所有介于给定的两个值(作为函数参数给出)之间的元素的元素 (若存在).
//思路分析：无序，需要遍历所有节点，介于指不包含边界值。删除需要pre结点指向下一个节点,临时节点来保存值并释放
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



// 8.给定两个单链表，编写算法找出两个链表的公共结点。
// 思路1：蛮方法：公共结点，可能不只一个，需要全部遍历对比，两个while循环，发现公共结点就打印出来。时间复杂度O(n*m)
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
// 思路2：利用两个链表公共结点的特征：从第一个公共结点到最后一个结点，都是公共结点，形状类似Y结构
void get_pub2(LinkList &L1,LinkList &L2){
    LinkNode *p1=L1->next,*p2=L2->next;
    int L1_len =0,L2_len=0; //获取链表长度,初始一定要赋值0，不然会随机大小
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


// 9.给定一个带表头结点的单链表，设 head 为头指针，结点结构为(data,next)，data
// 为整型元素，next 为指针，试写出算法: 按递增次序输出单链表中各结点的数据元素
// 并释放结点所占的存储空间 (要求:不允许使用数组作为辅助空间 ).
// 思路分析：排序算法，空间复杂度O(1),时间换空间.定义一个最小结点，遍历每个结点p，两个节点对比，小的被赋值为最新的最小结点。释放结点需要前驱节点pre
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


//答案：
void min_Delete(LinkList &L){
    while (L->next != nullptr) //循环到仅剩头结点
    {
        LinkNode *pre = L;
        LinkNode *p = pre->next;
        LinkNode *u;//指向被删除节点
        while (p->next !=nullptr)
        {
            if(p->next->data<pre->next->data){
                pre = p; //当前最小值为p的next，保存其前驱
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


// 10.将一个带头结点的单链表 A分解为两个带头结点的单链表 A和 B，使得A 表中含有原表
// 中序号为奇数的元素,而 B表中含有原表中序号为偶数的元素,且保持其相对顺序不变
//思路分析：尾插法创建单链表B(先进后出)，在int count = 1，count %2 ==0就为偶数位，将偶数位结点从A中删除，且使用尾插法添加到B中
//思路分析2,，不用创建序号变量，将p结点插入到A，next结点插入到B，p= next，
LinkList Discreat(LinkList &A){
    int i =1;
    LinkList B = new LinkNode; //创建B表头
    B->next = nullptr;
    LinkNode *ra = A,*rb = B,*p; //ra,rb分别指向A,B 的尾结点
    p = A->next;
    A->next = nullptr;
    while (p!=nullptr)
    {
        if(i%2==0){
            rb->next = p;
            rb = p;
        }else{
            ra->next = p;
            ra = p;
        }
        p = p->next;
        i++;
    }
    ra->next = nullptr;
    rb->next = nullptr;
    return B;   
}




// 11.设 C={a1,b1,a2,b2,....an,bn}为线性表，采用带头结点的单链表存放，设计一个就地算
// 法，将其拆分为两个线性表，使得 A={a1,a2,a3,a4},B={bn...b2,b1}。
//思路分析，设立序号变量来判断奇偶，跟上题类似，也可不采用序号，对于A表使用尾插法，对于B表使用头插法
LinkList Discreat_2(LinkList &A){
    LinkList B = new LinkNode;
    B->next = nullptr;
    LinkNode *p = A->next,*q;
    LinkNode *ra = A;
    while (p!=nullptr)
    {
        ra->next = p;ra =p;
        p = p->next;
        if(p!= nullptr){
            q = p->next;
            p->next = B->next;
            B->next = p;
            p = q;
        }
    }
    ra->next  = nullptr;
    return B;  
}


//12. 在递增有序的线性表中有相同的元素，储存方式为单链表，做去重处理
//思路分析：因为递增有序，所以可以使P和后继结点的数据对比，如果相同，删除后继结点，如果不同，P指向其后续结点
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


// 13.假设有两个按元素值递增次序排列的线性表，均以单链表形式存储。请编写算法将这两
// 个单链表归并为一个按元素值递减次序排列的单链表,并要求利用原来两个单链表的结
// 点存放归并后的单链表。
//思路分析：递增有序链表合并，合并完成需要变为降序，可采用头插法加入新节点
void mierge(LinkList &A,LinkList &B){
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
    delete B; //释放B头结点
}




// 14.设A和B.是两个单链表(带头结点)，其中元素递增有序。设计一个算法从A和B中的
// 公共元素产生单链表 C，要求不破坏A、B的结点。
//思路分析：不破坏A，B结点，需要新建一个链表C，公共元素需要新建节点（new），使用尾插法。可以通过遍历A中的元素与B元素一一对比，确定公共元素。因为递增有序，如果元素不等时
//值小的指针往下走，元素相等时，两个表指针都往下走
LinkList get_commion(LinkList A,LinkList B){
    LinkNode *p=A->next,*q = B->next,*r,*s;
    LinkList C  = new LinkNode;
    r = C;
    while (p!= nullptr&&q!=nullptr)
    {
        if(p->data <q->data){
            p = p->next;
        }else if (p->data>q->data)
        {
            q = q->next;
        }else{
            s = new LinkNode;
            s->data = p->data;
            r->next = s;
            r = s;
            p = p->next;
            q = q->next;
        }
    }
    r->next = nullptr;
    return C;
}



// 15.已知两个链表A和 B分别表示两个集合，其元素递增排列。编制函数，求 A与B的交
// 集，并存放于A链表中。
//思路分析：递增排序，求公共元素，与上题类似。使用A链表存放，可使用尾插法，相同元素节点保留一个，其他元素释放节点


// 16。两个整数序列A=al,a2,a3,,an和B=b1,b2,b3...bn;已经存入两个单链表中，设计一个算法，判断序列 B是否是序列 A 的连续子序列 
//思路分析：KMP算法？？标记节点变量flag，用于表示A每次遍历开始时的结点。同时遍历2链表，如果B中元素 = A元素，则同时指向下一结点；如果B！= A元素，B指向首元节点，标记节点指向下一个结点，A指向标记节点flag
//遍历完成后，如果B结点后继结点为空，则B是字序列
// 17
// 设计一个算法用于判断带头结点的循环双链表是否对称
// 18.有两个循环单链表，链表头指针分别为 h1和 h2，编写一个函数将链表 h2 链接到链表
// h1 之后，要求链接后的链表仍保持循环链表形式。:
// 19.设有一个带头结点的循环单链表，其结点值均为正整数。设计一个算法，反复找出单链
// 表中结点值最小的结点并输出，然后将该结点从中删除，直到单链表空为止，再删除表
// 头结点。
// 设头指针为L的带有表头结点的非循环双向链表，其每个结点中除有 pre(前驱指针).
// 20
// data(数据)和 next (后继指针) 域外，还有一个访问频度域 freg。在链表被启用
// 前，其值均初始化为零。每当在链表中进行一次 Locate(L,x)运算时，今元素值为 X
// 的结点中 freg 域的值增 1，并使此链表中结点保持按访问频度非增(递减》的顺序排
// 列，同时最近访问的结点排在频度相同的结点前面，以便使频繁访问的结点总是靠近表
// 头。试编写符合上述要求的 Locate(L,x)运算的算法，该运算为函数过程，返回找到
// 结点的地址，类型为指针型
// 单链表有环，是指单链表的最后一个结点的指针指向了链表中的某个结点(通常单链表
// 21.
// 的最后一个结点的指针域是空的)。试编写算法判断单链表是否存在环
// 1) 给出算法的基本设计思想。
// 2)根据设计思想，采用 C或 C++语言描述算法，关键之处给出注释
// 3) 说明你所设计算法的时间复杂度和空间复杂度