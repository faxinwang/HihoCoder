/*
时间限制:1000ms
单点时限:1000ms
内存限制:256MB
描述
小Hi和小Ho正在进行一项基因工程实验。他们要修改一段长度为N的DNA序列，使得这段DNA上最前面的K个碱基组成的序列与最后面
的K个碱基组成的序列完全一致。例如对于序列"ATCGATAC"和K=2,可以通过将第二个碱基修改为"C"使得最前面2个碱基与最后面两
个碱基都为"AC"。当然还存在其他修改方法，例如将最后一个碱基改为"T"，或者直接将最前面两个和最后面两个碱基都修改为"GG"。
小Hi和小Ho希望知道在所有方法中，修改碱基最少的方法需要修改多少个碱基。

输入
第一行包含一个整数T(1 <= T <= 10)，代表测试数据的数量。
每组测试数据包含2行，第一行是一个由"ATCG"4个大写字母组成的长度为N(1 <= N <= 1000)的字符串。第二行是一个整数K(1 <= K <= N)。

输出
对于每组数据输出最少需要修改的碱基数量。

样例输入
2  
ATCGATAC  
2  
ATACGTCT
6 

样例输出
1  
3 

解题思路：
参考：
https://www.cnblogs.com/boring09/p/4373492.html
http://blog.csdn.net/u010885899/article/details/46242729
http://blog.csdn.net/youb11/article/details/45890813

对于如下输入：
ABCDAB
4

这种比较是 ABCD 与 CDAB 比较，实际上就是字符串中的
0位与2位
1位与3位
2位与4位
3位与5位
比较。

之后的想法是把0 2 4 这样的分成一组，1 3 5这样的分成一组，因为这些的值都要相等，比如0 2 4位分别是A C A，只需把2中
的C变为A就行，实际上就是在这个组中要想相等就要少数服从多数，所以对于每组来说，求出每组出线最多的元素的次数，总的元
素数-最多的次数，意思就是让其他组员屈服，都等于我的值。



对于测试案例 ATACGTCT
s1 : A T A C G T
s2 : A C G T C T   
最少的修改应该是修改s2[1]为T，对应的此时s1[3]也改成了T；再修改s2[2]为A，对应s1[4]改为A；再修改s2[4]为A
把string扯直了，发现变成ATATATAT了，事后发现，原来是把string下标模(n-k)同余的都改成相同的字符就行了。而最
小的修改数量就是统计string下标同余的字符，找到该组频率最大的那个字符， 并把这组字符都变成频率最大的那个。

*/

#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 1005
using namespace std;

char s[maxn];
char a[]={"ATGC"};

int main(){
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    int T,k;
    scanf("%d",&T);
    while(T--){
        scanf("%s%d",s,&k);
        int N = strlen(s), len = N - k;
        int ans = 0;
        for(int i=0; i<len; ++i){
            int num[4]={0};
            for(int j=i; j<N; j+=len){
                for(int k=0; k<4;++k) if(a[k] == s[j]) ++num[k];
            }
            int _max=0, sum=0;
            for(int j=0; j<4; ++j){
                if(_max < num[j]) _max = num[j];
                sum += num[j];
            }
            ans += sum - _max;
        }
        printf("%d\n",ans);
    }

    return 0;
}