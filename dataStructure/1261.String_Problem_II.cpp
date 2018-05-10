/*
时间限制:50000ms
单点时限:5000ms
内存限制:512MB
描述
我们有一个字符串集合S，其中有N个两两不同的字符串。还有M个询问，每个询问都会先给出一个字符串w，
你需要回答以下三个问题：
1. 输出所有S的串中，可以由w恰好添加两个字符得到的串中，编号最小的3个。
2. 输出所有S的串中，可以由w修改不超过2个字符得到的串中，编号最小的3个。
3. 输出所有S的串中，可以由w删除恰好两个字符得到的串中，编号最小的3个。
字母可以添加在包括开头结尾在内的任意位置，比如在"abc"中添加"x"和"y"，可能可以得到"yxabc"，"aybxc"，
"axbyc"等等的串。

所有字符串只由小写字母构成。

输入
第一行两个数N和M，表示集合S中字符串的数量和询问的数量。
接下来N行，其中第i行给出S中第i个字符串。第i个字符串的编号就是i。
接下来M行，其中第i行给出第i个询问串。
数据范围：
N,M<=10000。
S中字符串长度和<=100000。
所有询问中字符串长度和<=100000。

输出
对每个询问输出三行，每行三个数，分别表示每个问题编号最小的3个串的编号，从小到大排列。
如果不到3个串，则在最后用-1补到3个输出，比如如果结果是1和2，那么输出1 2 -1，如果S中没有满足条件的串，
就输出-1 -1 -1。

样例输入
5 5
dsxmlkxp
asxglqkdxp
asxgavxp
asxglp
sxglkx
kebvpyky
hjpntqft
asxglkxp
polbmzgq
jdczlmtd

样例输出
-1 -1 -1
-1 -1 -1
-1 -1 -1
-1 -1 -1
-1 -1 -1
-1 -1 -1
2 -1 -1
1 3 -1
4 5 -1
-1 -1 -1
-1 -1 -1
-1 -1 -1
-1 -1 -1
-1 -1 -1
-1 -1 -1

解题思路:
第三个问题与第一个问题其实是同一种问题，判断字符串a是否可以通过w添加恰好2个字符得到，
算法思想比较简单，但不是很好描述，看代码应该能看懂(见add2())。

第二个问题，两个字符串a和w的长度必须相等，然后逐个比较对应位置的字符，如果对应位置不相同字符
的个数大于2个，则a不能通过w修改2个字符得到。
*/


#include<iostream>
#include<cstdio>
#include<string>
#include<sstream>
using namespace std;
const int maxn = 10000;

string s[maxn];

//检查a是否能通过w添加 "恰好" 2个字符而得到
bool add2(string& a, string& w)
{
    int n1=a.size(), n2=w.size();
    if(n1 - n2 != 2) return false;
    int diff = 0, i, j;
    for(i=0,j=0; i<n1 && j<n2;)
    {
        if(a[i] != w[j])
        {
            ++i;
            if( ++diff > 2 ) return false; //不同字符的个数大于2
        }
        else
        {
            ++i, ++j;
        }
    }
    diff += n1 - i; //添加a末尾多余字符的个数
    return diff==2; 
}

//检查a是否能通过w修改 "不超过" 两个字符而得到, 注意修改的是相同位置的字符
bool change2(string& a, string& w)
{
    int n1=a.size(), n2=w.size();
    if(n1 != n2) return false;
    int diff = 0;
    for(int i=0; i<n1; ++i )
    {
        if(a[i] != w[i] && ++diff > 2) return false;
    }
    return true;
}


int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    string w;
    int N,M;
    scanf("%d%d",&N,&M);
    for(int i=1; i<=N; ++i) cin>>s[i];
    for(int j=0; j<M; ++j)
    {
        cin>>w;
        int cnt_add = 3, cnt_change=3, cnt_del=3;
        stringstream add, change, del;
        for(int i=1; i<=N; ++i)
        {
            if( add2( s[i], w ) && cnt_add )
            {
                --cnt_add;
                add<<i<<" ";
            } 
            else if( add2(w, s[i]) && cnt_del ){
                --cnt_del;
                del<<i<<" ";
            } 
            else if( change2(s[i], w) && cnt_change ){
                --cnt_change;
                change<<i<<" ";
            }
        }
        while(cnt_add--) add<<"-1 ";
        while(cnt_change--) change<<"-1 ";
        while(cnt_del--) del<<"-1 ";

        cout<<add.str()<<endl;
        cout<<change.str()<<endl;
        cout<<del.str()<<endl;
    }

    return 0;
}