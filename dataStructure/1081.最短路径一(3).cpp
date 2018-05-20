/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
万圣节的早上，小Hi和小Ho在经历了一个小时的争论后，终于决定了如何度过这样有意义的一天——他们决定去闯鬼屋！
在鬼屋门口排上了若干小时的队伍之后，刚刚进入鬼屋的小Hi和小Ho都颇饥饿，于是他们决定利用进门前领到的地图，
找到一条通往终点的最短路径。
鬼屋中一共有N个地点，分别编号为1..N，这N个地点之间互相有一些道路连通，两个地点之间可能有多条道路连通，
但是并不存在一条两端都是同一个地点的道路。那么小Hi和小Ho至少要走多少路程才能够走出鬼屋去吃东西呢？

提示：顺序！顺序才是关键。

输入
每个测试点（输入文件）有且仅有一组测试数据。
在一组测试数据中：
第1行为4个整数N、M、S、T，分别表示鬼屋中地点的个数和道路的条数，入口（也是一个地点）的编号，出口（同样也是一个地点）的编号。
接下来的M行，每行描述一条道路：其中的第i行为三个整数u_i, v_i, length_i，表明在编号为u_i的地点和编号为v_i的地点之间有一条
长度为length_i的道路。
对于100%的数据，满足N<=10^3，M<=10^4, 1 <= length_i <= 10^3, 1 <= S, T <= N, 且S不等于T。
对于100%的数据，满足小Hi和小Ho总是有办法从入口通过地图上标注出来的道路到达出口。

输出
对于每组测试数据，输出一个整数Ans，表示那么小Hi和小Ho为了走出鬼屋至少要走的路程。

样例输入
5 23 5 4
1 2 708
2 3 112
3 4 721
4 5 339
5 4 960
1 5 849
2 5 98
1 4 99
2 4 25
2 1 200
3 1 146
3 2 106
1 4 860
4 1 795
5 4 479
5 4 280
3 4 341
1 4 622
4 2 362
2 3 415
4 1 904
2 1 716
2 5 575

样例输出
123

解题思路:
这里使用了bellman_ford算法, 当两个顶点之间存在多条边时, 根据题目只能保留权值最小
或者最大的边, 否则bellman_ford算法无法得到正确的结果. 这样的话, 还需要花费O(V^2)
的时间选出去重后的边.
*/

#include<iostream>
#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXV = 1e3+5;
const int MAXE = 1e4+5;
const int INF = 1<<30;

struct Edge{ int from, to, cost; };

int g[MAXV][MAXV];

Edge edg[MAXE];
int d[MAXV];
int V,E,S,T;

//时间复杂度O(V * E)
//返回值为true时表示没有负环, false时表示有负环, bellman_ford算法无法处理有负环的图
bool bellman_ford()
{
    fill(d, d+V+1, INF);
    int cnt=0;
    d[S] = 0;
    while(true)
    {
        bool update = false;
        ++cnt; //记录循环次数
        for(int i=0; i<E; ++i)
        {
            Edge &e = edg[i];
            if(d[e.from] != INF && d[e.to] > d[e.from] + e.cost)
            {
                d[e.to] = d[e.from] + e.cost;
                update = true;
                if(cnt >= V) return false; //如果第V次循环还有更新, 说明存在负权环.
            }
        }
        if(!update) break;
    }
    return true;
}

int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif

    //注意这看似是有向图，但其实是个无向图，虽然两个点之间可能有多条不同的边相连，
    //但每条路都是可以从一端到达另一端的。
    int u,v,w;
    scanf("%d%d%d%d",&V,&E,&S,&T );
    for(int i=0; i<E; ++i)
    {
        scanf("%d%d%d",&u,&v,&w);
        if(g[u][v] == 0) g[u][v] = g[v][u] = w;
        else g[u][v] = g[v][u] = min(g[u][v], w); //g[u][v]只保存距离最短的边的距离
    }
    
    //选出所有去重后的边, 注意i,j都要重第一个编号开始.
    E = 0;
    for(int i=1; i<=V; ++i)
    {
        for(int j=1; j<=V; ++j)
        {
            if(g[i][j])
            {
                edg[E].from = i;
                edg[E].to = j;
                edg[E].cost = g[i][j];
                ++E;
            }
        }
    }

    bellman_ford();
    printf("%d\n", d[T]);

    return 0;
}