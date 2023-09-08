#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
typedef int ElemType;

#define MAXSIZE 100

struct Book
{
    string id;
    string name;
    double price;

};

typedef struct
{
    /* data */
    Book *elem;
    int length;
}SqList;  //定义顺序表

// 初始化空表
Status InitList(SqList &L){
    L.elem = new Book[MAXSIZE];
    if(!L.elem) exit(OVERFLOW);
    L.length=0;
    return OK;

}

// 取值
Status getElem(SqList &L,int i,Book &b){
    if(i<1||i>L.length) return ERROR;
    b = L.elem[i-1];
    return OK;
}

// 查找
int searchElem(SqList &L, string name){
    for(int i=0;i<L.length;i++){
        if(L.elem[i].name == name) return i+1; //返回第几位
    }
    return 0;
}

// 插入
Status insert(SqList &L,int i,Book &b){ //在第i个位置插入新元素
    if(i<1||i>L.length) return ERROR;
    if(L.length==MAXSIZE) return ERROR;
    for(int j=L.length-1;j>=i-1;j--){
        L.elem[j+1]=L.elem[j];
    }
    L.elem[i-1] = b;
    L.length++;
    return OK;
}

// 删除
Status dellist(SqList &L, int i){ //删除第i位的元素
    if(i<1||i>L.length) return ERROR;
    for(int j =i-1;j<L.length-2;j++){
        L.elem[j] = L.elem[j+1];
    }
    L.length--;
    return OK;
}

int main(){
    SqList list;
    Status status = InitList(list);
    if(status == OK){
         cout << "顺序表初始化成功" << endl;
    }else{
        cout << "顺序表初始化失败" << endl;
    }
    Book book1;
    book1.id = "1234";
    book1.name = "英语";
    book1.price = 12.5;
    // 插入数据到表
    list.elem[list.length] = book1;
    list.length++;
    // 取值
    Book b2;
    getElem(list,1,b2);
    cout << "b2_id:" << b2.id << endl;

    //查找
    string testname = "英语";
    int result = searchElem(list,testname);
    if(result !=0){
        cout << "查询到英语位于第"<<result<<"位" << endl;
    }
    else{
        cout << "没有查询到该内容";
    }
    Book B2;
    B2.id="2345";
    B2.name = "语文";
    B2.price = 11.2;
    list.elem[list.length] =B2;
    list.length++;
    Book B3;
    B3.id="3456";
    B3.name = "数学";
    B3.price = 16.2;
    list.elem[list.length] = B3;
    list.length++;

    //第i位 插入
    Book Bi;
    Bi.id = "9527";
    Bi.name = "数据结构";
    Bi.price = 9.9;
    Status result2 = insert(list,2,Bi);
    if(result2 !=OK){
        cout << "插入失败"<<endl;
    }else{
        cout << "插入成功"<<endl;
    }


    //第i位，删除
    Status result3 = dellist(list,4);
    if(result3 !=OK){
        cout << "删除失败"<<endl;
    }else{
        cout << "删除成功"<<endl;
    }
    Book *p;
    //打印列表
    for(int i=0;i<list.length;i++){
        cout<<list.elem[i].name<<endl;
        p = list.elem+i;
        cout<<p<<endl;
        // cout<<p->name<<endl;
    }

    system("pause");
}