/*
时间限制:1000ms
单点时限:1000ms
内存限制:256MB
描述
小Hi和小Ho是一对好朋友，出生在信息化社会的他们对编程产生了莫大的兴趣，他们约定好互相帮助，在编程的学习道路上一同前进。
这一天，他们遇到了一只河蟹，于是河蟹就向小Hi和小Ho提出了那个经典的问题：“小Hi和小Ho，你们能不能够判断一段文字（原串）
里面是不是存在那么一些……特殊……的文字（模式串）？”

小Hi和小Ho仔细思考了一下，觉得只能想到很简单的做法，但是又觉得既然河蟹先生这么说了，就肯定不会这么容易的让他们回答了，
于是他们只能说道：“抱歉，河蟹先生，我们只能想到时间复杂度为（文本长度 * 特殊文字总长度）的方法，即对于每个模式串分开判断，
然后依次枚举起始位置并检查是否能够匹配，但是这不是您想要的方法是吧？”

河蟹点了点头，说道：”看来你们的水平还有待提高，这样吧，如果我说只有一个特殊文字，你能不能做到呢？“
小Ho这时候还有点晕晕乎乎的，但是小Hi很快开口道：”我知道！这就是一个很经典的模式匹配问题！可以使用KMP算法进行求解！“
河蟹满意的点了点头，对小Hi说道：”既然你知道就好办了，你去把小Ho教会，下周我有重要的任务交给你们！“

”保证完成任务！”小Hi点头道。

输入
第一行一个整数N，表示测试数据组数。
接下来的N*2行，每两行表示一个测试数据。在每一个测试数据中，第一行为模式串，由不超过10^4个大写字母组成，第二行为原串，
由不超过10^6个大写字母组成。其中N<=20

输出
对于每一个测试数据，按照它们在输入中出现的顺序输出一行Ans，表示模式串在原串中出现的次数。

样例输入
5
HA
HAHAHA
WQN
WQN
ADA
ADADADA
BABABB
BABABABABABABABABB
DAD
ADDAADAADDAAADAAD

样例输出
3
1
3
1
0

解题思路：
ADA
ADADADA
对于该测试样例，next数组的值(未优化)为:[-1,0,0,1]
p="ADA",s="ADADADA"
i=j=0
i=0,j=0: s[i]=p[j]='A', ++i,++j
i=1,j=1: s[i]=p[j]='D', ++i,++j
i=2,j=2: s[i]=p[j]='A', ++i,++j,++cnt
i=3,j=3: s[i]='D', p[j]='\0', j=next[j]=1

i=3,j=1: s[i]=p[j]='D', ++i,++j
i=4,j=2: s[i]=p[j]='A', ++i,++j,++cnt
i=5,j=3: s[i]='D', p[j]='\0', j=next[j]=1

i=5,j=1: s[i]=p[j]='D', ++i,++j
i=6,j=2: s[i]=p[j]='A', ++i,++j,++cnt
i=7,j=3: break
cnt=3
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
const int maxp = 1e4+5;
const int maxs = 1e6+5;

int _next[maxp];
char src[maxs], pat[maxp];

void cal_next(const char* p, int next[]){
    next[0] = -1;
    for(int i=0, k=-1; p[i]; ){
        if( k==-1 || p[k] == p[i]){
            next[++i] = ++k;
            //优化，可不要，该for循环只会执行一次。
            for(int t=i; t>-1 && p[t]==p[next[t]]; next[t]=next[next[t]]);
        }else { k = next[k]; }
    }
}

int count(const char* s, const char* p, int next[]){
    int cnt = 0, n2=strlen(p);
    for(int i=0,j=0; s[i]; ){
        if(j==-1 || s[i] == p[j]){
            ++i; ++j;
            if(j == n2) ++cnt;
        }else{
            j = next[j];
        }
    }
    return cnt;
}

int main(){
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%s%s",pat,src);
        cal_next(pat, _next);
        for(int i=0;i<5;++i) printf("%d ",_next[i]);
        printf("\n");
        printf("%d\n",count(src, pat, _next));
    }

    return 0;
}