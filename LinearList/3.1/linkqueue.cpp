typedef int Element;

//定义
typedef struct QNode
{
    /* data */
    Element data;
    struct QNode* next;
}QNode,*QueuePtr;

typedef struct linkqueue
{
    /* data */
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;


//init
void initLinkQueue(LinkQueue &LQ){
    LQ.front = LQ.rear = new QNode;
    LQ.front->next = nullptr;//头结点指向空
}

//En
bool EnQueue(LinkQueue &Lq,Element ele){
    //链不需要判断是否满
    QNode *node = new QNode;
    node->data = ele;
    node->next = nullptr;
    Lq.rear->next = node;
    Lq.rear = node;
    return true;

}

//De
bool Dequeue(LinkQueue &Lq,Element &e){
    //判断是否为空
    if(Lq.front == Lq.rear ) return  false;
    QueuePtr P;
    P  = Lq.front->next;
    e = P->data;
    Lq.front->next = P->next;
    if(Lq.rear == P){
        Lq.rear  = Lq.front;
    }
    delete P;
    return true;

}


//status
