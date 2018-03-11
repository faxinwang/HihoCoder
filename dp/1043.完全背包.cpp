/*
时间限制:20000ms
单点时限:1000ms
内存限制:256MB
描述
且说之前的故事里，小Hi和小Ho费劲心思终于拿到了茫茫多的奖券！而现在，终于到了小Ho领取奖励的时刻了！
等等，这段故事为何似曾相识？这就要从平行宇宙理论说起了………总而言之，在另一个宇宙中，小Ho面临的问题发生了细微的变化！
小Ho现在手上有M张奖券，而奖品区有N种奖品，分别标号为1到N，其中第i种奖品需要need(i)张奖券进行兑换，并且可以兑换无数次，
为了使得辛苦得到的奖券不白白浪费，小Ho给每件奖品都评了分，其中第i件奖品的评分值为value(i),表示他对这件奖品的喜好值。
现在他想知道，凭借他手上的这些奖券，可以换到哪些奖品，使得这些奖品的喜好值之和能够最大。

提示一： 切，不就是0~1变成了0~K么
提示二：强迫症患者总是会将状态转移方程优化一遍又一遍
提示三：同样不要忘了优化空间哦！

输入
每个测试点（输入文件）有且仅有一组测试数据。
每组测试数据的第一行为两个正整数N和M,表示奖品的种数，以及小Ho手中的奖券数。
接下来的n行描述每一行描述一种奖品，其中第i行为两个整数need(i)和value(i)，意义如前文所述。

测试数据保证
对于100%的数据，N的值不超过500，M的值不超过10^5
对于100%的数据，need(i)不超过2*10^5, value(i)不超过10^3

输出
对于每组测试数据，输出一个整数Ans，表示小Ho可以获得的总喜好值。

样例输入
5 1000
144 990
487 436
210 673
567 58
1056 897

样例输出
5940

解题思路：

在完全背包中，v变化的区间是顺序循环的原因：完全背包的特点是每种物品可选无限件，在求解加选第i种物品带来的
收益f[i][v]时，在状态f[i][v-c[i]]中已经尽可能多的放入物品i了，此时在f[i][v-c[i]]的基础上，我们可以再次
放入一件物品i，此时也是在不超过背包容量的基础下，尽可能多的放入物品i。

分析：

i = 2，表示正在处理第2件物品。在求解f[2][4]时，如果要计算把第2件物品放入背包后的代价时，我们需要知道f[2][2],
此时f[2][2]中已经尽全力放入第2件物品了（已经放入一件）。此时此刻还可以在放入一件第2件物品，在背包容量为4时，
最多可以放入两件第二件物品。

总结下，f[i][v]:表示在背包容量为v时，尽全力的放入第i件物品的代价。f[i][v - weight[i]]:表示在背包容量
为v - weight[i]时，尽全力的放入第i件物品的代价。因此由f[i][v - weight[i]]转换为f[i][v]时，也是在
f[i][v - weight[i]]的基础上有加入了一件物品i。

迭代方程：f[i][v] = max(f[i - 1][v],f[i][v - weight[i]] + Value[i]);
注意与O1背包方程的不同。

二维：
#include<iostream>  
#include<cstdio>  
#include<cstring>  
#define MAXN 505  
using namespace std;  
int dp[505][100005];  
int need[505];  
int value[505];  
int main()  
{  
    int n,v;  
    while(~scanf("%d%d",&n,&v))  
    {  
        memset(dp,0,sizeof(dp));  
        for(int i=1;i<=n;i++)  
            scanf("%d%d",&need[i],&value[i]);  
        for(int i=1;i<=n;i++)  
            for(int j=1;j<=v;j++)  
            {  
                int maxvalue=dp[i-1][j];  
                for(int k=0;k*need[i]<=j;k++)  
                {  
                    int thevalue=dp[i-1][j-need[i]*k]+value[i]*k;  
                    if(thevalue>maxvalue)  
                        maxvalue=thevalue;  
                }  
                dp[i][j]=maxvalue;  
            }  
            printf("%d\n",dp[n][v]);  
    }  
    return 0;  
} 

一维：
#include<iostream>  
#include<cstdio>  
#include<cstring>  
#define MAXN 505  
using namespace std;  
int dp[100005];  
int need[505];  
int value[505];  
int main()  
{  
    int n,v;  
    while(~scanf("%d%d",&n,&v))  
    {  
        int ans=0;  
        memset(dp,0,sizeof(dp));  
        for(int i=1;i<=n;i++)  
            scanf("%d%d",&need[i],&value[i]);  
        for(int i=1;i<=n;i++)  
            for(int j=0;j<=v;j++)  
                for(int k=0;k*need[i]<=j;k++){  
                dp[j]=max(dp[j],dp[j-need[i]*k]+value[i]*k);  
                if(dp[j]>ans)  
                    ans=dp[j];  
            }  
            printf("%d\n",ans);  
    }  
    return 0;  
}  

*/

//一维
#include<iostream>
#include<cstdio>
using namespace std;
const int maxc = 1e5+5;

int dp[maxc];

int main(){
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    int N,C;
    int need,value;
    scanf("%d%d",&N,&C);
    for(int i=0; i<N; ++i){
        scanf("%d%d",&need, &value);
        /*
        1.顺序循环，所以从dp[need]转换到dp[j+need]是在已经放入过该物品和当前背包容量
          允许的情况下尽可能地再放入该物品
        2.而01背包逆序循环，在从dp[j+need]转换到dp[need]时，是在没放入过该物品的情况
          下尽可能地放入该物品，所以最多只会放入一次
        */
        for(int j=need; j<=C; ++j) dp[j] = max(dp[j], dp[j-need] + value);
    }
    printf("%d\n", dp[C]);

    return 0;
}