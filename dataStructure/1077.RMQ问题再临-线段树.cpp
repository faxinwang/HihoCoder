/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
上回说到：小Hi给小Ho出了这样一道问题：假设整个货架上从左到右摆放了N种商品，并且依次标号为1到N，每次小Hi都给出一
段区间[L, R]，小Ho要做的是选出标号在这个区间内的所有商品重量最轻的一种，并且告诉小Hi这个商品的重量。但是在这个
过程中，可能会因为其他人的各种行为，对某些位置上的商品的重量产生改变（如更换了其他种类的商品）。

小Ho提出了两种非常简单的方法，但是都不能完美的解决。那么这一次，面对更大的数据规模，小Ho将如何是好呢？
提示：其实只是比ST少计算了一些区间而已

输入
每个测试点（输入文件）有且仅有一组测试数据。

每组测试数据的第1行为一个整数N，意义如前文所述。

每组测试数据的第2行为N个整数，分别描述每种商品的重量，其中第i个整数表示标号为i的商品的重量weight_i。

每组测试数据的第3行为一个整数Q，表示小Hi总共询问的次数与商品的重量被更改的次数之和。

每组测试数据的第N+4~N+Q+3行，每行分别描述一次操作，每行的开头均为一个属于0或1的数字，分别表示该行描述一个询问和
描述一次商品的重量的更改两种情况。对于第N+i+3行，如果该行描述一个询问，则接下来为两个整数Li, Ri，表示小Hi询问的
一个区间[Li, Ri]；如果该行描述一次商品的重量的更改，则接下来为两个整数Pi，Wi，表示位置编号为Pi的商品的重量变更为Wi

对于100%的数据，满足N<=10^6，Q<=10^6, 1<=Li<=Ri<=N，1<=Pi<=N, 0<weight_i, Wi<=10^4。

输出
对于每组测试数据，对于每个小Hi的询问，按照在输入中出现的顺序，各输出一行，表示查询的结果：标号在区间[Li, Ri]中的所
有商品中重量最轻的商品的重量。

样例输入
10
3655 5246 8991 5933 7474 7603 6098 6654 2414 884 
6
0 4 9
0 2 10
1 4 7009
0 5 6
1 3 7949
1 3 1227

样例输出
2414
884
7474


*/

#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 1e6+5;
const int INF = 1<<30;

struct Node
{
    int L, R, Min;
};

struct SegTree
{
    Node a[maxn<<2];
    void build(int rt,int L,int R)
    {
        a[rt].L = L;
        a[rt].R = R;
        a[rt].Min = INF;
        if(L == R) return ;
        int mid = L + (R - L )/2;
        build(rt<<1, L, mid);
        build(rt<<1|1, mid+1, R);
    }

    void pushup(int rt){ a[rt].Min = min( a[rt<<1].Min, a[rt<<1|1].Min ); }

    void insert(int rt,int pos,int val)
    {
        if( a[rt].L == a[rt].R ){
            a[rt].Min = val;
        }
        else
        {
            int mid = a[rt].L + (a[rt].R - a[rt].L) / 2;
            if(pos <= mid) insert(rt<<1, pos, val);
            else insert(rt<<1|1, pos, val);
            pushup(rt);
        }
    }

    int query(int rt,int L,int R)
    {
        if(a[rt].L ==L && a[rt].R == R) return a[rt].Min;
        int mid = (a[rt].L + a[rt].R)/2;
        if(R <= mid) return query(rt<<1, L,R);
        else if(mid < L) return query(rt<<1|1, L, R);
        else return min( query(rt<<1, L,mid), query(rt<<1|1, mid+1, R));
    }
};

int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    int N,M;
    int op,x,y;
    //不能直接声明为对象，否则会爆栈，因为对象里面开了大数组
    SegTree * tree = new SegTree;
    scanf("%d",&N);
    tree->build(1,1,N);
    for(int i=1; i<=N; ++i)
    {
        scanf("%d", &x);
        tree->insert(1,i,x);
    }
    scanf("%d",&M);
    while(M--)
    {
        scanf("%d%d%d",&op,&x,&y);
        if( op==1 ) tree->insert(1,x,y);
        else printf("%d\n", tree->query(1,x,y));
    }

    return 0;
}
