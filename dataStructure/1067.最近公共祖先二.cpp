/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
上上回说到，小Hi和小Ho用非常拙劣——或者说粗糙的手段山寨出了一个神奇的网站，这个网站可以计算出某两个人的所有共同祖先
中辈分最低的一个是谁。远在美国的他们利用了一些奇妙的技术获得了国内许多人的相关信息，并且搭建了一个小小的网站来应付
来自四面八方的请求。

但正如我们所能想象到的……这样一个简单的算法并不能支撑住非常大的访问量，所以摆在小Hi和小Ho面前的无非两种选择：

其一是购买更为昂贵的服务器，通过提高计算机性能的方式来满足需求——但小Hi和小Ho并没有那么多的钱；其二则是改进他们的算法，
通过提高计算机性能的利用率来满足需求——这个主意似乎听起来更加靠谱。

于是为了他们第一个在线产品的顺利运作，小Hi决定对小Ho进行紧急训练——好好的修改一番他们的算法。

而为了更好的向小Ho讲述这个问题，小Hi将这个问题抽象成了这个样子：假设现小Ho现在知道了N对父子关系——父亲和儿子的名字，
并且这N对父子关系中涉及的所有人都拥有一个共同的祖先（这个祖先出现在这N对父子关系中），他需要对于小Hi的若干次提问—
每次提问为两个人的名字（这两个人的名字在之前的父子关系中出现过），告诉小Hi这两个人的所有共同祖先中辈分最低的一个是谁？

提示一：老老实实分情况讨论就不会出错的啦！

提示二：并查集其实长得很像一棵树你们不觉得么？

输入
每个测试点（输入文件）有且仅有一组测试数据。
每组测试数据的第1行为一个整数N，意义如前文所述。
每组测试数据的第2~N+1行，每行分别描述一对父子关系，其中第i+1行为两个由大小写字母组成的字符串Father_i, Son_i，
分别表示父亲的名字和儿子的名字。每组测试数据的第N+2行为一个整数M，表示小Hi总共询问的次数。
每组测试数据的第N+3~N+M+2行，每行分别描述一个询问，其中第N+i+2行为两个由大小写字母组成的字符串Name1_i, Name2_i，
分别表示小Hi询问中的两个名字。
对于100%的数据，满足N<=10^5，M<=10^5, 且数据中所有涉及的人物中不存在两个名字相同的人（即姓名唯一的确定了一个人），
所有询问中出现过的名字均在之前所描述的N对父子关系中出现过，第一个出现的名字所确定的人是其他所有人的公共祖先。

输出
对于每组测试数据，对于每个小Hi的询问，按照在输入中出现的顺序，各输出一行，表示查询的结果：他们的所有共同祖先中辈分
最低的一个人的名字。

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

解题思路:
1.将所有名字转换为编号，用链接表来保存树结构。
2.对于树的深度优先遍历，每个节点会访问两次，第一次是达到该结点,将该结点染成灰色，第二次是离开该结点，将该结点染为黑色。
3.用并查集记录每个节点的父结点编号，在查询的时候再动态修改为记录每个节点的第一个灰色父结点。
4.由于需要按输入的顺序输出每个查询的答案，所以需要保存每个查询的输入顺序，最后按照输入的顺序输出答案。
*/

#include<iostream>
#include<cstdio>
#include<map>
#include<vector>
#include<string>
using namespace std;
const int maxn = 1e5+5;

struct Node{
    char color;
    string name;
    vector<int> child;
}tree[maxn]; //下标序号即为该结点的序号

map<string,int> ID;
vector<pair<int,int> > query[maxn];
int p[maxn]; //p[i] 保存结点i的第一个灰色父结点
int ans[maxn]; //ans[i]保存第i个询问的答案结点(也就是两个结点的最近公共祖先)的编号

int find(int x){
    if(tree[x].color == 1) return x;
    return p[x] = find( p[x] ); //路径压缩
}

void DFS(int u){
    ++tree[u].color; //gray
    for(int i=0,n=query[u].size(); i<n; ++i)
    {
        int v = query[u][i].first;
        int idx = query[u][i].second;
        if( ans[idx] ) continue; //u 与 v 的最近公共祖先已经计算出来了
        if( tree[v].color == 1 ) ans[idx] = v;
        else if( tree[v].color == 2 ) ans[idx] = find(v);
    }
    //dfs
    vector<int> &child = tree[u].child;
    for(int i=0, n=child.size(); i<n; ++i ) DFS(child[i]);
    ++tree[u].color; //black
}

int main(){
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    int N,M;
    int id=0, f_id, s_id;
    string father,son, name1,name2;
    scanf("%d", &N);
    while(N--)
    {
        cin>>father>>son;
        ID.count(father) ? f_id = ID[father] : ID[father] = f_id = ++id;
        ID.count(son) ? s_id = ID[son] : ID[son] = s_id = ++id;
        tree[f_id].name = father;
        tree[s_id].name = son;
        tree[f_id].child.push_back(s_id);
        p[s_id] = f_id;
    }

    scanf("%d",&M);
    for(int i=0;i<M; ++i)
    {
        cin>>name1>>name2;
        int id1 = ID[name1], id2 = ID[name2];
        query[id1].push_back(make_pair(id2, i)); //id1与id2是第i个查询
        query[id2].push_back(make_pair(id1, i));
    }
    DFS(1);
    for(int i=0; i<M; ++i) cout<<tree[ans[i]].name<<endl;

    return 0;
}