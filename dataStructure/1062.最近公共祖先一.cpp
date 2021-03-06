/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
小Ho最近发现了一个神奇的网站！虽然还不够像58同城那样神奇，但这个网站仍然让小Ho乐在其中，但这是为什么呢？
“为什么呢？”小Hi如是问道，在他的观察中小Ho已经沉迷这个网站一周之久了，甚至连他心爱的树玩具都弃置一边。
“嘿嘿，小Hi，你快过来看！”小Ho招呼道。
“你看，在这个对话框里输入我的名字，在另一个对话框里，输入你的名字，再点这个查询按钮，就可以查出来……什么！
我们居然有同一个祖祖祖祖祖爷爷？”
“诶，真是诶……这个网站有点厉害啊。”小Hi不由感叹道。
“是啊，这是什么算法啊，这么厉害！”小Ho也附和道。
“别2，我说的是他能弄到这些数据很厉害，而人类的繁殖树这种层数比较浅的树对这类算法的要求可是简单的不得了，
你都能写出来呢！”小Hi道。
“啊？我也能写出来？可是……该从哪开始呢？”小Ho困惑了。
小Ho要面临的问题是这样的，假设现在他知道了N个人的信息——他们的父亲是谁，他需要对于小Hi的每一次提问——两个人的名字，
告诉小Hi这两个人的是否存在同一个祖先，如果存在，那么他们的所有共同祖先中辈分最低的一个是谁？

-------------------------------------------------------
提示:
“最简单的法子……如果数据量不大的话，我完全可以直接将这两个人的祖先全部找出来，然后取它们的交集，然后再找到其中辈分
最低的一个不就行了。”小Ho思考了会这般说道。
小Hi点了点头道：“差不多就是这样！当然你也先将一个人的祖先全都标记出来，然后顺着另一个的父亲一直向上找，直到找到第
一个被标记过的结点，便是它们的最近公共祖先结点了。”
-------------------------------------------------------

输入
每个测试点（输入文件）有且仅有一组测试数据。
每组测试数据的第1行为一个整数N，意义如前文所述。
每组测试数据的第2~N+1行，每行分别描述一对父子关系，其中第i+1行为两个由大小写字母组成的字符串Father_i, Son_i，分别表
示父亲的名字和儿子的名字。每组测试数据的第N+2行为一个整数M，表示小Hi总共询问的次数。每组测试数据的第N+3~N+M+2行，每
行分别描述一个询问，其中第N+i+2行为两个由大小写字母组成的字符串Name1_i, Name2_i，分别表示小Hi询问中的两个名字。
对于100%的数据，满足N<=10^2，M<=10^2, 且数据中所有涉及的人物中不存在两个名字相同的人（即姓名唯一的确定了一个人）。

输出
对于每组测试数据，对于每个小Hi的询问，输出一行，表示查询的结果：如果根据已知信息，可以判定询问中的两个人存在共同的祖先，
则输出他们的所有共同祖先中辈分最低的一个人的名字，否则输出-1。

样例输入
11
JiaYan JiaDaihua
JiaDaihua JiaFu
JiaDaihua JiaJing
JiaJing JiaZhen
JiaZhen JiaRong
JiaYuan JiaDaishan
JiaDaishan JiaShe
JiaDaishan JiaZheng
JiaShe JiaLian
JiaZheng JiaZhu
JiaZheng JiaBaoyu
3
JiaBaoyu JiaLian
JiaBaoyu JiaZheng
JiaBaoyu LinDaiyu

样例输出
JiaDaishan
JiaZheng
-1

解题思路:
用map<sting,string> f 保存父子关系, f[son] = father, 表示son的父亲是father。
在查找最近公共祖先时，先将第一个结点及其祖先结点均放入集合set<string> s中，然后从下往上
依次追随第二个结点的祖先结点。并查找该祖先是否存在集合s中，如果存在，则该祖先就是二者的最近
公共祖先。否则继续往上找。
*/

#include<iostream>
#include<cstdio>
#include<map>
#include<string>
#include<set>
using namespace std;

map<string,string> f; //保存父子关系 f[son] = father

int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    string father, son, name;
    int N,M;
    scanf("%d",&N);
    while(N--)
    {
        cin>>father>>son;
        f[son] = father;
    }

    scanf("%d",&M);
    while(M--)
    {
        set<string> s;
        cin>>name;
        while(f.count(name))
        {
            s.insert(name);
            name = f[name];
        }
        //循环退出之后，name的值依然是最开始输入名字的祖先，且是最远的祖先
        s.insert(name); 
        cin>>name;
        //开始寻找最近公共祖先
        bool found=false;
        while(f.count(name))
        {
            if(s.count(name))
            {
                found = 1;
                cout<<name<<endl;
                break;
            }
            name = f[name];
        }
        //循环退出之后，name的值依然是最开始输入名字的祖先，且是最远的祖先
        if(!found)
        {
            if(s.count(name)) 
            {
                found = 1;
                cout<<name<<endl;
            }
            else printf("-1\n");
        } 
    }
    return 0;
}