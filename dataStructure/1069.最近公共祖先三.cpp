/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
上上回说到，小Hi和小Ho使用了Tarjan算法来优化了他们的“最近公共祖先”网站，但是很快这样一个离线算法就出现了问题：
如果只有一个人提出了询问，那么小Hi和小Ho很难决定到底是针对这个询问就直接进行计算还是等待一定数量的询问一起计算。
毕竟无论是一个询问还是很多个询问，使用离线算法都是只需要做一次深度优先搜索就可以了的。

那么问题就来了，如果每次计算都只针对一个询问进行的话，那么这样的算法事实上还不如使用最开始的朴素算法呢！但是如果
每次要等上很多人一起的话，因为说不准什么时候才能够凑够人——所以事实上有可能要等上很久很久才能够进行一次计算，实际
上也是很慢的！

“那到底要怎么办呢？在等到10分钟，或者凑够一定数量的人两个条件满足一个时就进行运算？”小Ho想出了一个折衷的办法。

“哪有这么麻烦！别忘了和离线算法相对应的可是有一个叫做在线算法的东西呢！”小Hi笑道。

小Ho面临的问题还是和之前一样：假设现在小Ho现在知道了N对父子关系——父亲和儿子的名字，并且这N对父子关系中涉及的所
有人都拥有一个共同的祖先（这个祖先出现在这N对父子关系中），他需要对于小Hi的若干次提问——每次提问为两个人的名字
（这两个人的名字在之前的父子关系中出现过），告诉小Hi这两个人的所有共同祖先中辈分最低的一个是谁？

提示：最近公共祖先无非就是两点连通路径上高度最小的点嘛！

输入
每个测试点（输入文件）有且仅有一组测试数据。
每组测试数据的第1行为一个整数N，意义如前文所述。
每组测试数据的第2~N+1行，每行分别描述一对父子关系，其中第i+1行为两个由大小写字母组成的字符串Father_i, Son_i，
分别表示父亲的名字和儿子的名字。每组测试数据的第N+2行为一个整数M，表示小Hi总共询问的次数。
每组测试数据的第N+3~N+M+2行，每行分别描述一个询问，其中第N+i+2行为两个由大小写字母组成的字符串Name1_i, Name2_i，
分别表示小Hi询问中的两个名字。
对于100%的数据，满足N<=10^5，M<=10^5, 且数据中所有涉及的人物中不存在两个名字相同的人（即姓名唯一的确定了一个人），
所有询问中出现过的名字均在之前所描述的N对父子关系中出现过，且每个输入文件中第一个出现的名字所确定的人是其他所有人
的公共祖先。

输出
对于每组测试数据，对于每个小Hi的询问，按照在输入中出现的顺序，各输出一行，表示查询的结果：他们的所有共同祖先中辈
分最低的一个人的名字。

样例输入
4
Adam Sam
Sam Joey
Sam Micheal
Adam Kevin
3
Sam Sam
Adam Sam
Micheal Kevin

样例输出
Sam
Adam
Adam

解题思路：
    Adame
    /   \
  Sam  Kevin
  /  \
Joey  Micheal

首先用深度优先遍历将树转化为数组序列seq, seq[i]=k 就表示序号为i的结点的编号为k,
然后记录下离开某个结点时该结点在序列中的序号，例如RID[k]=i表示编号为k的结点
在序列seq中最后一次出现的位置为i.
然后用RMQ-ST算法预处理序列seq,根据dep[ seq[i] ]，即结点seq[i]的深度，作为求极值的
依据。
在查询时，根据输入的名字name1,name2查找对应的名字的ID[name1],ID[name2]，然后
根据查找到的ID得到两个ID在seq序列中最后出现的序号，较小的作为L,较大的作为R,
在区间[L,R]中深度值最小的结点即为L,R的最近公共祖先。

test output:
  idx : 1 name:Adam
   idx : 2 name:Sam
    idx : 3 name:Joey
   idx : 4 name:Sam
    idx : 5 name:Micheal
   idx : 6 name:Sam
  idx : 7 name:Adam
   idx : 8 name:Kevin
  idx : 9 name:Adam
