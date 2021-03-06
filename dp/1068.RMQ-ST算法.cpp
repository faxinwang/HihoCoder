/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
小Hi和小Ho在美国旅行了相当长的一段时间之后，终于准备要回国啦！而在回国之前，他们准备去超市采购一些当地特产——比如汉堡
（大雾）之类的回国。但等到了超市之后，小Hi和小Ho发现者超市拥有的商品种类实在太多了——他们实在看不过来了！于是小Hi决定
向小Ho委派一个任务：假设整个货架上从左到右拜访了N种商品，并且依次标号为1到N，每次小Hi都给出一段区间[L, R]，小Ho要做
的是选出标号在这个区间内的所有商品重量最轻的一种，并且告诉小Hi这个商品的重量，于是他们就可以毫不费劲的买上一大堆东西
了——多么可悲的选择困难症患者。

（虽然说每次给出的区间仍然要小Hi来进行决定——但是小Hi最终机智的选择了使用随机数生成这些区间！但是为什么小Hi不直接使用
随机数生成购物清单呢？——问那么多做什么！）

提示一：二分法是宇宙至强之法！（真的么？）
提示二：线段树不也是二分法么？

输入
每个测试点（输入文件）有且仅有一组测试数据。
每组测试数据的第1行为一个整数N，意义如前文所述。
每组测试数据的第2行为N个整数，分别描述每种商品的重量，其中第i个整数表示标号为i的商品的重量weight_i。
每组测试数据的第3行为一个整数Q，表示小Hi总共询问的次数。
每组测试数据的第N+4~N+Q+3行，每行分别描述一个询问，其中第N+i+3行为两个整数Li, Ri，表示小Hi询问的一个区间[Li, Ri]。
对于100%的数据，满足N<=10^6，Q<=10^6, 1<=Li<=Ri<=N，0<weight_i<=10^4。

输出
对于每组测试数据，对于每个小Hi的询问，按照在输入中出现的顺序，各输出一行，表示查询的结果：标号在区间[Li, Ri]中的所有
商品中重量最轻的商品的重量。

样例输入
10
7334
1556
8286
1640
2699
4807
8068
981
4120
2179
5
3 4
2 8
2 4
6 8
7 10

样例输出
1640
981
1556
981
981


解题思路:
参考:https://www.cnblogs.com/JeromeHuang/p/4472727.html

RMQ（Range Minimum/Maximum Query），即区间最值查询，是指这样一个问题：对于长度为n的数列A，回答若干询问RMQ（A,i,j）
(i,j<=n)，返回数列A中下标在i，j之间的最小/大值。这两个问题是在实际应用中经常遇到的问题。最简单的算法就是对每次查询进
行一次遍历，复杂度为O(QN)，其中Q为查询的次数。当然有效率更高的算法。RMQ-ST算法。
在线算法（ST算法）解决这个问题。所谓在线算法，是指用户每输入一个查询便马上处理一个查询。该算法一般用较长的时间做预处理，
待信息充足以后便可以用较少的时间回答每个查询。ST（Sparse Table）算法是一个非常有名的在线处理RMQ问题的算法，它可以在
O(nlogn)时间内进行预处理，然后在O(1)时间内回答每个查询。首先是预处理，用动态规划（DP）解决。设A[i]是要求区间最值的数列，

F[i, j]表示从第i个数起连续2^j个数中的最大值。

例如数列3 2 4 5 6 8 1 2 9 7，F[1，0]表示第1个数起，长度为2^0=1的最大值，
其实就是3这个数。 F[1，2]=5，F[1，3]=8，F[2，0]=2，F[2，1]=4……从这里可以看出 F[i,0]其实就等于A[i]。这样，DP的状态、
初值都已经有了，剩下的就是状态转移方程。我们把F[i，j]平均分成两段（因为f[i，j]一定是偶数个数字），从i到i+2^(j-1)-1为一
段，i+2^(j-1)到i+2^j-1为一段(长度都为2^（j-1）)。用上例说明，当i=1，j=3时就是3,2,4,5 和 6,8,1,2这两段。F[i，j]就是
这两段的最大值中的最大值。于是我们得到了

动态规划方程 F[i, j] = max(F[i，j-1], F[i + 2^(j-1)，j-1])

然后是查询，由于给出的区间不一定是2的次幂，所以需要取一个最小幂覆盖区间。取k=[log2(j-i+1)]，向上取整，则有：

RMQ(A, i, j) = max{F[i,k],F[j-2^k+1,k]}，

即将区间分为[i,i+(2^k)-1] [j-(2^k)+1,j]，容易证明这两个区间是有重合地方的。 举例说明，要求区间[2，8]的最大值，就要把
它分成[2,5]和[5,8]两个区间，因为这两个区间的最大值我们可以直接由f[2，2]和f[5，2]得到。

以下是上面测试用例计算出的spare table
7334 1556 1556 981 0 0
1556 1556 1556 981 0 0
8286 1640 1640 981 0 0
1640 1640 1640 0 0 0
2699 2699 981 0 0 0
4807 4807 981 0 0 0
8068 981 981 0 0 0
981 981 0 0 0 0
4120 2179 0 0 0 0
2179 0 0 0 0 0

*/

#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 1e6 + 5;
const int maxm = 20;

int dp[maxn][maxm]; //2^20 > 10^6

//预处理数据，时间复杂度为O(NlogN)
void init_RMQ(int n)
{
    for(int j=1; j<=maxm; ++j)
    {
        for(int i=1; i+(1<<j) - 1 <= n; ++i) dp[i][j] = min(dp[i][j-1], dp[i+ (1<<(j-1))][j-1]);
    }
}

//查询区间最大最小值，时间复杂度O(1)
int RMQ(int L,int R)
{
    int k = 0, Len = R - L + 1;
    while(1<<(k+1) <= Len ) ++k;
    return min(dp[L][k], dp[R-(1<<k)+1][k]);
}

int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    int N,M, L,R;
    scanf("%d",&N);
    for(int i=1; i<=N; ++i) scanf("%d", &dp[i][0]);

    init_RMQ(N);

    scanf("%d",&M);
    while(M--)
    {
        scanf("%d%d",&L,&R);
        printf("%d\n", RMQ(L,R));
    }

    // for(int i=0; i<=N; ++i)
    // {
    //     for(int j=0; j<=5; ++j) printf("%d ", dp[i][j]);
    //     printf("\n");
    // }

    return 0;
}