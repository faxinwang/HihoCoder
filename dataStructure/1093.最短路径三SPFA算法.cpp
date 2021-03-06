/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
万圣节的晚上，小Hi和小Ho在吃过晚饭之后，来到了一个巨大的鬼屋！

鬼屋中一共有N个地点，分别编号为1..N，这N个地点之间互相有一些道路连通，两个地点之间可能有多条道路连通，
但是并不存在一条两端都是同一个地点的道路。

不过这个鬼屋虽然很大，但是其中的道路并不算多，所以小Hi还是希望能够知道从入口到出口的最短距离是多少？

-------------------------------------------------------------
提示：Super Programming Festival Algorithm。
“唔……地点很多，道路很少，这个鬼屋是一个稀疏图，既然这一点被特地标注出来，那么想来有其作用的咯？”小Ho道。

“是的，正好有一种最短路径算法，它的时间复杂度只和边的条数有关，所以特别适合用来解决这种边的数量很少的最
短路问题！”小Hi点了点头道：“它就是SPFA算法，即Shortest Path Faster Algorithm。”

“听上去很厉害的样子，但是实际上怎么做的呢？”小Ho问道。

“你会用宽度优先搜索写这道题么？”小Hi反问道。

“这个当然会啊，构造一个队列，最开始队列里只有(S, 0)——表示当前处于点S，从点S到达该点的距离为0，然后每
次从队首取出一个节点(i, L)——表示当前处于点i，从点S到达该点的距离为L，接下来遍历所有从这个节点出发的边
(i, j, l)——表示i和j之间有一条长度为l的边，将(j, L+l)加入到队尾，最后看所有遍历的(T, X)节点中X的最小
值就是答案咯~”小Ho对于搜索已经是熟稔于心，张口便道。

