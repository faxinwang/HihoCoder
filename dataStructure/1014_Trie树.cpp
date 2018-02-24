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
