/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
小Ho：小Hi，上次我学会了如何检测一个数是否是质数。于是我又有了一个新的问题，
我如何去快速得求解[1,N]这个区间内素数的个数呢？

小Hi：你自己有什么想法么？

小Ho：有！我一开始的想法是，自然我们已经知道了如何快速判定一个数是否是质数，
那么我就直接将[1,N]之间每一个数判定一次，就可以得到结果。但我发现这个方法太笨了。

小Hi：确实呢，虽然我们已经通过快速素数检测将每一次判定的时间复杂度降低，但是
N个数字的话，总的时间复杂度依旧很高。

小Ho：是的，所以后来我改变了我的算法。我发现如果一个数p是质数的话，那么它的倍
数一定都是质数。所以我建立了一个布尔类型的数组isPrime，初始化都为true。我从2开
始枚举，当我找到一个isPrime[p]仍然为true时，可以确定p一定是一个质数。接着我再
将N以内所有p的倍数全部设定为isPrime[p*i]=false。

写成伪代码为：

isPrime[] = true
primeCount = 0
For i = 2 .. N
	If isPrime[i] Then
		primeCount = primeCount + 1
		multiple = 2
		While (i * multiple ≤ N)
			isPrime[i * multiple] = false
			multiple = multiple + 1
		End While 
	End If
End For
  
小Hi：小Ho你用的这个算法叫做Eratosthenes筛法，是一种非常古老的质数筛选算法。
其时间复杂度为O(n log log n)。但是这个算法有一个冗余的地方：比如合数10，在
枚举2的时候我们判定了一次，在枚举5的时候我们又判定了一次。因此使得其时间复杂
度比O(n)要高。

小Ho：那有没有什么办法可以避免啊？
小Hi：当然有了，一个改进的方法叫做Eular筛法，其时间复杂度是O(n)的。

--------------------------------------------------------------
提示：Eular质数筛法
小Hi：我们可以知道，任意一个正整数k，若k≥2，则k可以表示成若干个质数相乘的形式。
Eratosthenes筛法中，在枚举k的每一个质因子时，我们都计算了一次k，从而造成了冗余。
因此在改进算法中，只利用k的最小质因子去计算一次k。

首先让我们了解一下Eular筛法，其伪代码为：

isPrime[] = true
primeList = []
primeCount = 0
For i = 2 .. N
	If isPrime[i] Then
		primeCount = primeCount + 1
		primeList[ primeCount ] = i
	End If 
	For j = 1 .. primeCount
		If (i * primeList[j] > N) Then
			Break
		End If
		isPrime[ i * primeList[j] ] = false
		If (i % primeList[j] == 0) Then
			Break
		End If
	End If
End For
	
与Eratosthenes筛法不同的是，对于外层枚举i，无论i是质数，还是是合数，我们都会用i的
倍数去筛。但在枚举的时候，我们只枚举i的质数倍。比如2i,3i,5i,...，而不去枚举4i,6i...，
原因我们后面会讲到。

此外，在从小到大依次枚举质数p来计算i的倍数时，我们还需要检查i是否能够整除p。若i能够整
除p，则停止枚举。

利用该算法，可以保证每个合数只会被枚举到一次。我们可以证明如下命题：

假设一个合数k=M*p1，p1为其最小的质因子。则k只会在i=M，primeList[j]=p1时被筛掉一次。

首先会在i=M，primeList[j]=p1时被筛掉是显然的。因为p1是k的最小质因子，所以i=M的所有质
因子也≥p1。于是j循环在枚举到primeList[j]=p1前不会break，从而一定会在i=M，primeList[j]=p1
时被筛掉

其次不会在其他时候被筛掉。否则假设k在i=N, primeList[j]=p1时被筛掉了，此时有k=N*p2。
由于p1是k最小的质因子，所以p2 > p1，M > N且p|N。则i=N，j枚举到primeList[j]=p1时
(没到primeList[j]=p2)就break了。所以不会有其他时候筛掉k。

同时，不枚举合数倍数的原因也在此：对于一个合数k=M*2*3。只有在枚举到i=M*3时，才会计算到k。
若我们枚举合数倍数，则可能会在i=M时，通过M*6计算到k，这样也就造成了多次重复计算了。

综上，Eular筛法可以保证每个合数只会被枚举到一次，时间复杂度为O(n)。当N越大时，其相对于
Eratosthenes筛法的优势也就越明显。
--------------------------------------------------------------

输入
第1行：1个正整数n，表示数字的个数，2≤n≤1,000,000。

输出
第1行：1个整数，表示从1到n中质数的个数

样例输入
9
样例输出
4

*/


#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 1e6+5;
typedef long long LL;

int a[maxn], p[maxn];

//O(n), 返回n以内的素数个数
int eular_prime_sieve(int n)
{
    int cnt=0;
    for(int i=2; i<=n; ++i)
    {
        if(a[i]==0) p[cnt++] = i;
        for(int j=0; j<cnt; ++j)
        {
            if(i * p[j] > n) break;
            a[ i*p[j] ] = 1;
            if(i % p[j] == 0) break;
        }
    }
    return cnt;
}

//O(nloglogn), 返回n以内的素数个数
int prime_sieve(int n)
{
	int cnt=0;
	// for(int i=2,k=4; k<=n; ++i, k+=i+i-1)
	for(LL i=2; i<=n ; ++i)
	{
		if(a[i] == 0)
		{
			// ++cnt;
			p[cnt++] = i;
			//这里j一定要用LL, 否则i*i会发生溢出
			for(LL j=i*i; j<=n; j+=i) a[j] = 1;
		}
	}
	return cnt;
}


int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif
    int n;
    scanf("%d",&n);
    printf("%d\n", eular_prime_sieve(n));
	// printf("%d\n", n = prime_sieve(n));
    return 0;
}