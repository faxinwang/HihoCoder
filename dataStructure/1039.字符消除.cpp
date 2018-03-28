/*
时间限制:1000ms
单点时限:1000ms
内存限制:256MB

描述
小Hi最近在玩一个字符消除游戏。给定一个只包含大写字母"ABC"的字符串s，消除过程是如下进行的：

1)如果s包含长度超过1的由相同字母组成的子串，那么这些子串会被同时消除，余下的子串拼成新的字符串。
例如"ABCCBCCCAA"中"CC","CCC"和"AA"会被同时消除，余下"AB"和"B"拼成新的字符串"ABB"。

2)上述消除会反复一轮一轮进行，直到新的字符串不包含相邻的相同字符为止。例如”ABCCBCCCAA”经过一轮
消除得到"ABB"，再经过一轮消除得到"A"

游戏中的每一关小Hi都会面对一个字符串s。在消除开始前小Hi有机会在s中任意位置(第一个字符之前、最后
一个字符之后以及相邻两个字符之间)插入任意一个字符('A','B'或者'C')，得到字符串t。t经过一系列消
除后，小Hi的得分是消除掉的字符的总数。

请帮助小Hi计算要如何插入字符，才能获得最高得分。

输入
输入第一行是一个整数T(1<=T<=100)，代表测试数据的数量。

之后T行每行一个由'A''B''C'组成的字符串s，长度不超过100。

输出
对于每一行输入的字符串，输出小Hi最高能得到的分数。

提示
第一组数据：在"ABCBCCCAA"的第2个字符后插入'C'得到"ABCCBCCCAA"，消除后得到"A"，总共消除9个
字符(包括插入的'C')。
第二组数据："AAA"插入'A'得到"AAAA"，消除后得到""，总共消除4个字符。
第三组数据：无论是插入字符后得到"AABC","ABBC"还是"ABCC"都最多消除2个字符。

样例输入
3
ABCBCCCAA
AAA
ABC

样例输出
9
4
2

解题思路：
1.在字符串的n+1(包括第一个字符前面和最后一个字符后面)分别插入A,B,C然后进行消除，也就是纯粹的暴力尝试。
2.在消除的时候，只需要提取不需要消除的字符组装成一个新字符返回即可。
3.如果返回的新字符比原来的短，则可能可以继续消除，否则不可以继续消除。
4.源字符串的长度加1(插入了一个字符)再减去消除过程中最短字符串的长度就是消除的字符个数，也就是所得到的分数。
*/


#include<bits/stdc++.h>
using namespace std;

string eliminate(string s)
{
    int n = s.size();
    if(n == 1) return s; //如果只有一个字符，则不可消除，直接返回
    string res;
    if(s[0] != s[1]) res += s[0];
    for(int i=1; i<n-1; ++i)
    {
        if(s[i] != s[i-1] && s[i] != s[i+1]) res += s[i];
    }
    if(s[n-1] != s[n-2]) res += s[n-1];
    // cout<<s<<"---->"<<res<<endl;
    return res;
}

int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    int T;
    scanf("%d",&T);
    char tmp[]={"ABC"};
    while(T--)
    {
        string s;
        cin>>s;
        int maxLen = s.size(), minLen = maxLen,Len;
        for(int i=0; i<=maxLen; ++i)
        {
            for(int j=0; j<3;++j)
            {
                string t = s.substr(0,i) + tmp[j] + s.substr(i);
                int Len = t.size();
                t = eliminate(t);
                while(Len > t.size())
                {
                    Len = t.size();
                    t = eliminate(t);
                }
                if(minLen > Len) minLen = Len;
            }

            /*
            下面这种写法wa了,
            比如 ABB 
            按照下面的写法得到的字符串是ABBB, 然后只能消除三个，
            但时如果在末尾添加字符A得到ABBA，则同通过两次全部消除.
            */
            // string t;
            // if(i == 0)              t = s[0] + s;
            // else if(i == maxLen)    t = s + s[maxLen-1];
            // else                    t  = s.substr(0,i) + s[i-1] + s.substr(i);
            // int Len = t.size();
            // t = eliminate(t);
            // while(Len > t.size())
            // {
            //     Len = t.size();
            //     t = eliminate(t);
            // }
            // if(minLen > Len) minLen = Len;
        }
        //插入了一个字符，所以长度加1
        printf("%d\n", maxLen + 1 - minLen);
    }


    return 0;
}