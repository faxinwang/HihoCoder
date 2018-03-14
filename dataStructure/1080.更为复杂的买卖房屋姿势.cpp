/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
小Hi和小Ho都是游戏迷，“模拟都市”是他们非常喜欢的一个游戏，在这个游戏里面他们可以化身上帝模式，买卖房产。

在这个游戏里，会不断的发生如下两种事件：一种是房屋自发的涨价或者降价，而另一种是政府有关部门针对房价的硬性调控。
房价的变化自然影响到小Hi和小Ho的决策，所以他们希望能够知道任意时刻某个街道中所有房屋的房价总和是多少——但是很不
幸的，游戏本身并不提供这样的计算。不过这难不倒小Hi和小Ho，他们将这个问题抽象了一下，成为了这样的问题：

小Hi和小Ho所关注的街道的长度为N米，从一端开始每隔1米就有一栋房屋，依次编号为0..N，在游戏的最开始，每栋房屋都有
一个初始价格，其中编号为i的房屋的初始价格为p_i，之后共计发生了M次事件，所有的事件都是对于编号连续的一些房屋发生
的，其中第i次事件如果是房屋自发的涨价或者降价，则被描述为三元组(L_i, R_i, D_i)，表示编号在[L_i, R_i]范围内的房
屋的价格的增量（即正数为涨价，负数为降价）为D_i；如果是政府有关部门针对房价的硬性调控，则被描述为三元组(L_i, R_i, V_i)，
表示编号在[L_i, R_i]范围内的房屋的价格全部变为V_i。而小Hi和小Ho希望知道的是——每次事件发生之后，这个街道中所有房
屋的房价总和是多少。

输入
每个测试点（输入文件）有且仅有一组测试数据。
每组测试数据的第1行为两个整数N、M，分别表示街道的长度和总共发生的事件数。
每组测试数据的第2行为N+1个整数，其中第i个整数位p_i，表示编号为i的房屋的初始价格。
每组测试数据的第3-M+2行，按照发生的时间顺序，每行描述一个事件，如果该行描述的事件为，“房屋自发的涨价或者降价”，则该行
为4个整数0, L_i, R_i, D_i，意义如前文所述；如果该行描述的事件为“政府有关部门针对房价的硬性调控”，则该行为4个整数
1, L_i, R_i, V_i，意义如前文所述。
对于100%的数据，满足N<=10^5，1<=p_i, |D_i|, V_i<=10^4，0<=l_i<r_i<=n.
对于100%的数据，满足在任意时刻，任何房屋的价格都处于[1, 10^4]内。

输出
对于每组测试数据，输出M行，其中第i行为一个整数Ans_i，表示第i次事件发生之后，这个街道中所有房屋的房价总和。

样例输入
10 6
3195 2202 4613 3744 2892 4858 619 5079 9478 7366 8942 
0 1 6 886
1 0 2 9710
1 0 10 7980
0 4 9 -7594
0 2 8 1581
0 4 4 -1010

样例输出
58304
75652
87780
42216
53283
52273

解题思路：
本题使用的线段树上的每个结点都具有一个lazy_add标记和一个lazy_set标记, lazy_set标记具有覆盖性，
可直接覆盖子结点的lazy_set和lazy_add标记，而lazy_add标记具有累加性，需要累加到子结点的lazy_add
标记和区间和字段中去。
*/

#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 1e5+5;
int debug;

struct Node
{
    int L, R;       //区间
    int sum;        //区间和
    int lazy_set;   //懒惰设置价格
    int lazy_add;   //懒惰更新价格
};

struct SegTree
{
    Node a[maxn<<2];
    inline int Mid(int rt){ return a[rt].L + (a[rt].R - a[rt].L)/2; }

    inline int Length(int rt){ return a[rt].R - a[rt].L + 1; }

    void build(int L, int R, int rt=1)
    {
        a[rt].L = L;
        a[rt].R = R;
        a[rt].sum = a[rt].lazy_add = a[rt].lazy_set = 0;
        if(L == R) return ;
        int mid = Mid(rt);
        build(L, mid, rt<<1);
        build(mid+1, R, rt<<1|1);
    }

    void push_up(int rt){ a[rt].sum = a[rt<<1].sum + a[rt<<1|1].sum; }

