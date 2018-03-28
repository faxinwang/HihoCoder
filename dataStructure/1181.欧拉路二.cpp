/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
在上一回中小Hi和小Ho控制着主角收集了分散在各个木桥上的道具，这些道具其实是一块一块骨牌。

week50_1.png

主角继续往前走，面前出现了一座石桥，石桥的尽头有一道火焰墙，似乎无法通过。

小Hi注意到在桥头有一张小纸片，于是控制主角捡起了这张纸片，只见上面写着：

将M块骨牌首尾相连放置于石桥的凹糟中，即可关闭火焰墙。切记骨牌需要数字相同才能连接。
——By 无名的冒险者
小Hi和小Ho打开了主角的道具栏，发现主角恰好拥有M快骨牌。

小Ho：也就是说要把所有骨牌都放在凹槽中才能关闭火焰墙，数字相同是什么意思？

小Hi：你看，每一块骨牌两端各有一个数字，大概是只有当数字相同时才可以相连放置，比如：

week50_2.png

小Ho：原来如此，那么我们先看看能不能把所有的骨牌连接起来吧。

 
提示：Fleury算法求欧拉路径

 
输入
第1行：2个正整数，N,M。分别表示骨牌上出现的最大数字和骨牌数量。1≤N≤1,000，1≤M≤5,000

第2..M+1行：每行2个整数，u,v。第i+1行表示第i块骨牌两端的数字(u,v)，1≤u,v≤N

输出
第1行：m+1个数字，表示骨牌首尾相连后的数字

比如骨牌连接的状态为(1,5)(5,3)(3,2)(2,4)(4,3)，则输出"1 5 3 2 4 3"

你可以输出任意一组合法的解。

样例输入
5 5
3 5
3 2
4 2
3 4
5 1

样例输出
1 5 3 4 2 3

*/

#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 1e3+5;
const int maxm = maxn * 5;

int g[maxn][maxn];
int deg[maxn];
int path[maxm]; //保存欧拉路径
int N,M, top;

void dfs(int u)
{
    for(int v=1; v<=N; ++v)
    {
        if(g[u][v])
        {
            --g[u][v];
            --g[v][u];
            dfs(v);
        }
    }
    path[top++] = u;
}

int main()
{
#ifdef WFX
freopen("in.txt","r", stdin);
#endif
    int u,v, start=1;
    scanf("%d%d", &N, &M);
    while(M--)
    {
        scanf("%d%d",&u,&v);
        ++g[u][v]; ++g[v][u];
        ++deg[u]; ++deg[v];
        if(deg[u] & 1) start = u;
        else if(deg[v] & 1) start = v;
    }
    // int start=1;
    // for(; deg[start]%2==0 && start<N; ++start);
    dfs(start);
    for(int i=0; i<top; ++i) printf("%d ", path[i]); //无向图正向逆向输出均可，有向图要逆向输出

    return 0;
}