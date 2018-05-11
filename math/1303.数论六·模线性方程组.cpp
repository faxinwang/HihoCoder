/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
小Ho：今天我听到一个挺有意思的故事！

小Hi：什么故事啊？

小Ho：说秦末，刘邦的将军韩信带领1500名士兵经历了一场战斗，战死四百余人。韩信为了清点人
数让士兵站成三人一排，多出来两人；站成五人一排，多出来四人；站成七人一排，多出来六人。
韩信立刻就知道了剩余人数为1049人。

小Hi：韩信点兵嘛，这个故事很有名的。

小Ho：我觉得这里面一定有什么巧妙的计算方法！不然韩信不可能这么快计算出来。

小Hi：那我们不妨将这个故事的数学模型提取出来看看？

小Ho：好！

<小Ho稍微思考了一下>

小Ho：韩信是为了计算的是士兵的人数，那么我们设这个人数为x。三人成排，五人成排，七人成排，
即x mod 3, x mod 5, x mod 7。也就是说我们可以列出一组方程：

x mod 3 = 2
x mod 5 = 4
x mod 7 = 6
韩信就是根据这个方程组，解出了x的值。

小Hi：嗯，就是这样！我们将这个方程组推广到一般形式：给定了n组除数m[i]和余数r[i]，通过
这n组(m[i],r[i])求解一个x，使得x mod m[i] = r[i]。

小Ho：我怎么感觉这个方程组有固定的解法？

小Hi：这个方程组被称为模线性方程组。它确实有固定的解决方法。不过在我告诉你解法之前，你
不如先自己想想怎么求解如何？

小Ho：好啊，让我先试试啊！

----------------------------------------------------------
提示：模线性方程组
小Hi：一开始就直接求解多个方程不是太容易，我们从n=2开始递推：
已知：
x mod m[1] = r[1]
x mod m[2] = r[2]
根据这两个式子，我们存在两个整数k[1],k[2]：

x = m[1] * k[1] + r[1]
x = m[2] * k[2] + r[2]
由于两个值相等，因此我们有：

	m[1] * k[1] + r[1] = m[2] * k[2] + r[2]
=>	m[1] * k[1] - m[2] * k[2] = r[2] - r[1]
由于m[1],m[2],r[1],r[2]都是常数，若令A=m[1],B=m[2],C=r[2]-r[1],x=k[1],y=k[2]，
则上式变为：Ax + By = C。

是不是觉得特别眼熟。

小Ho：这不是扩展欧几里德么！

小Hi：没错，这就是我们之前讲过的扩展欧几里德。

我们可以先通过gcd(m[1], m[2])能否整除r[2]-r[1]来判定是否存在解。

假设存在解，则我们通过扩展欧几里德求解出k[1],k[2]。

再把k[1]代入x = m[1] * k[1] + r[1]，就可以求解出x。

同时我们将这个x作为特解，可以扩展出一个解系：

X = x + k*lcm(m[1], m[2]) k为整数
lcm(a,b)表示a和b的最小公倍数。其求解公式为lcm(a,b)=a*b/gcd(a,b)。

将其改变形式为：

X mod lcm(m[1], m[2]) = x。
令M = lcm(m[1], m[2]), R = x，则有新的模方程X mod M = R。

此时，可以发现我们将x mod m[1] = r[1]，x mod m[2] = r[2]合并为了一个式子
X mod lcm(m[1], m[2]) = x。满足后者的X一定满足前两个式子。

小Ho：每两个式子都可以通过该方法化简为一个式子。那么我们只要重复进行这个操作，
就可以将n个方程组化简为一个方程，并且求出一个最后的解了。

小Hi：没错，就是这样。将其写做伪代码为：

M = m[1], R = r[1]
For i = 2 .. N 
	d = gcd(M, m[i])
	c = r[i] - R
	If (c mod d) Then	// 无解的情况
		Return -1
	End If
	(k1, k2) = extend_gcd(M / d, m[i] / d)	// 扩展欧几里德计算k1,k2
	k1 = (c / d * k1) mod (m[i] / d)	// 扩展解系
	R = R + k1 * M		// 计算x = m[1] * k[1] + r[1]
	M = M / d * m[i] 	// 求解lcm(M, m[i])
	R %= M 			// 求解合并后的新R，同时让R最小
End For		
If (R < 0) Then 
	R = R + M
End If
Return R
---------------------------------------------------------


输入
第1行：1个正整数, N，2≤N≤1,000。

第2..N+1行：2个正整数, 第i+1行表示第i组m,r，2≤m≤20,000,000，0≤r<m。

计算过程中尽量使用64位整型。

输出
第1行：1个整数，表示满足要求的最小X，若无解输出-1。答案范围在64位整型内。

样例输入
3
3 2
5 3
7 2

样例输出
23

*/

#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e3+5;
typedef long long LL;

LL m[maxn], r[maxn];

LL gcd( LL a, LL b )
{
    while(a && b) a>b? a%=b : b%=a;
    return a+b;
}

LL ext_gcd(LL a, LL b, LL &x, LL &y)
{
    if(b == 0)
    {
        x = 1; y = 0;
        return a;
    }
    LL c = ext_gcd(b, a%b, x, y);
    LL x0 = x;
    x = y;
    y = x0 - a / b * y;
    return c;
}

LL chain_remain(int n)
{
    LL M = m[0], R=r[0], k1, k2, x;
    for(int i=1; i<n; ++i)
    {
        LL d = gcd(M, m[i]);
        LL c = r[i] - R;
        if(c % d) return -1; //无解
        ext_gcd(M/d, m[i]/d, k1, k2);
        k1 *= c/d; //的原方程的解
        LL T = m[i] / d;
        k1 = (k1 % T + T) % T;  //将k1化为最小正整数解
        x = M * k1 + R;  //x = m[1] * k1 + r[1]
        // printf("x=%d\n",x);
        R = x; 
        M = M / d * m[i]; // M = lcm(M, m[i]) = M * m[i] / gcd(M, m[i])
        R %= M;
    }

    if(x < 0) x += M; return x;
    // if(R < 0) R += M; return R; 
}

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif

    int N;
    scanf("%d", &N);
    for(int i=0; i<N; ++i) scanf("%lld%lld", &m[i], &r[i]);
    printf("%lld", chain_remain(N));

    return 0;
}