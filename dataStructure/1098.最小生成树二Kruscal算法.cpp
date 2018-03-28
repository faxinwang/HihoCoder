/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
随着小Hi拥有城市数目的增加，在之间所使用的Prim算法已经无法继续使用了——但是幸运的是，经过计算机的分析，
小Hi已经筛选出了一些比较适合建造道路的路线，这个数量并没有特别的大。

所以问题变成了——小Hi现在手上拥有N座城市，且已知其中一些城市间建造道路的费用，小Hi希望知道，最少花费多
少就可以使得任意两座城市都可以通过所建造的道路互相到达（假设有A、B、C三座城市，只需要在AB之间和BC之间
建造道路，那么AC之间也是可以通过这两条道路连通的）。

提示：积累的好处在于可以可以随时从自己的知识库中提取想要的！

输入
每个测试点（输入文件）有且仅有一组测试数据。
在一组测试数据中：
第1行为2个整数N、M，表示小Hi拥有的城市数量和小Hi筛选出路线的条数。
接下来的M行，每行描述一条路线，其中第i行为3个整数N1_i, N2_i, V_i，分别表示这条路线的两个端点和在这条路线上
建造道路的费用。
对于100%的数据，满足N<=10^5, M<=10^6，于任意i满足1<=N1_i, N2_i<=N, N1_i≠N2_i, 1<=V_i<=10^3.
对于100%的数据，满足一定存在一种方案，使得任意两座城市都可以互相到达。

输出
对于每组测试数据，输出1个整数Ans，表示为了使任意两座城市都可以通过所建造的道路互相到达至少需要的建造费用。

样例输入
5 29
1 2 674
2 3 249
3 4 672
4 5 933
1 2 788
3 4 147
2 4 504
3 4 38
1 3 65
3 5 6
1 5 865
1 3 590
1 4 682
2 4 227
2 4 636
1 4 312
1 3 143
2 5 158
2 3 516
3 5 102
1 5 605
1 4 99
4 5 224
2 4 198
3 5 894
1 5 845
3 4 7
2 4 14
1 4 185

样例输出
92

解题思路：
kruskal算法比Prim算法要好理解一些，算法过程如下:
首先将具有N个顶点的图看成是N棵只有单个结点的树，然后算法每次从所有的边中取出权值最小的一条边，
如果将该边加入生成树不会造成回路，就将该边添加到图中去，将两颗独立的树连接成一棵树,加入该边后就
剩下N-1棵树; 否则取出下一条权值最小的边。继续重复上述操作， 直到加入了N-1条边到生成树中为止，
此时图中只剩下一颗具有N个结点的树，此树即为该图的最小生成树.

时间复杂度：
设图中边的总数为E,则：
优先级队列的pop()和push()操作都需要Log(E),所以将E条边全部放入优先级队列需要ELog(E)的时间。
Find() 和 Union()可以看成是O(1)的操作。在Kruskal算法中，外层循环用于选择N-1条边,所以至少循环
N-1次，上限是E次，所以外层循环次数是N-1~E次，假设循环次数为K(N-1 <= k < E), 循环内每次pop()出一
条边需要Log(E)的时间，所以算法总共需要 ELog(E) + KLog(E) 的时间，所以kruskal算法的时间复杂度为
ELog(E).

空间复杂度：
算法需要存储所有的边和一个元素个数为结点数N的并查集，所以空间复杂度为O(E).
*/

#include<iostream>
#include<cstdio>
#include<queue>
#include<functional> // greater<>, also included in algorithm,iostream,etc.
using namespace std;
const int maxn = 1e5+5;

struct Edge
{
    int u,v,w;
    Edge(int u,int v,int w):u(u),v(v),w(w){}
    /*
    // bool operator<(const Edge& e)const{return w < e.w &&(u!=e.u || v!=e.v); }
    这样写判断条件，可以避免在set中具有相同权值的不同边被错误去重的情况。
    但时又带来了新的问题，就是相同的边只会插入第一次出现的一条而不是边权最小的一条，这显然会导致错误。
    其他的办法是先用链接矩阵保存图，每次加入边的时候只保存最短的边，但是为了这一点点的优化却要增加O(N^2)
    的空间复杂度，感觉不是很划算，所以干脆使用优先队列来的方便。
    */
    //使用小根堆，需要重载大于号
    bool operator>(const Edge& e)const{ return w > e.w ; }
};
priority_queue<Edge, deque<Edge>, greater<Edge> > Q; 
int p[maxn]; //并查集

int Find(int x)
{
    if(p[x] == 0) return x;
    return p[x] = Find(p[x]);
}

void Union(int u,int v)
{
    // int pu = Find(u);
    // int pv = Find(v);
    // if(pu != pv) p[pu] = pv;
    p[u] = v;
}

int kruskal(int N)
{
    int res = 0;
    while(N>1) //N个点只需要N-1条边构成生成树
    {
        Edge e = Q.top(); Q.pop();
        int pu = Find(e.u);
        int pv = Find(e.v);
        if(pu != pv) //两颗子树合并成一颗大树
        {
            Union(pu,pv);
            res += e.w;
            --N;
        }
    }
    return res;
}

int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    int N,M;
    int u,v,w;
    scanf("%d%d",&N,&M);
    for(int i=0; i<M; ++i)
    {
        scanf("%d%d%d",&u,&v,&w);
        Q.push(Edge(u,v,w));
    }

    printf("%d\n", kruskal(N));

    return 0;
}