/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
我们有一个字符串集合S，其中有N个两两不同的字符串。

还有M个询问，每个询问给出一个字符串w，求有多少S中的字符串可以由w添加恰好一个字母得到。

字母可以添加在包括开头结尾在内的任意位置，比如在"abc"中添加"x"，就可能得到"xabc", "axbc", 
"abxc", "abcx".这4种串。

输入
第一行两个数N和M，表示集合S中字符串的数量和询问的数量。
接下来N行，其中第i行给出S中第i个字符串。
接下来M行，其中第i行给出第i个询问串。
所有字符串只由小写字母构成。

数据范围：
N,M<=10000。
S中字符串长度和<=100000。
所有询问中字符串长度和<=100000。

输出
对每个询问输出一个数表示答案。

样例输入
3 3
tourist
petr
rng
toosimple
rg
ptr

样例输出
0
1
1

解题思路：
设a为集合S中可以通过w添加一个字符而得到的字符串，则a的长度必定比w的长度大1
然后从两个字符串的第一个字符开始比较，如果a[i] != w[j] ,则跳过a的第i个字符继续比较，
如果还有不相同的字符，则说明a不能通过w添加一个字符而得到。
*/

#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
const int maxn = 10000;

string s[maxn];

//检查a是否能通过w添加一个字符而得到
bool check(string& a, string& w)
{
    int diff = 0;
    int n1=a.size(), n2=w.size();
    for(int i=0,j=0; i<n1 && j<n2; ++i, ++j)
    {
        if(a[i] != w[j])
        {
            ++i;
            if(++diff > 1) break;
        }
    }
    return diff <= 1; //diff=0表示在w的末尾添加一个字符即可
}

int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    string w;
    int N,M;
    scanf("%d%d",&N,&M);
    for(int i=0; i<N; ++i) cin>>s[i];
    for(int j=0; j<M; ++j)
    {
        cin>>w;
        int ans = 0;
        for(int i=0; i<N; ++i)
        {
            if(s[i].size() - w.size() != 1) continue;
            ans += check(s[i], w)? 1 : 0;
        }
        printf("%d\n",ans);
    }

    return 0;
}