    /*
    push down 操作中，set操作可以覆盖子结点的add操作，但时不能覆盖当前结点的add操作，
    也就是说，同一个结点可能既存在lazy_set标记又存在lazy_add标记，并且只可能是先有了
    lazy_set标记之后才有了lazy_add标记(因为对于同一个结点，如果一旦打上了lazy_set标记，
    其lazy_add标记就失效了，会被置为0)，所以lazy标记在下推的过程中，必须先处理lazy_set标记，
    再处理lazy_add标记。

    另外一个需要注意的是，lazy_set标记是覆盖性的，而lazy_add标记是累加性的，所以再下推的过程
    中，当前结点的lazy_add的值要累加到子结点上而不是直接赋值给子结点的lazy_add,因为子结点的
    lazy_add值可能不为0，并且将当前结点的lazy_add值(乘以子结点区间长度后)累加到子结点的区间和上去。
    */
    void push_down(int rt)
    {
        if(a[rt].L == a[rt].R) return;
        int lc = rt<<1, rc = lc+1;
        if(a[rt].lazy_set)
        {
            a[lc].lazy_set = a[rc].lazy_set = a[rt].lazy_set;
            a[lc].sum = Length(lc) * a[lc].lazy_set;
            a[rc].sum = Length(rc) * a[rc].lazy_set;
            //设置标记可以覆盖增减标记
            a[lc].lazy_add = a[rc].lazy_add = 0;
            //消除父结点的懒惰设置标记
            a[rt].lazy_set = 0;
        }
        if(a[rt].lazy_add)
        {
            a[lc].lazy_add += a[rt].lazy_add;
            a[rc].lazy_add += a[rt].lazy_add;
            a[lc].sum += Length(lc) * a[rt].lazy_add;
            a[rc].sum += Length(rc) * a[rt].lazy_add;
            //消除父结点的懒惰增减标记
            a[rt].lazy_add = 0;
        }
    }

    void set(int L, int R, int val, int rt=1)
    {
        // if(debug) printf("set: L=%d  R=%d val=%d rt=%d\n",L,R,val, rt);
        push_down(rt);
        if(a[rt].L == L && a[rt].R == R)
        {
            a[rt].sum = Length(rt) * val;
            a[rt].lazy_set = val;
            a[rt].lazy_add = 0;
            return;
        }

        int mid = Mid(rt), lc=rt<<1, rc=lc+1;
        if(R <= mid ) set(L, R, val, lc);
        else if(mid < L) set(L, R, val, rc);
        else
        {
            set(L, mid, val, lc);
            set(mid+1, R, val, rc);
        }
        push_up(rt);
    }

    void add(int L, int R, int val, int rt=1)
    {
        // if(debug) printf("add: L=%d  R=%d val=%d rt=%d\n",L,R,val,rt);
        push_down(rt);
        if(a[rt].L == L && a[rt].R == R)
        {
            a[rt].sum += Length(rt) * val;
            a[rt].lazy_add += val;
            return;
        }
        int mid = Mid(rt), lc=rt<<1, rc=lc+1;
        if(R <= mid ) add(L, R, val, lc);
        else if(mid < L) add(L, R, val, rc);
        else
        {
            add(L, mid, val, lc);
            add(mid+1, R, val, rc);
        }
        push_up(rt);
    }


    int query(int L,int R,int rt=1)
    {
        push_down(rt);
        if(a[rt].L == L && a[rt].R == R) return a[rt].sum;
        int mid = Mid(rt);
        if(R <= mid) return query(L, R, rt<<1);
        else if(mid < L) return query(L,R, rt<<1|1);
        else return query(L, mid, rt<<1) + query(mid+1, R, rt<<1|1);
    }

    void dfs(int rt=1)
    {
        if(a[rt].R)
        {
            dfs(rt<<1);
            dfs(rt<<1|1);
            printf("L=%d R=%d sum=%d\n", a[rt].L, a[rt].R, a[rt].sum);
        }
    }

}tree;



int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif

    int N, M, val;
    int op, L, R;
    scanf("%d%d",&N,&M);
    tree.build(0,N);
    for(int i=0; i<=N; ++i)
    {
        scanf("%d", &val);
        tree.set(i,i,val);
    }
    // debug = 1;
    // if(debug) tree.dfs();

    while(M--)
    {
        scanf("%d%d%d%d", &op, &L, &R, &val);
        op == 1? tree.set(L,R,val) : tree.add(L,R,val);
        printf("%d\n", tree.query(0,N));
    }

    return 0;
}
