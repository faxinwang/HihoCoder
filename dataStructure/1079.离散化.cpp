/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
小Hi和小Ho在回国之后，重新过起了朝7晚5的学生生活，当然了，他们还是在一直学习着各种算法~

这天小Hi和小Ho所在的学校举办社团文化节，各大社团都在宣传栏上贴起了海报，但是贴来贴去，有些海报就会被其他社团的海报
所遮挡住。看到这个场景，小Hi便产生了这样的一个疑问——最后到底能有几张海报还能被看见呢？

于是小Ho肩负起了解决这个问题的责任：因为宣传栏和海报的高度都是一样的，所以宣传栏可以被视作长度为L的一段区间，且有
N张海报按照顺序依次贴在了宣传栏上，其中第i张海报贴住的范围可以用一段区间[a_i, b_i]表示，其中a_i, b_i均为属于[0, L]
的整数，而一张海报能被看到当且仅当存在长度大于0的一部分没有被后来贴的海报所遮挡住。那么问题就来了：究竟有几张海报能
被看到呢？

----------------------------------------------------
提示一：正确的认识信息量

提示二：小Hi大讲堂之线段树的节点意义
在线段树的通常用法中，线段树的节点是有2种不同的意义的，一种是离散型的，比如在Hiho一下 第二十周中，
一个节点虽然描述的是一个区间[3, 9]，但是实际上这样一个区间是{3, 4, 5, 6, 7, 8, 9}这样的意义。而
另一种就是连续型的，比如就在这一周的问题中，一个节点如果描述的是一个区间[3, 9]，它就确确实实描述
的是在数轴上从3这个标记到9这个标记的这一段。

那么有的小朋友可能就要问了，这两种不同的意义有什么区别呢？

在小Hi看来，其实只有这样的几个区别：
1.叶子节点：在离散型中，叶子节点是[i, i]，而连续性中是[i, i + 1]；
2.分解区间：在离散型中，一段区间是分解成为[l, m], [m + 1, r]，而在连续型中，是分解成为[l, m], [m, r]；
3.在离散区间中，区间长度为 R-L+1, 而在连续区间中，区间长度为 R-L；
4.其他所有类似的判定问题。
----------------------------------------------------

输入
每个测试点（输入文件）有且仅有一组测试数据。

每组测试数据的第1行为两个整数N和L，分别表示总共贴上的海报数量和宣传栏的宽度。

每组测试数据的第2-N+1行，按照贴上去的先后顺序，每行描述一张海报，其中第i+1行为两个整数a_i, b_i，表示第i张海报所贴的
区间为[a_i, b_i]。

对于100%的数据，满足N<=10^5，L<=10^9，0<=a_i<b_i<=L。

输出
对于每组测试数据，输出一个整数Ans，表示总共有多少张海报能被看到。

样例输入
5 10
4 10
0 2
1 6
5 9
3 4

样例输出
5

解题思路：
之前在POJ上面做过这个题目，那时候线段树写得不是很熟练，也不知道离散区间和连续区间有什么差别，
现在总算是搞懂了。上面题目的提示中已经说明了离散区间和连续区间的区别，这里只说一下离散化需要注意的
问题吧，之前很多人都说离散化的时候，如果原来两个数字之间的差大于1, 那么离散化之后这两个数字之间的差
也要大于1，这是因为这样做的人使用的是离散区间，如果使用连续区间，就不存在这个问题。原因如下：
对于这样几张海报：[1,10],[1,3],[6,10]
如果使用离散区间，就要离散成[1,7],[1,3],[5,7],这样[1,7]这个区间才不会被覆盖掉，而如果离散成了
[1,4],[1,2],[3,4]的话，那么[1,4](长度为4)这个区间就被[1,2]和[3,4]这两个长度为2区间覆盖了，最后
可见的海报就变成2个了。但时如果线段树使用的是连续区间的话，那么在离散成[1,4],[1,2],[3,4]这三个区间后，
[1,4]区间的长度为3, [1,2]和[3,4]这两个区间的长度均为1, [1,4]区间还有[2,3]这个区间没有被覆盖，所以最后
可见的海报依然是3个。
*/

#include<iostream>
#include<cstdio>
#include<set>
#include<map>
using namespace std;
const int maxn = 1e5+5;

map<int,int> mp; //用于区间离散化
pair<int,int> poster[maxn]; //保存海报原始区间

struct Node
{
    int L, R, sum; //sum表示这段区间中被覆盖的长度
    bool asyn; //懒惰标记
};

struct SegTree
{
    Node a[maxn<<2];
    int Mid(int rt) { return a[rt].L + (a[rt].R - a[rt].L)/2; }
    
    //这次建立的是连续区间,注意连续区间和离散区间之间的区别
    void build(int rt,int L, int R)
    {
        a[rt].L = L;
        a[rt].R = R;
        a[rt].sum = 0;
        a[rt].asyn = 0;
        if(L + 1 == R) return ;
        int mid = L + (R - L)/2;
        build(rt<<1, L, mid);
        build(rt<<1|1, mid, R);
    }

    void push_up(int rt){ a[rt].sum = a[rt<<1].sum + a[rt<<1|1].sum; }

    void insert(int rt, int L, int R, int val = 1)
    {
        if(a[rt].asyn) push_down(rt);
        if(a[rt].L == L && a[rt].R == R)
        {
            a[rt].sum = (R - L) * val;
            a[rt].asyn = 1;
            return;
        }
        int mid = Mid(rt);
        if( R <= mid ) insert(rt<<1, L, R, val);
        else if(mid <= L) insert(rt<<1|1, L, R, val);
        else
        {
            insert(rt<<1, L, mid,val);
            insert(rt<<1|1, mid, R, val);
        }
        push_up(rt);
    }

    void push_down(int rt)
    {
        if(a[rt].L +1 == a[rt].R) return; //叶子结点
        int lc = rt<<1, rc = lc+1;
        a[lc].asyn = 1;
        a[lc].sum = a[lc].R - a[lc].L;
        a[rc].asyn = 1;
        a[rc].sum = a[rc].R - a[rc].L;
        a[rt].asyn = 0;
    }

    int query(int rt, int L, int R)
    {
        if(a[rt].asyn) push_down(rt);
        if(a[rt].L == L && a[rt].R == R) return a[rt].sum;
        int mid = Mid(rt);
        if(R <= mid) return query(rt<<1, L, R);
        else if(mid <= L) return query(rt<<1|1, L, R);
        else return query(rt<<1, L, mid) + query(rt<<1|1, mid, R);
    }

}tree;

int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    int N,L;
    set<int> st;
    scanf("%d%d",&N,&L);
    for(int i=0; i<N; ++i)
    {
        scanf("%d%d", &poster[i].first, &poster[i].second);
        st.insert(poster[i].first);
        st.insert(poster[i].second);
    }

    //进行离散化
    set<int>::iterator pos = st.begin();
    int idx=0;
    for(; pos != st.end(); ++pos) mp[*pos] = ++idx;

    //用离散化之后的数据建立线段树
    tree.build(1, 0, idx);
    //逆向插入，如果当前海报的区间没有全部覆盖，则该张海报最终将是可见的。
    int ans = 0;
    for(int i=N-1; i>=0; --i)
    {
        int L = mp[poster[i].first];
        int R = mp[poster[i].second];
        int sum = tree.query(1, L, R);
        // printf("L=%d R=%d sum=%d\n", L, R, sum);
        if( sum < (R - L) ) //没有完全覆盖
        {
            ++ans; 
            tree.insert(1, L, R); //val 使用默认值1
        }
    }
    printf("%d\n", ans);

    return 0;
}
