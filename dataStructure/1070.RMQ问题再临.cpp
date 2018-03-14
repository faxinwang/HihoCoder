/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
终于，小Hi和小Ho踏上了回国的旅程。在飞机上，望着采购来的特产——小Hi陷入了沉思：还记得在上上周他们去超市的时候，
前前后后挑了那么多的东西，都幸运的没有任何其他人（售货员/其他顾客）来打搅他们的采购过程。但是如果发生了这样的
事情，他们的采购又会变得如何呢？

于是小Hi便向小Ho提出了这个问题：假设整个货架上从左到右摆放了N种商品，并且依次标号为1到N，每次小Hi都给出一段区
间[L, R]，小Ho要做的是选出标号在这个区间内的所有商品重量最轻的一种，并且告诉小Hi这个商品的重量。但是在这个过
程中，可能会因为其他人的各种行为，对某些位置上的商品的重量产生改变（如更换了其他种类的商品），面对这样一个问题，
小Ho又该如何解决呢？

提示：平衡乃和谐之理

输入
每个测试点（输入文件）有且仅有一组测试数据。

每组测试数据的第1行为一个整数N，意义如前文所述。

每组测试数据的第2行为N个整数，分别描述每种商品的重量，其中第i个整数表示标号为i的商品的重量weight_i。

每组测试数据的第3行为一个整数Q，表示小Hi总共询问的次数与商品的重量被更改的次数之和。

每组测试数据的第N+4~N+Q+3行，每行分别描述一次操作，每行的开头均为一个属于0或1的数字，分别表示该行描述一个询问和描述
一次商品的重量的更改两种情况。对于第N+i+3行，如果该行描述一个询问，则接下来为两个整数Li, Ri，表示小Hi询问的一个区间
[Li, Ri]；如果该行描述一次商品的重量的更改，则接下来为两个整数Pi，Wi，表示位置编号为Pi的商品的重量变更为Wi

对于100%的数据，满足N<=10^4，Q<=10^4, 1<=Li<=Ri<=N，1<=Pi<=N, 0<weight_i, Wi<=10^4。

输出
对于每组测试数据，对于每个小Hi的询问，按照在输入中出现的顺序，各输出一行，表示查询的结果：标号在区间[Li, Ri]中的所
有商品中重量最轻的商品的重量。

样例输入
10
618 5122 1923 8934 2518 6024 5406 1020 8291 2647 
6
0 3 6
1 2 2009
0 2 2
0 2 10
1 1 5284
0 2 5

样例输出
1923
2009
1020
1923

解题思路：
这里用线段树处理，线段树结点中记录该结点所表示的区间中的最小值，在插入的时候需要向上更新。
*/

#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 1e4+5;
const int INF = 1<<30;

struct Node
{
    int L,R, Min;
};

struct SegTree
{
    Node arr[maxn<<2];
    void build(int rt, int L,int R)
    {
        arr[rt].L = L;
        arr[rt].R = R;
        arr[rt].Min = INF;
        if( L == R ) return;
        int mid = L + (R - L)/2;
        build(rt<<1, L,mid);
        build(rt<<1|1, mid+1,R);
    }

    void pushup(int rt){ arr[rt].Min = min( arr[rt<<1].Min, arr[rt<<1|1].Min ); }

    void insert(int rt, int pos, int val)
    {
        if(arr[rt].L == arr[rt].R){
            arr[rt].Min = val;
        }
        else
        {
            int mid = arr[rt].L + (arr[rt].R - arr[rt].L)/2;
            if(pos <= mid) insert(rt<<1, pos, val);
            else insert(rt<<1|1, pos, val);
            pushup(rt);
        }
    }

    int query(int rt,int L,int R)
    {
        if(arr[rt].L == L && arr[rt].R == R) return arr[rt].Min;
        int mid = arr[rt].L + (arr[rt].R - arr[rt].L)/2;
        if(R <= mid) return query(rt<<1, L,R);
        else if(mid < L) return query(rt<<1|1, L, R);
        else return min(query(rt<<1, L, mid), query(rt<<1|1, mid+1, R));
    }
};



int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    int N,M;
    int op,x,y;
    SegTree tree;
    scanf("%d",&N);
    tree.build(1,1,N);
    for(int i=1; i<=N; ++i){
        scanf("%d", &x);
        tree.insert(1,i,x);
    }
    
    scanf("%d",&M);
    while(M--)
    {
        scanf("%d%d%d",&op,&x,&y);
        if(op == 1) tree.insert(1,x,y);
        else printf("%d\n", tree.query(1,x,y));
    }

    return 0;
}