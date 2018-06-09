/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
给定一个字符串 S ，最少需要几次增删改操作可以把 S 变成一个回文字符串？
一次操作可以在任意位置插入一个字符，或者删除任意一个字符，或者把任意一个字符修改成任意其他字符。

输入
字符串 S。S 的长度不超过100, 只包含'A'-'Z'。

输出
最少的修改次数。

样例输入
ABAD

样例输出
1

解题思路:
典型的区间模型，回文串拥有很明显的子结构特征，即当字符串X是一个回文串时，在X两边各添加一
个字符'a'后，aXa仍然是一个回文串，我们用d[i][j]来表示A[i...j]这个子串变成回文串所需要
添加的最少的字符数，那么对于A[i] == A[j]的情况，很明显有 d[i][j] = d[i+1][j-1] 
（这里需要明确一点，当i+1 > j-1时也是有意义的，它代表的是空串，空串也是一个回文串，
所以这种情况下d[i+1][j-1] = 0）；当A[i] != A[j]时，我们将它变成更小的子问题求解，
我们有六种决策：
    1.在A[j]后面添加一个字符A[i]    d[i][j] = d[i+1][j] + 1
    2.在A[i]前面添加一个字符A[j]    d[i][j] = d[i][j-1] + 1
    3.删除字符A[i]                 d[i][j] = d[i+1][j] + 1
    4.删除字符A[j]                 d[i][j] = d[i][j-1] + 1
    5.把字符A[i]修改为A[j]         d[i][j] = d[i+1][j-1] + 1
    6.把字符A[j]修改为A[i]         d[i][j] = d[i+1][j-1] + 1
综合得到状态转移方程为：
    d[i][j] = min{ d[i+1][j], d[i][j-1], d[i+1][j-1] } + 1;  

*/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 105;
typedef long long LL;

char s[maxn];
int d[maxn][maxn];

int dp(int i, int j)
{
    if(i >= j) return 0;
    if(d[i][j] >= 0) return d[i][j];
    if(s[i] == s[j]) return d[i][j] = dp(i+1, j-1);
    int ans = maxn;
    ans = min(ans, dp(i+1, j) + 1 ); //在s[j]后面插入s[i],或者删除了s[i]
    ans = min(ans, dp(i, j-1) + 1 ); //在s[i]前面插入s[j],或者删除了s[j]
    ans = min(ans, dp(i+1, j-1) +1 ); //把s[i]修改为s[j] 或 s[j]修改为s[i]
    return d[i][j] = ans;
}

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif
    memset(d, -1, sizeof(d));
    scanf("%s",s);
    printf("%d\n", dp(0, strlen(s)-1) );

    return 0;
}