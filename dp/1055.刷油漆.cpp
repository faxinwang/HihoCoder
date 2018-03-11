/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
上回说到，小Ho有着一棵灰常好玩的树玩具！这棵树玩具是由N个小球和N-1根木棍拼凑而成，这N个小球都被小Ho标上了
不同的数字，并且这些数字都是处于1..N的范围之内，每根木棍都连接着两个不同的小球，并且保证任意两个小球间都不
存在两条不同的路径可以互相到达。没错，这次说的还是这棵树玩具的故事！

小Ho的树玩具的质量似乎不是很好，短短玩了几个星期，便掉漆了！

“简直是一场噩梦！”小Ho拿着树玩具眼含热泪道。

“这有什么好忧伤的，自己买点油漆刷一刷不就行了？”小Hi表示不能理解。

“还可以这样？”小Ho顿时兴高采烈了起来，立马跑出去买回来了油漆，但是小Ho身上的钱却不够——于是他只买回了有限的油漆，
这些油漆最多能给M个结点涂上颜色，这就意味着小Ho不能够将他心爱的树玩具中的每一个结点都涂上油漆！

小Ho低头思索了半天——他既不想只选一部分结点补漆，也不想找小Hi借钱，但是很快，他想出了一个非常棒的主意：将包含1号结
点的一部分连通的结点进行涂漆（这里的连通指的是这一些涂漆的结点可以互相到达并且不会经过没有涂漆的结点），然后将剩下
的结点拆掉！

那么究竟选择哪些结点进行涂漆呢？小Ho想了想给每个结点都评上了分——他希望最后留下来，也就是涂漆了的那些结点的评分之
和可以尽可能的高！

那么，小Ho该如何做呢？

输入
每个测试点（输入文件）有且仅有一组测试数据。

每组测试数据的第一行为两个整数N、M，意义如前文所述。

每组测试数据的第二行为N个整数，其中第i个整数Vi表示标号为i的结点的评分

每组测试数据的第3~N+1行，每行分别描述一根木棍，其中第i+1行为两个整数Ai，Bi，表示第i根木棍连接的两个小球的编号。

对于100%的数据，满足N<=10^2，1<=Ai<=N, 1<=Bi<=N, 1<=Vi<=10^3, 1<=M<=N

小Hi的Tip：那些用数组存储树边的记得要开两倍大小哦！

输出
对于每组测试数据，输出一个整数Ans，表示使得涂漆结点的评分之和最高可能是多少。

样例输入
10 4
370 328 750 930 604 732 159 167 945 210 
1 2
2 3
1 4
1 5
4 6
4 7
4 8
6 9
5 10

样例输出
2977

解题思路：
dp[u][j]表示以节点u为根的结点个数为 j 的树可得到的最大分数，所以答案就是dp[1][m]。
状态转移方程为：dp[u][j]=max(dp[v1][k1]+dp[v2][k2]+...+dp[vx][kx])，v是u的子节点。

注意我们要dp[u][j](2<=j<=m)全都用一遍泛化物品，这里特别要注意是 j 是从小到大，还是从大到小。
对于某个j来说：dp[u][j] = max(dp[u][j], dp[u][j - k] + dp[v][k])，我们要根据这个式子来不断更新dp[u][j]的值，
更新的过程中要用到dp[u][j-k]的值，也就是说比 j 小的值。试想一下如果我们 j 是从小到大更新的，那么我用dp[v][k]来
更新dp[u][j]的时候用到的dp[u][j-k]是有可能包含dp[v][k]的，也就是说我们求dp[u][j-k]的时候可能用过了dp[v][k]，
但是dp[v][k]在dp[u][j]中至多出现一次，，现在会出现两次，所以是错误的。正解j要从大到小更新。
*/

#include<iostream>
#include<cstdio>
#include<vector>
#define maxn 105
using namespace std;

int N,M;
vector<int> g[maxn];
int s[maxn];
int dp[maxn][maxn]; //dp[i][j]表示以i为根节点，具有j-1个子结点的最大总得分，包括根结点一共j个结点。

void DFS(int u, int pre){
    dp[u][1] = s[u]; //只包含自身时分数即为该结点自身的分数
    for(int i=0,n=g[u].size(); i<n; ++i){
        int v = g[u][i];
        if(v == pre) continue;
        DFS(v, u);
         //因为在计算dp[u][j]的时候用到了dp[u][j-k]，为了避免重复统计，需要逆序计算
        for(int j=M; j>=2; --j){ //可以理解为有M个物品，每个物品的重量为1,价值为dp[i][j]，背包容量为M的01背包问题
            for(int k=1; k<j; ++k){
                dp[u][j] = max(dp[u][j], dp[u][j-k] + dp[v][k]);
            }
        }
    }
}

int main(){
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    int a,b;
    scanf("%d%d",&N,&M);
    for(int i=1; i<=N; ++i) scanf("%d", s+i);
    for(int i=1; i<N; ++i){  //N-1 edges 
        scanf("%d%d",&a,&b);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    DFS(1,-1);
    printf("%d\n", dp[1][M]);

    return 0;
}
