/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
恺撒密码是一种古老的加密方法。它将26个英文字母'A'-'Z'向左循环移动K位，得到新的密码表。

例如K=2，有:

ABCDEFGHIJKLMNOPQRSTUVWXYZ
CDEFGHIJKLMNOPQRSTUVWXYZAB
则用'C'替代'A'，'D'替代'B'……  

对于两个只包含大写字母的字符串A和B，如果A和B长度相同，并且A可以通过某种(某个K)恺撒加密得到B，
我们就认为A和B是相似的。

例如"ABC"与"DEF"相似，"HI"与"ZA"相似。显然"相似"关系具有传递性和对称性。    

给定N个字符串，请你将相似的字符串聚成一类，并输出最终有几个不同的类别。

输入
第一行包含一个整数N。  
以下N行每行包含一个字符串S。S只包含大写字母。  
对于50%的数据，1 ≤ N ≤ 100，N个字符串总长度不超过10000。  
对于100%的数据，1 ≤ N ≤ 100000，N个字符串总长度不超过1000000。

输出
一个整数表示答案。

样例输入
6  
ABC
DEF  
ZAB  
HIHO  
JKJQ  
NONU

样例输出
2

解题思路： 
将所有字符串旋转到第一个字符为'A'并放入set以去重, 最后set中元素的个数就是
不同类别字符串的个数。 
*/
#include<iostream>
#include<cstdio>
#include<string>
#include<set>
using namespace std;


int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    int N;
    string str;
    set<string> s;
    scanf("%d",&N);
    while(N--)
    {
        cin>>str;
        int offset = str[0] - 'A';
        for(int i=0,n=str.size(); i<n; ++i) str[i] = (str[i] -  offset + 26) % 26;
        s.insert(str);
    }
    cout<<s.size()<<endl;

    return 0;
}
