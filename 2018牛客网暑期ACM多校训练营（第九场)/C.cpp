/*************************************************************************
    > File Name: CC.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-08-16 14:24:19
 ************************************************************************/
 
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define REV 500000004
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,a[MAXN],sum1[MAXN],sum2[MAXN],pow2[MAXN];
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
int fact[MAXN],invf[MAXN];
int comb(int n,int k)
{
    return 1LL*fact[n]*invf[k]%MOD*invf[n-k]%MOD;
}
int main()
{
    fact[0]=invf[0]=pow2[0]=1;
    for(int i=1;i<=200000;i++)
        fact[i]=1LL*fact[i-1]*i%MOD;
    invf[200000]=pow_mod(fact[200000],MOD-2);
    for(int i=199999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    for(int i=1;i<=200000;i++) pow2[i]=2LL*pow2[i-1]%MOD;
    scanf("%d",&n);
    int a=n,b=n;
    for(int i=1;i<=2*n-1;i++)
    {
        int x;
        int res=1LL*comb(a+b-2,a-1)*pow2[2*n-1-(a+b-2)]%MOD;
        printf("%d\n",res);
        scanf("%d",&x);
        if(x==0) a--; else b--;
        if(a==0||b==0) break;
    }
    return 0;
}
