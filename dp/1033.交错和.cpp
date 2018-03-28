/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
给定一个数 x，设它十进制展从高位到低位上的数位依次是 a0, a1, ..., an - 1，定义交错和函数：

f(x) = a[0] - a[1] + a[2] - ... + ( - 1)^(n - 1)*a[n - 1]

例如：

f(3214567) = 3 - 2 + 1 - 4 + 5 - 6 + 7 = 4

给定 l, r, k，求在 [l, r] 区间中，所有 f(x) = k 的 x 的和，即：

1405402477702.png

输入
输入数据仅一行包含三个整数，l, r, k(0 ≤ l ≤ r ≤ 1018, |k| ≤ 100)。

输出
输出一行一个整数表示结果，考虑到答案可能很大，输出结果模 10^9 + 7。


提示
对于样例 ，满足条件的数有 110 和 121，所以结果是 231 = 110 + 121。

更多样例：

Input
4344 3214567 3
Output
611668829

Input
404491953 1587197241 1
Output
323937411

Input
60296763086567224 193422344885593844 10
Output
608746132

Input
100 121 -1
Output
120

样例输入
100 121 0

样例输出
231

解题思路:
做的第一个数位dp的题目，之前看了两次没看懂，这次又看了大半天，在纸上画了一下递归路径，
才慢慢理解了lead_zero 和 limit的作用。
自己写的时候因为把Node里面的n开始写成了int型，查找了半天才发现需要写成long long型才可以。
第二个难以理解的就是合并的式子，这个还是不太懂，不过这个是跟具体问题相关的，不影响代码框架。
参数中的sum表示剩下的数字要凑出的交错和等于sum，所以
dp[pos][dig][sum]表示bits[pos]==dig(或dig+10)，剩下的可以凑出交错和为sum的数字的个数和总和(保存
在结构体中)
*/

#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 1e9+7;

struct Node
{
    LL n; //满足条件的数字的个数
    LL s; //满足条件的数字的和 
    Node(int n=-1,int s=0):n(n),s(s){}
};

int bits[21];
LL base[21];
Node dp[21][20][400];

Node dfs(int pos, int dig, bool lead_zero, bool limit, LL sum)
{
    Node t;
    t.n = t.s = 0; //需要置零，因为默认的n不为0
    //下面这个判断对于该题目是多余的，因为不会有这样的情况发生
    // if(pos < 0 || pos >= 20 || dig < 0 || dig > 9 || sum < -200 || sum >= 200) return t;
    if(!limit && dp[pos][ dig + (lead_zero?0:10) ][sum + 200].n != -1)
        return dp[pos][ dig + (lead_zero?0:10) ][sum + 200];
    if(pos == 0)
    {
        if(dig == sum) t.n = 1, t.s = sum;
        return t;
    }
    int up = limit? bits[pos-1]:9;
    LL newSum = dig - sum;
    Node tmp;
    for(int d=0; d<=up; ++d)
    {
        if(lead_zero)
            tmp = dfs( pos-1, d, d==0, limit && d==up , sum);
        else
            tmp = dfs( pos-1, d, false, limit && d==up, newSum);
        t.n += tmp.n;
        
        t.s = ((t.s + tmp.s) % mod + (tmp.n * dig) % mod * base[pos] % mod) % mod;
    }
    if(!limit) dp[pos][dig +(lead_zero?0:10) ][sum + 200] = t;
    return t;
}


LL solve(LL n, LL sum)
{
    if(n<=0) return 0;
    memset(bits,0,sizeof(bits));
    int pos = 0;
    while(n)
    {
        bits[pos++] = n % 10;
        n /= 10;
    }
    return dfs(pos, 0, true, true, sum).s;
}


int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    LL L,R,S;
    base[0]=1;
    for(int i=1;i<21;++i) base[i] = base[i-1] * 10 % mod;
    cin>>L>>R>>S;
    cout<< ( solve(R,S) - solve(L -1, S) + mod ) % mod <<endl;

    return 0;
}

