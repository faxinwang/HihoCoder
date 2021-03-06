/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
在上次安排完相亲之后又过了挺长时间，大家好像都差不多见过面了。不过相亲这个事不是说那么容易的，所以Nettle的姑
姑打算收集一下之前的情况并再安排一次相亲。所以现在摆在Nettle面前的有2个问题：

1.姑姑想要了解之前所有相亲的情况。对于任一个一次相亲，只要跟参与相亲的两人交流就可以得到这次相亲的情况。如果一
个人参加了多次相亲，那么跟他交流就可以知道这几次相亲的情况。那么问题来了，挖掘技术到底哪家强姑姑最少需要跟多少
人进行交流可以了解到所有相亲的情况。

----------------------------------------------------------------
问题1解答
同样的转化为图G=(V,E)，则问题转化为：
在图G中选取尽可能少的点，使得图中每一条边至少有一个端点被选中。
这个问题在二分图问题中被称为最小点覆盖问题。即用最少的点去覆盖所有的边。
结论：由König定理可知最小点覆盖的点数 = 二分图最大匹配
----------------------------------------------------------------

2.因为春节快要结束了，姑姑打算给这些人再安排一次集体相亲。集体相亲也就是所有人在一起相亲，不再安排一对一对的进
行相亲。但是姑姑有个条件，要求所有参与相亲的人之前都没有见过。也就是说在之前的每一次相亲中的两人不会被同时邀请
来参加这次集体相亲。那么问题又来了，姑姑最多可以让多少人参与这个集体相亲。

----------------------------------------------------------------
问题2解答
依旧转化为图G=(V,E)，则问题转化为：
在图G中选取尽可能多的点，使得任意两个点之间没有连边。
这个问题在二分图问题中被称为最大独立集问题。
结论：最大独立集的点数 = 总点数 - 二分图最大匹配
证明：
假设最大独立集的点数为|U|，二分图最大匹配的匹配数为|M|，最大匹配中所有顶点集合为EM
先证明 |U|≤|V|-|M|
M中任意一条边的两个端点是连接的，所有对于M中的边必有一个端点不在|U|集合中，所以|M|≤|V|-|U|
再证明|U|≥|V|-|M|
首先我们知道一定有|U|≥|V|-|EM|，即将最大匹配的点删除之后，剩下的点一定都不相连。
接下来我们考虑能否将M集合中的一个端点放入U中：
假设(x,y)属于M，存在(a,x),(b,y)，且a,b都在U中，则会出现两种情况：

如果(a,b)连接，则有一个更大的匹配存在，矛盾
如果(a,b)不连接，a->x->y->b有一个新的增广路，因此有一个更大的匹配，矛盾

故有a,b两点中至多只有1个点属于U，则我们总是可以选取x,y中一个点放入集合U
所以|U|≥|V|-|EM|+|M|=|V|-|M|

综上有|U|=|V|-|M|
----------------------------------------------------------------

输入
第1行：2个正整数，N,M(N表示点数 2≤N≤1,000，M表示边数1≤M≤5,000)
第2..M+1行：每行两个整数u,v，表示一条无向边(u,v)

输出
第1行：1个整数，表示最小点覆盖数
第2行：1个整数，表示最大独立集数

样例输入
5 4
3 2
1 3
5 4
1 5

样例输出
2
3

解题思路：
相关知识：http://dsqiu.iteye.com/blog/1689505

三个重要的性质： 
1. 由König定理可知最小点覆盖的点数 = 二分图最大匹配 
  König 定理是一个二分图中很重要的定理，它的意思是，一个二分图中的最大匹配数等于这个图中的最小点覆盖数。如果你还不知
  道什么是最小点覆盖，我也在这里说一下：假如选了一个点就相当于覆盖了以它为端点的所有边，你需要选择最少的点来覆盖所有
  的边。 
2. 最大独立集的点数 = 总点数 - 二分图最大匹配 
  独立集：图中任意两个顶点都不相连的顶点集合。 
3. 最小路径覆盖＝｜G｜－最大匹配数 
  在一个 N*N 的有向图中，路径覆盖就是在图中找一些路经，使之覆盖了图中的所有顶点，且任何一个顶点有且只有一条路径与之关
  联；（如果把这些路径中的每条路径从它的起始点走到它的终点，那么恰好可以经过图中的每个顶点一次且仅一次）；如果不考虑
  图中存在回路，那么每条路径就是一个弱连通子集． 

由上面可以得出： 
1.一个单独的顶点是一条路径； 
2.如果存在一路径 p1,p2,……pk，其中 p1 为起点，pk 为终点，那么在覆盖图中，顶点 p1,p2,……pk 不再与其它的顶点之间存在
  有向边．最小路径覆盖就是找出最小的路径条数，使之成为 G 的一个路径覆盖． 
  路径覆盖与二分图匹配的关系：最小路径覆盖＝｜G｜－最大匹配数；

*/

#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
const int maxn = 1e3+5;

vector<int> g[maxn];
int vis[maxn];
int match[maxn];

int Find(int u)
{
    // vis[u] = 1;
    for(int i=0,n=g[u].size(); i<n; ++i)
    {
        int v = g[u][i];
        if(!vis[v])
        {
            vis[v] = 1;
            if(!match[v] || Find(match[v]))
            {
                match[u] = v;
                match[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int solve(int N)
{
    int ans = 0;
    for(int i=1; i<=N; ++i) if(!match[i])
    {
        memset(vis,0,sizeof(vis));
        ans += Find(i);
    }
    return ans;
}

int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    int N,M;
    int u,v;
    scanf("%d%d",&N,&M);
    for(int i=0;i<M; ++i)
    {
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int ans = solve(N);
    printf("%d\n%d", ans, N - ans);

    return 0;
}