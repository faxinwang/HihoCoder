/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
小Hi和小Ho是一对好朋友，出生在信息化社会的他们对编程产生了莫大的兴趣，他们约定好互相帮助，在编程的学习道路上一同前进。
这一天，他们遇到了一本词典，于是小Hi就向小Ho提出了那个经典的问题：“小Ho，你能不能对于每一个我给出的字符串，都在这个词
典里面找到以这个字符串开头的所有单词呢？”

身经百战的小Ho答道：“怎么会不能呢！你每给我一个字符串，我就依次遍历词典里的所有单词，检查你给我的字符串是不是这个单词的
前缀不就是了？”

小Hi笑道：“你啊，还是太年轻了！~假设这本词典里有10万个单词，我询问你一万次，你得要算到哪年哪月去？”

小Ho低头算了一算，看着那一堆堆的0，顿时感觉自己这辈子都要花在上面了...

小Hi看着小Ho的囧样，也是继续笑道：“让我来提高一下你的知识水平吧~你知道树这样一种数据结构么？”

小Ho想了想，说道：“知道~它是一种基础的数据结构，就像这里说的一样！”

小Hi满意的点了点头，说道：“那你知道我怎么样用一棵树来表示整个词典么？”

小Ho摇摇头表示自己不清楚。

“你看，我们现在得到了这样一棵树，那么你看，如果我给你一个字符串ap，你要怎么找到所有以ap开头的单词呢？”小Hi又开始考校小Ho。

“唔...一个个遍历所有的单词？”小Ho还是不忘自己最开始提出来的算法。

“笨！这棵树难道就白构建了！”小Hi教训完小Ho，继续道：“看好了！”

“那么现在！赶紧去用代码实现吧！”小Hi如是说道

输入
输入的第一行为一个正整数n，表示词典的大小，其后n行，每一行一个单词（不保证是英文单词，也有可能是火星文单词哦），单词由
不超过10个的小写英文字母组成，可能存在相同的单词，此时应将其视作不同的单词。接下来的一行为一个正整数m，表示小Hi询问的次数，
其后m行，每一行一个字符串，该字符串由不超过10个的小写英文字母组成，表示小Hi的一个询问。

在20%的数据中n, m<=10，词典的字母表大小<=2.
在60%的数据中n, m<=1000，词典的字母表大小<=5.
在100%的数据中n, m<=100000，词典的字母表大小<=26.

输出
对于小Hi的每一个询问，输出一个整数Ans,表示词典中以小Hi给出的字符串为前缀的单词的个数。

样例输入
5
babaab
babbbaaaa
abba
aaaaabaa
babaababb
5
babb
baabaaa
bab
bb
bbabbaab

样例输出
1
0
3
0
0

解题思路：
本题主要是根据输入数据建立起前缀树，在建立前缀树的同时也统计了以任何一个可能的前缀
为前缀的单词的个数。
插入单词的时间复杂度为单词ward的长度：O(len(word))
查询以给定前缀为前缀的单词的个数的时间复杂度为前缀pre的长度: O(len(pre))

*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;

//前缀树结点，相当于26叉树
struct TrieNode{
    char ch;
    bool end;//标记到此为止是一个单词
    int childCnt; //记录以该结点为前缀的单词的个数
    TrieNode* sub[26];
    TrieNode(char c):ch(c),childCnt(0),end(0){ memset(sub,0,sizeof(sub)); }
};

//前缀树
class Trie{
private:
    TrieNode* _root;
public:
    Trie(){
        _root = new TrieNode('0');
    }

    /*
    做算法题，为了效率，所以不做释放内存的操作。但在真正做工程应用的时候必须
    在析构的时候释放内存，否则会存在内存泄露。
    */
    ~Trie(){
        // clear(_root);
    }


    void insert(char* s){ insert(_root,s); }
    /*
    1.插入单词到Trie树中，沿着单词的路径往下走，当路径上代表某个字母
    的结点不存在时，就创建该结点。
    2.对于每一个插入的单词word，它都有len(word)个前缀(包括其自身),
    而且这些前缀中的某些前缀还可能是其他单词的前缀，例如对于单词smile和
    其前缀smi,在单词smile插入完成以后，smi至少存在一个以其为前缀的单词smile,
    所以在沿着路径往下走的时候，以每一个结点所表示的前缀的单词个数都应该+1。
    这样在任何时刻，都可以知道任何一个前缀所对应的单词有多少个。
    */
    void insert(TrieNode* rt, char* s){
        if(*s){
            int k = *s - 'a';
            if(!rt->sub[k]) rt->sub[k] = new TrieNode(*s);
            insert(rt->sub[k],s+1);
        }
		++(rt->childCnt); //以到此为前缀的单词数+1
    }

    //获取以给定字符串为前缀的单词的个数，TC=O(len(s))
    int getCount(char* s){
        TrieNode* p = _root;
        while(p && *s){
            p = p->sub[*s - 'a'];
            ++s;
        }
        return p? p->childCnt : 0;
    }
    
    void printAll(){ DFS(_root,""); }
    //遍历所有结点，输出所有单词。
    void DFS(TrieNode* rt,string str){
        for(int i=0; i<26; ++i) if(rt->sub[i]){
        	DFS(rt->sub[i], str + char('a' + i));
        }
		if(rt->end) cout<<str<<endl;
    }

    
    void clear(TrieNode* rt){
        if(rt){
            for(int i=0; i<26; ++i){
                clear(rt->sub[i]);
                delete rt->sub[i];
            } 
            delete rt;
        }
    }
};

int main(){
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    char s[10];
    int n,m;
    scanf("%d",&n);
    Trie trie;
    for(int i=0; i<n; ++i){
        scanf("%s",s);
        trie.insert(s);
    }
     scanf("%d",&m);
     for(int i=0; i<m; ++i){
         scanf("%s",s);
         printf("%d\n",trie.getCount(s));
     }
//    trie.printAll();

    return 0;
}
