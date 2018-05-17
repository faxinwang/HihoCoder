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

解题思路：
在链接矩阵实现的dijkstra算法中, 外层循环用于固化所有V个顶点. 内层循环中,有一个O(V)的内层循
环用于寻找离源点距离最小的待松弛的顶点u, 还有一个O(V)的内层循环用于松弛所有与u相邻的顶点v.

如果dijkstra算法用链接表实现, 则内层循环中用于进行松弛操作的循环可以变得的很小( O(G[u].size()) ), 
但因为内层循环中还有一个O(V)的循环用于寻找离源点距离最小的待松弛的顶点.故总时间复杂度还是O(V^2)

我们可以用堆优化从内层循环中寻找离源点距离最小的顶点的过程, 每次从堆中取出离源点距离最小的元素后, 如果该点
到源点的距离没有被松弛过, 则该点没有利用价值, 可以直接抛弃, 如果该点到源点的距离被松弛过, 则与该点相连的点
到源点的距离可能因为该点而变得更小. 因此需要将该点加入到堆中. 这样, 堆中元素的数目为O(V), 从堆中取出和插入
元素的次数为O(E), 因此总的时间复杂度降到了O(E log V), 算法变得非常高效了.

使用堆优化的dijkstra算法依然无法处理存在负权边的图.
*/


#include<iostream>
#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn = 1e3+5;
const int INF = 1<<30;

typedef pair<int,int> Pair; //first保存到源点的距离, second保存顶点的编号
struct Edge
{
    int to, cost; 
    Edge(int t=0,int c=0):to(t),cost(c){}
};

vector<Edge> G[maxn];
int d[maxn];
// int p[maxn]; //记录前驱结点
int V,E,S,T;

//时间复杂度O(V log (E))
void opt_dijkstra()
{
    fill(d, d + V + 1, INF);
    priority_queue<Pair,vector<Pair>, greater<Pair> > Q;
    d[S] = 0;
    Q.push(Pair(0,S)); //将源点和其最短距离放进优先队列
    while(!Q.empty())
    {
        Pair p = Q.top(); Q.pop();
        int u = p.second;
        if(d[u] < p.first) continue;
        for(int i=0, n=G[u].size(); i<n; ++i)
        {
            Edge &e = G[u][i];
            if(d[e.to] > d[u] + e.cost)
            {
                d[e.to] = d[u] + e.cost;
                Q.push(Pair(d[e.to], e.to));
            }
        }
    }
}

int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    int u,v,w;
    scanf("%d%d%d%d",&V,&E,&S,&T );
    //注意这看似是有向图，但其实是个无向图，虽然两个点之间可能有多条不同的边相连，
    //但每条路都是可以从一端到达另一端的。
    for(int i=1; i<=E; ++i)
    {
        scanf("%d%d%d",&u,&v,&w);
        G[u].push_back(Edge(v,w));
        G[v].push_back(Edge(u,w));
    }
    opt_dijkstra();
    printf("%d\n", d[T]);

    return 0;
}