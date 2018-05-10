#include<iostream>
using namespace std;
typedef long long LL;


// sp(n) = sp(k-1) * sp(n-k). k=1...n;
// sp(1) = sp(0) = 1;
LL sp(LL n)
{
    static LL f[20]={0};
    if(f[n]) return f[n];
    LL ans = 0;
    if(n <= 1) return 1;
    for(int k=1; k<=n; ++k)
    {
        ans += sp(k-1) * sp(n-k);
    }
    return f[n] = ans;
}

// n个等着进栈，栈中有k个
//f(n,k) = f(n,k-1) + f(n-1, k+1); 一个元素出栈或者一个元素进栈
//f(0,k) = 1; 栈中有k个, 外面没有等着的.
//f(n,0) = f(n-1,1) //全部都在外面等着, 因此只能放一个进栈
LL f2(int n, int k)
{
    static LL f[20][20]={0};
    if(f[n][k]) return f[n][k];
    if(n == 0) return 1;
    if(k == 0) return f[n][k] = f2(n-1,1);
    return f[n][k] = f2(n, k-1) + f2(n-1, k+1);
}

int main()
{
    for(LL i=0; i<=10; ++i)
    {
        printf("%lld : %lld %lld\n", i, sp(i), f2(i,0));
    }
    /*
    0 : 1 1
    1 : 1 1
    2 : 2 2
    3 : 5 5
    4 : 14 14
    5 : 42 42
    6 : 132 132
    7 : 429 429
    8 : 1430 1430
    9 : 4862 4862
    */

    return 0;
}