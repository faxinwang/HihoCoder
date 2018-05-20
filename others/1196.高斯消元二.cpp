/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
在上一回中，小Hi和小Ho趁着便利店打折，买了一大堆零食。当他们结账后，看到便利店门口还有其他的活动。

店主：买了东西还可以参加游戏活动哦，如果能够完成游戏还有额外的奖品。

小Hi和小Ho赶紧凑了过去。

店主放了一块游戏板在店门口，有5行6列格子。左上角为坐标(1,1)。一部分格子是亮着的，另一部分是暗着的。

week57_1.PNG

 当按下某一个格子时，它和上下左右4个格子的状态就会改变。原来亮着的格子变成暗的，原来暗的格子会变亮。
 比如下图中按下标记有红叉的格子后，绿色虚线区域内的格子状态都会改变：
week57_2.PNG

店主给出初始的状态，参加游戏的人员需要通过按下某些格子，让游戏板上所有的灯都亮起来就可以赢得奖品。

小Ho：这不就是开关灯问题么，看我来解决它！

本题改编自ACMICPC Greater New York 2002 EXTENDED LIGHTS OUT

输入
第1..5行：1个长度为6的字符串，表示该行的格子状态，1表示该格子是亮着的，0表示该格子是暗的。

保证一定存在解，且一定存在暗着的格子。

输出
需要按下的格子数量k，表示按下这k个位置后就可以将整个游戏板所有的格子都点亮。

接下来k行，每行一个坐标(x,y)，表示需要按下格子(x,y)。x坐标较小的先输出，若x相同，则先输出y坐标较小的。

样例输入
001111
011111
111111
111110 
111100

样例输出
2
1 1
5 6
*/

#include<bits/stdc++.h>
using namespace std;
const int M = 5;
const int N = 6;

int tab[M][N];
int flip[M][N];
int best[M][N];
int dir[5][2] = {0,1,1,0,  0,-1,-1,0,  0,0};

int color(int x,int y)
{
    int c = tab[x][y];
    for(int i=0; i<5; ++i)
    {
        int tx = x + dir[i][0];
        int ty = y + dir[i][1];
        if(0 <= tx && tx < M && 0 <= ty && ty < N) c += flip[tx][ty];
    }
    return c & 1;
}

int calu()
{
    for(int i=1; i<M; ++i)
        for(int j=0; j<N; ++j)
            if(color(i-1, j) == 0) flip[i][j] = 1;
    for(int j=0; j<N; ++j) if(color(M-1, j) == 0) return -1;
    int res=0;
    for(int i=0; i<M; ++i)
        for(int j=0; j<N; ++j)
            res += flip[i][j];
    return res;
}

void solve()
{
    int res = N * M; //题目保证一定存在解
    for(int i=0, n=1<<N; i<n; ++i)
    {
        memset(flip, 0 ,sizeof(flip));
        for(int j=0; j<N; ++j) flip[0][j] = i>>j & 1;

        int num = calu();
        if(num < 0) continue;
        if(num < res)
        {
            res = num;
            memcpy(best, flip, sizeof(flip));
        }
    }
    printf("%d\n", res);
    for(int i=0; i<M; ++i)
        for(int j=0; j<N; ++j)
            if( best[i][j] ) printf("%d %d\n", i+1, j+1);
}

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif
    
    char s[7];
    for(int i=0; i<M; ++i)
    {
        scanf("%s",s);
        for(int j=0; j<N; ++j) tab[i][j] = s[j] - '0';
    }

    solve();
    
    return 0;
}