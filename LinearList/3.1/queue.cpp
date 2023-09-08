#include<cassert> //宏判断条件是否满足，不满足则终止运行
#define Maxsize 100
typedef int Elemtype;

// define
typedef struct queue
{
    Elemtype elem[Maxsize];
    int front,rear;
    // size 记录队列使用大小
    int size;
    // flag 标记是入队还是出队
    int flag; 
};

//init 
void InitQueue(queue &Q){
    Q.front=Q.rear=0;
}

//destroy
void destroy(queue* Q){
    //先判断是否为空指针
    assert(Q);
    delete Q;
}

// En 
bool EnQueue(queue &Q,int X){
    //判断队列是否已满
    //1. 牺牲一个单元判断队尾指针指向是否是队头指针
    if((Q.rear+1)%Maxsize==Q.front){
        return false;
    }
    //2.判断size,是否等于Maxsize
    if(Q.size == Maxsize){
        return false;
    }
    //3. 利用flag标记，判断入队是否会导致队列已满
    Q.flag =1;
    if(Q.rear == Q.front){
        return false;
    }

    Q.rear = (Q.rear+1)%Maxsize;
    Q.elem[Q.front] = X;
    return true;
}

//De
bool DeQueue(queue &Q,int X){
    //判断是否已空
    if(Q.rear==Q.front){
        return false;
    }
    X = Q.elem[Q.front];
    Q.front = (Q.front+1)%Maxsize;
    return true;
}