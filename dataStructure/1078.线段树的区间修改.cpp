/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
对于小Ho表现出的对线段树的理解，小Hi表示挺满意的，但是满意就够了么？于是小Hi将问题改了改，又出给了小Ho：

假设货架上从左到右摆放了N种商品，并且依次标号为1到N，其中标号为i的商品的价格为Pi。小Hi的每次操作分为两种可能，
第一种是修改价格——小Hi给出一段区间[L, R]和一个新的价格NewP，所有标号在这段区间中的商品的价格都变成NewP。第二
种操作是询问——小Hi给出一段区间[L, R]，而小Ho要做的便是计算出所有标号在这段区间中的商品的总价格，然后告诉小Hi。

那么这样的一个问题，小Ho该如何解决呢？

提示：推动科学发展的除了人的好奇心之外还有人的懒惰心！

输入
每个测试点（输入文件）有且仅有一组测试数据。
每组测试数据的第1行为一个整数N，意义如前文所述。
每组测试数据的第2行为N个整数，分别描述每种商品的重量，其中第i个整数表示标号为i的商品的重量Pi。
每组测试数据的第3行为一个整数Q，表示小Hi进行的操作数。
每组测试数据的第N+4~N+Q+3行，每行分别描述一次操作，每行的开头均为一个属于0或1的数字，分别表示该行描述一个询问和
一次商品的价格的更改两种情况。对于第N+i+3行，如果该行描述一个询问，则接下来为两个整数Li, Ri，表示小Hi询问的一个
区间[Li, Ri]；如果该行描述一次商品的价格的更改，则接下来为三个整数Li，Ri，NewP，表示标号在区间[Li, Ri]的商品的
价格全部修改为NewP。

对于100%的数据，满足N<=10^5，Q<=10^5, 1<=Li<=Ri<=N，1<=Pi<=N, 0<Pi, NewP<=10^4。

输出
对于每组测试数据，对于每个小Hi的询问，按照在输入中出现的顺序，各输出一行，表示查询的结果：标号在区间[Li, Ri]中的
所有商品的价格之和。

样例输入
10
4733 6570 8363 7391 4511 1433 2281 187 5166 378 
6
1 5 10 1577
1 1 7 3649
0 8 10
0 1 4
1 6 8 157
1 3 4 1557

样例输出
4731
14596

解题思路：
1.每个区间结点记录该区间的区间和。
2.修改区间值的时候，用懒惰标记记录最后(最下面)一个修改的结点，表示该结点下面的结点的信息暂时还不修改。
3.当往下走的时候，不管是修改还是查询，如果途中遇到某个结点的懒惰标记为true, 则需要向下同步该结点的信息，否则会出错。
*/

#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 1e5+5;

struct Node
{
    int L, R, val, sum;
    int lazy_set; //向下同步标记
};

struct SegTree
{
    Node a[maxn<<2];

    //获取区间中值
    inline int Mid(int rt){ return a[rt].L + (a[rt].R - a[rt].L ) / 2; }
    inline int Mid(int L, int R){ return L + (R- L)/2; }
    inline int Len(int rt){ return a[rt].R - a[rt].L + 1; }

    //建立线段树
    void build(int L, int R, int rt=1)
    {
        a[rt].L = L;
        a[rt].R = R;
        a[rt].sum = a[rt].lazy_set = a[rt].val= 0;
        if(L == R)
        {
            scanf("%d",&a[rt].val);
            a[rt].sum = a[rt].val;
            return ;
        } 
        int mid = Mid(L,R);
        build(L, mid, rt<<1);
        build(mid+1, R, rt<<1|1);
        push_up(rt);
    }

    inline void push_up(int rt){ a[rt].sum = a[rt<<1].sum + a[rt<<1|1].sum;  }
    
    //将区间[L,R]的值修改为val.
    //向上走的时候，如果遇到了懒惰标记，要将懒惰标记向下传递，否则会出现修改错误
    //回溯的时候，要将更新的信息向上同步
    void insert(int L, int R, int val, int rt=1)
    {
        if(a[rt].lazy_set) push_down(rt);
        if(L <= a[rt].L  && a[rt].R <= R)
        {
            a[rt].val = val;
            a[rt].sum = Len(rt) * val;
            a[rt].lazy_set = val;
            return;
        }
        int mid = Mid(rt);
        if(R <= mid) insert(L, R, val, rt<<1);
        else if(mid < L) insert(L, R, val, rt<<1|1);
        else 
        {
            insert(L, R, val ,rt<<1);
            insert(L, R, val, rt<<1|1);
        }
        push_up(rt);
    }

    //向下同步更新，并将懒惰同步标记传递给左右子结点
    void push_down(int rt)
    {
        if(a[rt].L == a[rt].R) return; //已经到达叶子结点，不需要往下同步
        int lc = rt<<1, rc=lc+1;
        a[lc].val = a[lc].lazy_set = a[rt].lazy_set; //set标记向下传递
        a[rc].val = a[rc].lazy_set = a[rt].lazy_set;
        a[lc].sum = Len(lc) * a[rt].val;
        a[rc].sum = Len(rc) * a[rt].val;
        a[rt].lazy_set = 0;
    }

    //区间查询
    int query(int L, int R, int rt=1)
    {
        if(a[rt].lazy_set) push_down(rt);
        if(L <= a[rt].L && a[rt].R <= R) return a[rt].sum;
        int mid = Mid(rt);
        if(R <= mid) return query(L, R, rt<<1);
        else if(mid < L) return query(L, R, rt<<1|1);
        else return query(L, R, rt<<1) + query(L, R, rt<<1|1);
    }

    void dfs(int rt)
    {
        if(a[rt].L)
        {
            dfs(rt<<1);
            dfs(rt<<1|1);
            printf("rt=%d  L=%d  R=%d  val=%d, sum=%d\n", rt,a[rt].L, a[rt].R, a[rt].val, a[rt].sum);
        } 
    }

}tree;


int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    int N, Q, val;
    int op, x, y;
    scanf("%d",&N);
    tree.build(1, N);

    scanf("%d",&Q);
    while(Q--)
    {
        scanf("%d", &op);
        if(op == 1)
        {
            scanf("%d%d%d",&x,&y,&val);
            tree.insert(x, y ,val);
        }
        else
        {
            scanf("%d%d",&x,&y);
            printf("%d\n", tree.query(x, y));
        }
    }

    return 0;
}
