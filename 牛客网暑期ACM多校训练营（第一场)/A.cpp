/*************************************************************************
    > File Name: A.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-07-19 12:06:15
 ************************************************************************/
 
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 3005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
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
int fact[MAXN],invf[MAXN],inv[MAXN],pow2[MAXN];
int n,m;
int comb(int n,int k)
{
    return 1LL*fact[n]*invf[k]%MOD*invf[n-k]%MOD;
}
int main()
{
    fact[0]=invf[0]=inv[1]=1;
    for(int i=1;i<=3000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[3000]=pow_mod(fact[3000],MOD-2);
    for(int i=2999;i>=1;i--)
    {
        invf[i]=1LL*invf[i+1]*(i+1)%MOD;
        inv[i+1]=1LL*invf[i+1]*fact[i]%MOD;
    }
    while(scanf("%d%d",&n,&m)==2)
    {
        int ans=1LL*comb(n+m+1,m)*comb(n+m,m)%MOD;
        ans=1LL*ans*inv[m+1]%MOD;
        printf("%d\n",ans);
    }
    return 0;
}