“SPFA算法呢，其实某种意义上就是宽度优先搜索的优化——如果你在尝试将(p, q)加入到队尾的时候，发现队列中
已经存在一个(p, q')了，那么你就可以比较q和q'：如果q>=q'，那么(p, q)这个节点实际上是没有继续搜索下
去的必要的——算是一种最优化剪枝吧。而如果q<q'，那么(p, q')也是没有必要继续搜索下去的——但是它已经存在
于队列里了怎么办呢？很简单，将队列中的(p, q')改成(p, q)就可以了！”

“那我该怎么知道队列中是不是存在一个(p, q')呢？”<额，维护一个position[1..N]的数组就可以了，如果不在队
列里就是-1，否则就是所在的位置！”

“所以说这本质上就是宽度优先搜索的剪枝咯？”小Ho问道。

小Hi笑道：“怎么可能！SPFA算法其实是BELLMAN-FORD算法的一种优化版本，只不过在成型之后可以被理解成为宽
度优先搜索的！这个问题，我们会在之后好好讲一讲的！”
-------------------------------------------------------------

输入
每个测试点（输入文件）有且仅有一组测试数据。
在一组测试数据中：
第1行为4个整数N、M、S、T，分别表示鬼屋中地点的个数和道路的条数，入口（也是一个地点）的编号，出口（同样也是一个地点）
的编号。接下来的M行，每行描述一条道路：其中的第i行为三个整数u_i, v_i, length_i，表明在编号为u_i的地点和编号为
v_i的地点之间有一条长度为length_i的道路。
对于100%的数据，满足N<=10^5，M<=10^6, 1 <= length_i <= 10^3, 1 <= S, T <= N, 且S不等于T。
对于100%的数据，满足小Hi和小Ho总是有办法从入口通过地图上标注出来的道路到达出口。

输出
对于每组测试数据，输出一个整数Ans，表示那么小Hi和小Ho为了走出鬼屋至少要走的路程。

样例输入
5 10 3 5
1 2 997
2 3 505
3 4 118
4 5 54
3 5 480
3 4 796
5 2 794
2 5 146
5 4 604
2 5 63

样例输出
172

解题思路：
参考：http://www.cnblogs.com/devtang/archive/2011/08/25/spfa.html

SPFA(Shortest Path Faster Algorithm)是Bellman-Ford算法的一种队列实现，减少了不必要的冗余计算。
算法大致流程是用一个队列来进行维护。 初始时将源加入队列。 每次从队列中取出一个元素，并对所有与他相
邻的点进行松弛，若某个相邻的点松弛成功，则将其入队。 直到队列为空时算法结束。这个算法，简单的说就是
队列优化的bellman-ford,利用了每个点不会更新次数太多的特点发明的此算法

SPFA——Shortest Path Faster Algorithm，它可以在O(kE)的时间复杂度内求出源点到其他所有点的最短路径，
可以处理负边。SPFA的实现甚至比Dijkstra或者Bellman_Ford还要简单：设Dist代表S到I点的当前最短距离，
Fa代表S到I的当前最短路径中I点之前的一个点的编号。开始时Dist全部为+∞，只有Dist[S]=0，Fa全部为0。
维护一个队列，里面存放所有需要进行迭代的点。初始时队列中只有一个点S。用一个布尔数组记录每个点是否处在队列中。
每次迭代，取出队头的点v，依次枚举从v出发的边v->u，设边的长度为len，判断Dist[v]+len是否小于Dist[u]，若小
于则改进Dist[u]，将Fa[u]记为v，并且由于S到u的最短距离变小了，有可能u可以改进其它的点，所以若u不在队列中，
就将它放入队尾。这样一直迭代下去直到队列变空，也就是S到所有的最短距离都确定下来，结束算法。若一个点入队次
数超过n，则有负权环。

SPFA 在形式上和宽度优先搜索非常类似，不同的是宽度优先搜索中一个点出了队列就不可能重新进入队列，但是SPFA中
一个点可能在出队列之后再次被放入队列，也就是一个点改进过其它的点之后，过了一段时间可能本身被改进，于是再
次用来改进其它的点，这样反复迭代下去。设一个点用来作为迭代点对其它点进行改进的平均次数为k，有办法证明对
于通常的情况，k在2左右。

SPFA算法（Shortest Path Faster Algorithm），也是求解单源最短路径问题的一种算法，用来解决：给定一个加权
有向图G和源点s，对于图G中的任意一点v，求从s到v的最短路径。 SPFA算法是Bellman-Ford算法的一种队列实现，减
少了不必要的冗余计算，他的基本算法和Bellman-Ford一样，并且用如下的方法改进： 1、第二步，不是枚举所有节点，
而是通过队列来进行优化 设立一个先进先出的队列用来保存待优化的结点，优化时每次取出队首结点u，并且用u点当前
的最短路径估计值对离开u点所指向的结点v进行松弛操作，如果v点的最短路径估计值有所调整，且v点不在当前的队列中，
就将v点放入队尾。这样不断从队列中取出结点来进行松弛操作，直至队列空为止。 2、同时除了通过判断队列是否为空来
结束循环，还可以通过下面的方法： 判断有无负环：如果某个点进入队列的次数超过V次则存在负环（SPFA无法处理带负环的图）。

SPFA算法有两个优化算法 SLF 和 LLL： SLF：Small Label First 策略，设要加入的节点是j，队首元素为i，
若dist(j)<dist(i)，则将j插入队首，否则插入队尾。 LLL：Large Label Last 策略，设队首元素为i，队列中所
有dist值的平均值为x，若dist(i)>x则将i插入到队尾，查找下一元素，直到找到某一i使得dist(i)<=x，则将i出对
进行松弛操作。 SLF 可使速度提高 15 ~ 20%；SLF + LLL 可提高约 50%。 在实际的应用中SPFA的算法时间效率不是
很稳定，为了避免最坏情况的出现，通常使用效率更加稳定的Dijkstra算法。

*/

#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int maxn = 1e5+5;
const int INF = 1<<28;
int N,M,S,T;

struct Edge
{
    int End,Len;
    Edge(int end, int len):End(end),Len(len){}
};

vector<Edge> g[maxn];
int d[maxn];  //d[i] 表示源点S到结点i的距离，SPFA算法结束后，d[i]就是S到i的最短距离
bool s[maxn]; //s[i]为true表示i在SPFA算法维护的队列中。

//时间复杂度 O(kE), k约等于2
int SPFA()
{
    s[S] = 1;
    for(int i=0; i<=N; ++i) d[i] = INF;
    d[S] = 0;
    queue<int> Q;
    Q.push(S);
    while(!Q.empty())
    {
        int u = Q.front(); Q.pop();
        for(int i=0,n=g[u].size(); i<n; ++i)
        {
            int v = g[u][i].End;
            int w = g[u][i].Len;
            if(d[u] + w < d[v])
            {
                d[v] = d[u] + w;
                if(!s[v]) //如果v结点不在队列中，将v结点放入队列。
                {
                    s[v] = 1;
                    Q.push(v);
                }
            }
        }
        s[u] = 0; //结点u离开队列。
    }
}


int main()
{
#ifdef WFX
freopen("in.txt","r", stdin);
#endif
    int u,v,w;
    scanf("%d%d%d%d",&N,&M,&S,&T);
    for(int i=1; i<=M; ++i)
    {
        scanf("%d%d%d",&u,&v,&w);
        g[u].push_back(Edge(v,w));
        g[v].push_back(Edge(u,w));
    }
    SPFA();
    printf("%d\n", d[T]);

	return 0;
}
    
