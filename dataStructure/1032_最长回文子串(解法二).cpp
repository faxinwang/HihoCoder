/*
时间限制:1000ms
单点时限:1000ms
内存限制:64MB
描述
   小Hi和小Ho是一对好朋友，出生在信息化社会的他们对编程产生了莫大的兴趣，他们约定好互相帮助，在编程的学习道路上一同前进。
   这一天，他们遇到了一连串的字符串，于是小Hi就向小Ho提出了那个经典的问题：“小Ho，你能不能分别在这些字符串中找到它们每一
   个的最长回文子串呢？”

   小Ho奇怪的问道：“什么叫做最长回文子串呢？”

   小Hi回答道：“一个字符串中连续的一段就是这个字符串的子串，而回文串指的是12421这种从前往后读和从后往前读一模一样的字符串，
   所以最长回文子串的意思就是这个字符串中最长的身为回文串的子串啦~”

   小Ho道：“原来如此！那么我该怎么得到这些字符串呢？我又应该怎么告诉你我所计算出的最长回文子串呢？

   小Hi笑着说道：“这个很容易啦，你只需要写一个程序，先从标准输入读取一个整数N（N<=30)，代表我给你的字符串的个数，然后接
   下来的就是我要给你的那N个字符串（字符串长度<=10^6)啦。而你要告诉我你的答案的话，只要将你计算出的最长回文子串的长度按
   照我给你的顺序依次输出到标准输出就可以了！你看这就是一个例子。”


样例输入
3
abababa
aaaabaa
acacdas

样例输出
7
5
3

解题思路：
参考：https://www.cnblogs.com/xcw0754/p/4442652.html
*/

#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 1e6+5;

char s1[maxn];  //保存原串
char s2[maxn*2]; //做了插入处理的结果串
int p[maxn*2]; //保存关于长度的信息（回文长度的一半再加1）

int manacher(char* s){
    int id=1,mx=1,ans=1;
    p[0] = p[1] = 1;
    for(int i=2; s[i]; ++i){
        p[i] = i > id + p[id] ? 1 : min(p[2 * id - i], id + p[id] - i);
        while(s[ i - p[i] ] == s[ i + p[i] ]) ++p[i];
        if(i + p[i] > id +  p[id])  id = i;
        if(mx < p[i]) mx = p[i];
    }
    return mx-1;
}

int main(){
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%s",s1);
        int k=0;
        s2[k++]='@';
        s2[k++]='#';
        for(int i=0; s1[i]; ++i){
            s2[k++] = s1[i];
            s2[k++] = '#';
        }
        s2[k] = 0;
        memset(p,0,sizeof(p));
        printf("%d\n",manacher(s2));
    }

    return 0;
}