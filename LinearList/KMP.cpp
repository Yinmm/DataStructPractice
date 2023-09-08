#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include <vector>
using namespace std;
void cal_next(char *str, int *next, int len)
{
    next[0] = -1;//next[0]初始化为-1，-1表示不存在相同的最大前缀和最大后缀
    int k = -1;//k初始化为-1
    for (int q = 1; q <= len-1; q++)
    {
        while (k > -1 && str[k + 1] != str[q])//如果下一个不同，那么k就变成next[k]，注意next[k]是小于k的，无论k取任何值。
        {
            k = next[k];//往前回溯
        }
        if (str[k + 1] == str[q])//如果相同，k++
        {
            k = k + 1;
        }
        next[q] = k;//这个是把算的k的值（就是相同的最大前缀和最大后缀长）赋给next[q]
    }
}


void get_next(int* next,const string s){
    int j = -1;
    next[0] = j;
    for(int i=1;i<s.size();i++){
        while(j>=0&&s[i]!=s[j+1]){
            j = next[j];
            // j--;
        }
        if(s[i]==s[j+1]){
            j++;
        }
        next[i]=j;
    }
}

vector<int> KMP2(string txt,string s){
    vector<int> position;
    int j = -1;
    int *next = new int[s.size()];
    get_next(next,s);
    for(int i=0;i<txt.size();i++){
        while(j>=0&&txt[i]!=s[j+1]){
            j = next[j];
        }
        if(txt[i] == s[j+1]){
            j++;
        }
        if(j == s.size()-1){
            position.push_back(i-s.size()+1);
            cout << "在位置" << i-s.size()+1<< endl;
            j = -1;
            i = i-s.size()+1;
            // return i-s.size()+1;
            
        }
    }
    delete[] next;
    return position;
}





int KMP(char *str, int slen, char *ptr, int plen)
{
    int *next = new int[plen];
    cal_next(ptr, next, plen);//计算next数组
    int k = -1;
    for (int i = 0; i < slen; i++)
    {
        while (k >-1&& ptr[k + 1] != str[i])//ptr和str不匹配，且k>-1（表示ptr和str有部分匹配）
            k = next[k];//往前回溯
        if (ptr[k + 1] == str[i])
            k = k + 1;
        if (k == plen-1)//说明k移动到ptr的最末端
        {
            //cout << "在位置" << i-plen+1<< endl;
            //k = -1;//重新初始化，寻找下一个
            //i = i - plen + 1;//i定位到该位置，外层for循环i++可以继续找下一个（这里默认存在两个匹配字符串可以部分重叠），感谢评论中同学指出错误。
            return i-plen+1;//返回相应的位置
        }
    }
    return -1;  
}

int main(){
    char *str =(char*) "bababacaadababababacacaddababababaca";
    char *ptr =(char*) "ababaca";
    string const txt = "sdaabaafbaaabaafuuuaabaaft";
    string const str1 = "aabaaf";
    // int *next = new int[str1.size()];
    // get_next(next,str1);
    vector<int> result = KMP2(txt, str1);
    if (!result.empty()) {
        cout << "在位置:";
        for (int i : result) {
            cout << " " << i;
    }
    cout << endl;
    } else {
        cout << "未找到匹配位置" << endl;
    }
    system("pause");
    return 0;
}