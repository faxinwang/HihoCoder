/*
时间限制:4000ms
单点时限:1000ms
内存限制:256MB
描述
现在有一个有n个元素的数组a1, a2, ..., an。

记f(i, j) = ai * ai+1 * ... * aj。

初始时，a1 = a2 = ... = an = 0，每次我会修改一个ai的值，你需要实时反馈给我 ∑1 <= i <= j <= n f(i, j)
的值 mod 10007。

输入
第一行包含两个数n(1<=n<=100000)和q(1<=q<=500000)。

接下来q行，每行包含两个数i, x，代表我把ai的值改为了x。

输出
分别输出对应的答案，一个答案占一行。

样例输入
5 5
1 1
2 1
3 1
4 1
5 1

样例输出
1
3
6
10
15

解题思路：
每个线段树结点中出保存区间端点外，还要保存如下信息：
int ans;  //区间内所有f(i,j)的和(1<=i<=j<=N)，例如如果区间为[1,2]，那就是f(1,1)+f(2,2)+f(1,2)
int LAns; //区间前缀积之和,例如对于区间A[1,3],其前缀乘积之和为A[1] + A[1]*A[2] + A[1]*A[2]*A[3]
int RAns; //区间后缀积之和,例如对于区间A[1,3],其后缀乘积之和为A[1]*A[2]*A[3] + A[2]*A[3] + A[3] 
int prod; //A[L]*A[L+1]*A[L+2]*...*A[R]

则当两个区间合并的时候：
int lc = rt<<1, rc = lc+1;
a[rt].ans = (a[lc].ans + a[rc].ans + a[lc].RAns * a[rc].LAns) % mod;
a[rt].LAns = (a[lc].LAns + a[lc].prod * a[rc].LAns) % mod;
a[rt].RAns = (a[rc].RAns + a[rc].prod * a[lc].RAns) % mod;
a[rt].prod = (a[lc].prod * a[rc].prod) % mod;

例如：
a[2,3] 与 a[4,5]合并的时候:
对于a[2,3]有(省略了数组名称)：
ans1 = 2 + 3 + 2*3
prod1 = 2*3
LAns1 = 2 + 2*3
RAns1 = 2 * 3 + 3

对于a[4,5]有：
ans2 = 4 + 5 + 4 * 5
prod2 = 4 * 5
LAns2 =  4 + 4 * 5
Rans2 = 4 * 5 + 5

则区间a[2,3]与a[4,5]合并得到a[2,3,4,5]，有：
ans = ans1 + ans2 +RAns1 * LAns2
    = 2 + 3 + 4 + 5
      + 2*3 + 4*5 + 3*4
      + 2*3*4 + 3*4*5
      + 2*3*4*5
prod = prod1 * prod2
     = 2*3*4*5
LAns = LAns1 + prod1 * LAns2
     = 2 + 2*3 + 2*3*4 + 2*3+4*5
RAns = RAns2 + prod2 * RAns1
     = 5 + 4*5 + 3*4*5 + 2*3*4*5
*/


#include<iostream>
#include<cstdio>
const int maxn = 100005;
const int mod = 10007;
struct Node
{
    int L,R;
    int ans;  //区间内所有f(i,j)的和(1<=i<=j<=N)，例如如果区间为[1,2]，那就是f(1,1)+f(2,2)+f(1,2)
    int LAns; //所有前缀积之和
    int RAns; //来自后缀积之和
    int prod; //A[L]*A[L+1]*A[L+2]*...*A[R]
};

struct SegTree
{
    Node a[maxn<<2];
    int Mid(int rt){ return a[rt].L + (a[rt].R - a[rt].L)/2;}
    void build(int L, int R, int rt=1)
    {
        a[rt].L = L;
        a[rt].R = R;
        a[rt].LAns = a[rt].RAns = a[rt].prod = 0;
        if(L == R) return;
        int mid = Mid(rt);
        build(L, mid, rt<<1);
        build(mid+1, R, rt<<1|1);
    }

    void push_up(int rt)
    {
        int lc = rt<<1, rc = lc+1;
        a[rt].ans = (a[lc].ans + a[rc].ans + a[lc].RAns * a[rc].LAns) % mod;
        a[rt].LAns = (a[lc].LAns + a[lc].prod * a[rc].LAns) % mod;
        a[rt].RAns = (a[rc].RAns + a[rc].prod * a[lc].RAns) % mod;
        a[rt].prod = (a[lc].prod * a[rc].prod) % mod;
    }

    void insert(int pos, int val, int rt=1)
    {
        if(a[rt].L == a[rt].R)
        {
            a[rt].ans = a[rt].prod = a[rt].LAns = a[rt].RAns = val % mod;
            return;
        }
        int mid = Mid(rt);
        if(pos<=mid) insert(pos,val, rt<<1);
        else insert(pos,val, rt<<1|1);
        push_up(rt);
    }
}tree;

int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    int N,Q;
    int x,y;
    scanf("%d%d",&N, &Q);
    tree.build(1,N);
    while(Q--)
    {
        scanf("%d%d",&x,&y);
        tree.insert(x,y);
        printf("%d\n",tree.a[1].ans);
    }

    return 0;
}