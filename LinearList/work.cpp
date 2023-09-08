typedef struct LNode
{
    /* data */
    int data;
    struct LNode *next;
}LNode,*LinkList;

// (1 )将两个递增的有序链表合并为一个递增的有序链表。要求结果链表仍使用原来两个链表
// 的存储空间，不另外占用其他的存储空间。表中不允许有重复的数据
void MergeList(LinkList A,LinkList B,LinkList &C){
    LNode *pa,*pb,*pc;
    pa = A->next;pb = B->next;
    C = pc = A; //C的头节点指向a的头结点
    while(pa && pb){
        if (pa->data<pb->data){
            pc->next = pa;
            pa = pa->next;
            pc = pc->next;
        }else if (pa->data>pb->data)
        {
            pc->next = pb;
            pb = pb->next;
            pc = pc->next;
        }else{
            pc->next = pa;
            pa = pa->next;
            pc = pc->next;
            LNode *q = pb->next;
            delete pb;
            pb = q;
        }
        
    }
    pc->next=pa?pa:pb; //处理后续节点
    delete B;//删除b的头结点
}

void MergeList_L(LinkList &La,LinkList &Lb,LinkList &Lc){
    LNode *pa,*pb,*pc;
    pa=La->next;  pb=Lb->next;
    Lc=pc=La;             //用La的头结点作为Lc的头结点 
    while(pa && pb){
        if(pa->data<pb->data){ pc->next=pa;pc=pa;pa=pa->next;}
        else if(pa->data>pb->data) {pc->next=pb; pc=pb; pb=pb->next;}
        else {// 相等时取La的元素，删除Lb的元素
                pc->next=pa;pc=pa;pa=pa->next;
                LNode *q=pb->next;delete pb ;pb =q;}
    }
    pc->next=pa?pa:pb;    //插入剩余段  
    delete Lb;             //释放Lb的头结点}  
}

// （2）将两个非递减的有序链表合并为一个非递增的有序链表。
// 要求结果链表仍使用原来两个链表的存储空间, 不另外占用其它的存储空间。表中允许有重复的数据。
void mergelist2(LinkList &A,LinkList &B, LinkList &C){
    LNode *pa,*pb,*pc,*q;
    pa = A->next;pb = B->next;
    C = pc = A;
    pc->next = nullptr;
    while (pa || pb){
        if(!pa){q = pb;pb = pb->next;}
        else if(!pb){q = pa;pa = pa->next;}
        else if(pa->data<=pb->data){q = pa;pa=pa->next;}
        else{q = pb;pb= pb->next;}
        q->next = pc->next;pc->next = q; //使用头插入插入
    }
    delete B;
}

void Union(LinkList& La, LinkList& Lb, LinkList& Lc) {
    LNode *pa,*pb,*pc,*q;
    pa = La->next;  pb = Lb->next;              // 初始化
    Lc=pc=La; //用La的头结点作为Lc的头结点 
    Lc->next = nullptr;
    while ( pa || pb ) {
        if  ( !pa )  { q = pb;  pb = pb->next; }
        else if  ( !pb )  { q = pa;  pa = pa->next; } 
        else if (pa->data <= pb->data )     { q = pa;  pa = pa->next; }
        else  { q = pb;  pb = pb->next; }
        q->next = Lc->next;  Lc->next = q;    // 插入
    }
    delete Lb;             //释放Lb的头结点
}


// （3）已知两个链表A和B分别表示两个集合，其元素递增排列。请设计算法求出A与B的交集，并存放于A链表中。
void jiaoji(LinkList &A,LinkList&B){
    LNode *pa,*pb,*q;
    LinkList C;
    LNode *pc;
    C = pc = A;
    pa = A->next;pb = B->next;
    if(pa->data<pb->data){
        pa = pa->next;
        while(pa&&pb){
            if(pa->data == pb->data){q =pa;pc->next = q;pc = pc->next; pa = pa->next;pb = pb->next;}
            else{pa = pa->next;}
        }
    }else if(pa->data<pb->data){
        pb = pb->data;
        while(pa&&pb){
            if(pb.data)
        }
    }
}