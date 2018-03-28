/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
小Ho：喂不得了啦，那边便利店的薯片半价了!

小Hi：啥?!

小Ho：那边的便利店在打折促销啊。

小Hi：走走走，赶紧去看看=v=

于是小Hi和小Ho来到了便利店。

老板为了促销，推出了组合包的形式，将不同数量的各类商品打包成一个组合，顾客可以选择组合进行购买。比如2袋薯片，
1听可乐的组合只要5元，而1袋薯片，2听可乐的组合只要4元。

通过询问老板，小Hi和小Ho知道：一共有N种不同的商品和M种不同的商品组合；每一个组合的价格等于组合内商品售价之和，
一个组合内同一件商品不会超过10件。

小Hi：这样算下来的话，一听可乐就是1元，而一包薯片是2元。小Ho，如果你知道所有的组合情况，你能分别算出每一件
商品单独的价格么？

小Ho：当然可以了，这样的小问题怎么能难到我呢？

   
提示：高斯消元

 
输入
第1行：2个正整数，N,M。表示商品的数量N，组合的数量M。1≤N≤500, N≤M≤2*N

第2..M+1行：N+1个非负整数，第i+1行第j列表示在第i个组合中，商品j的数量a[i][j]。第i+1行第N+1个数表示该组合
的售价c[i]。0≤a[i][j]≤10, 0≤c[i]≤10^9

输出
若没有办法计算出每个商品单独的价格，输出"No solutions"

若可能存在多个不同的结果，输出"Many solutions"

若存在唯一可能的结果，输出N行，每行一个非负整数，第i行表示第i个商品单独的售价。数据保证如果存在唯一解，那么解
一定恰好是非负整数解。

样例输入
2 2
2 1 5
1 2 4
样例输出
2
1


*/

#include<bits/stdc++.h>
using namespace std;
const int maxn = 505;
const int maxm = maxn * 2;

double a[maxm][maxn];

inline int dcmp(double x)
{  
    if(fabs(x) < 1e-7) return 0;
    return x>0? 1 : -1;
}

// M equations, N items in 0 ~ N-1, a[i][N] 保存第i个方程的结果
int gauss(int M, int N)
{
    //处理上三角矩阵
    for(int c=0; c<N; ++c)
    {
        //查看当前列的下面是否全为0，若全为0 ，则有多解
        int _max = c;
        for(int r=c+1; r<M; ++r) if(a[_max][c] < a[r][c]) _max = r;
        if( dcmp(a[_max][c]) == 0 )  return -1; //多解
        
        if( _max != c) swap(a[_max], a[c]); //把不为0的那一行交换到当前
        //将当前行的第一个自变量a[c][c]的系数变换为1
        for(int k=c; k<=N; ++k) a[c][k] /= a[c][c];
        //将当前行当前列下面自变量的系数变换为0
        for(int r=c+1; r<M; ++r)
        {
            for(int k=N; k>=c; --k) 
                a[r][k] -= a[c][k] * a[r][c];
            a[r][c] = 0; //浮点数，避免误差，置零
        }
    }
    //检查是否有解：
    //查看第N行到底M-1行，如果存在系数全为0，结果不为0 的情况，则无解。
    for(int r=N; r<M; ++r)
    {
        int c=0;
        for(; c<N && dcmp(a[r][c])==0 ; ++c);
        if(c==N && a[r][N] > 0 ) return 0;  ///无解
    }

    // //从正方形矩阵最后一行开始往上代入各自变量的值
    // for(int r=N; r>=0; --r)
    // {
    //     for(int)
    // }
}

int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    int N,M;
    scanf("%d%d",&N,&M);
    for(int r=0;r<M; ++r)
        for(int c=0; c<=N; ++c )
            scanf("%d",&a[r][c]);

    int ans = gauss(M, N);
    if(ans == -1) printf("Many solutions\n");
    else if(ans = 0) printf("No solutions\n");
    // else for(int i=0; i<N; ++i) printf("%d\n", a[i][N]);
    for(int r=0; r<N; ++r)
    {
        for(int c=0; c<=N; ++c) printf("%d ", a[r][c]);
        printf("\n");
    }

    return 0;
}