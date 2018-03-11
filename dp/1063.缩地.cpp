/*
时间限制:12000ms
单点时限:1000ms
内存限制:256MB
描述
编织者是 Dota 系列中的一个伪核，拥有很强的生存能力和线上消耗能力。编织者的代表性技能是缩地。缩地带来的隐身、
极限移动速度和伤害让它拥有很高的机动性以及赖线和收割的能力。
假设当前作战区域是一棵有根树，编织者所在的位置为根节点1，树中每个节点，有一个权值vi，代表这个节点的收益。
树中的每条边，有一个权值wi，代表每条边的长度。编织者从根结点出发，最远累计移动d 距离时，所能得到的收益的最大
值是多少？注意重复经过一个节点收益只能计算一次。

输入
第一行包含一个整数 n (1 ≤ n ≤ 100)，表示节点总数。
接下来的一行，包含 n 个数字，表示一个结点的价值 vi（0 ≤ vi ≤ 2）。
接下来的 n-1 行，每行三个整数 (ai, bi, wi)。表示一条连接 ai, bi 节点的边，边长为 wi (1 ≤ ai, bi ≤ n, 1 ≤ wi ≤ 104)。
接下来的一行包含一个数 q，表示询问总数 (0 ≤ q  ≤ 100000)。 接下来 q 行，每行包含一个整数 d ( ≤ d  ≤ 106)，表示从根结点
出发，最远累计移动的距离 d。

输出
对于每组询问，输出一行表示对应的询问所能得到的最大收益。

样例输入
3
0 1 1
1 2 5
1 3 3
3
3
10
11

样例输出
1
1
2

////未通过。

*/

#include<iostream>
#include<cstdio>
#include<vector>
#define maxn 105
using namespace std;
const int INF = 1<<20;

struct Edge{
    int end,weight;
    Edge(int e, int w):end(e),weight(w){};
};

vector<Edge> g[maxn];
//dp[i][j][1]表示以i为根结点, 收益为j, 最后必须回到i结点时最小行走的距离
//dp[i][j][0]表示以i为根结点, 收益为j, 最后可不回到i结点时最小行走的距离
int dp[maxn][maxn][2]; 


int DFS(int u,int pre){
    for(int i=0,n=g[u].size(); i<n; ++i){
        int v = g[u][i].end;
        int w = g[u][i].weight;
        if(v == pre) continue;
        DFS(v,u);  
        for(int j=200; j>=0; --j){
            for(int k=j; k>=0; --k){
                dp[u][j][1] = min(dp[u][j][1], dp[u][j-k][1] + dp[v][k][1] + w * 2);
                dp[u][j][0] = min(dp[u][j][0], dp[u][j-k][1] + dp[v][k][0] + w);
                dp[u][j][0] = min(dp[u][j][0], dp[u][j-k][0] + dp[v][k][1] + w * 2);
            }
        }
    }
}

int main(){
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    int N,Q,d;
    int u,v,w, score;
    scanf("%d",&N);
    for(int i=0; i<=100; ++i) for(int j=0;j<=200; ++j) dp[i][j][0] = dp[i][j][1] = INF;
    for(int i=1; i<=N; ++i){
        scanf("%d",&score);
        dp[i][score][1] = dp[i][score][0] = 0; //从i点出发获得score的收益需要行走的最下距离为0
    } 
    for(int i=1; i<N; ++i){
        scanf("%d%d%d", &u,&v,&w );
        g[u].push_back( Edge(v,w) );
        g[v].push_back( Edge(u,w) );
    }
    DFS(1,-1);
    for(int i=0; i<10; ++i){
        for(int j=0; j<150; ++j) printf("%d ",dp[i][j][0]);
        printf("\n");
    }
    scanf("%d",&Q);
    for(int i=0; i<Q; ++i){
        scanf("%d",&d);
        for(int j=200; j>=1; --j) if(dp[1][j][0] <= d){
            printf("%d\n",j);
            break;
        }
    }

    return 0;
}