index:1 2 3 2 4 2 1 5 1
depth:
Adam 1
Sam 2
Joey 3
Micheal 3
Kevin 2

L:6 R:6 Sam
ret:2
L:6 R:9 Adam
ret:1
L:5 R:8 Adam
ret:1
0 0 0 0 0
1 1 1 1 0
2 2 2 1 0
3 2 2 0 0
2 2 1 0 0
4 2 1 0 0
2 1 1 0 0
1 1 0 0 0
5 1 0 0 0
1 0 0 0 0

*/

#include<iostream>
#include<cstdio>
#include<map>
#include<vector>
using namespace std;
const int maxn = 1e5+5;

vector<int> g[maxn]; // store the tree structure
map<string, int> ID; // name to id
string name[maxn];   // id to name
int seq[maxn<<2];    // seq[i]保存DFS序列中第i个序号所对应结点的ID
int RID[maxn<<2];    // RID[i]保存DFS遍历时离开结点i时的idx值
int dep[maxn];       //dep[i] is the depth of node i
int id,idx;

int st[maxn][20];    //ST[i][j] 保存seq中从序号i开始的连续2^j个序号中dep值最小的id

void DFS(int u,int d)
{
    // printf("cur : %d name:%s\n",u, name[u].c_str());
    dep[u] = d;
    for(int i=0,n=g[u].size(); i<n; ++i)
    {
        seq[++idx] = u; //开始访问下一个结点时
        // printf("%s idx : %d name:%s\n",string(d,' ').c_str(), idx, name[u].c_str());
        DFS( g[u][i], d+1);
    }
    seq[++idx] = u; //离开结点u时的序号
    // printf("%s idx : %d name:%s\n",string(d,' ').c_str(), idx, name[u].c_str());
    RID[u] = idx;
}

void init_RMQ(int n)
{
    for(int i=0; i<=n; ++i)
    {
        st[i][0] = seq[i];
    }
    for(int j=1; j<=20; ++j)
    {
        for(int i=1; i+(1<<j)-1 <= n; ++i)
        {
            if(dep[ st[i][j-1] ] < dep[ st[i+(1<<(j-1))][j-1] ] )
                st[i][j] = st[i][j-1];
            else
                st[i][j] = st[i+(1<<(j-1))][j-1];
        }
    }
}

int RMQ(int L,int R)
{
    int Len = R - L + 1, k=0;
    while((1<<(k+1)) <= Len) ++k;
    return min( st[L][k], st[R - (1<<k) + 1][k] );
}


int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    int N,M;
    int f_id, s_id;
    string father,son;
    scanf("%d", &N);
    while(N--)
    {
        cin>>father>>son;
        ID.count(father) ? f_id = ID[father] : ID[father] = f_id = ++id;
        ID.count(son) ? s_id = ID[son] : ID[son] = s_id = ++id;
        g[f_id].push_back(s_id);
        name[f_id] = father;
        name[s_id] = son;
    }

    string name1,name2;
    DFS(1,1);

    // printf("index:");
    // for(int i=1; i<=idx; ++i) printf("%d ", seq[i]);
    // cout<<endl;

    // printf("depth:\n");
    // for(int i=1; i<=id; ++i) printf("%s %d\n", name[i].c_str(), dep[i]);
    // cout<<endl;

    init_RMQ(idx);

    scanf("%d",&M);
    while(M--)
    {
        int ret;
        cin>>name1>>name2;
        int L = RID[ ID[name1] ];
        int R = RID[ ID[name2] ];
        if(L > R) swap(L, R);
        cout<<name[ RMQ(L,R) ]<<endl;
        // cout<<"L:"<<L<<" R:"<<R<<" "<<name[ ret=RMQ(L, R) ]<<endl;
        // printf("ret:%d\n",ret);
    }

    // for(int i=0; i<=idx; ++i)
    // {
    //     for(int j=0; j<5; ++j) printf("%d ",st[i][j]);
    //     printf("\n");
    // }

    return 0;
}