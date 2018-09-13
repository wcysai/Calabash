/*************************************************************************
    > File Name: D.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-09-11 10:56:03
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 600005
#define INF 1000000000
#define MOD 998244353
#define REV 499122177
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a,b,p;
int g[MAXN];
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
void pre()
{
    g[1]=1;
    for(int i=2;i<=n-1;i++)
        g[i]=(1LL*g[i-1]*g[i-1]+2)%MOD;
}
void prefact()
{
    fact[0]=invf[0]=1;
    for(int i=1;i<=n;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[n]=pow_mod(fact[n],MOD-2);
    for(int i=n-1;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
}
int comb(int n,int k)
{
    return 1LL*fact[n]*invf[k]%MOD*invf[n-k]%MOD;
}
int main()
{
    scanf("%d",&n);
    scanf("%d%d",&a,&b);
    pre();
    p=1LL*a*pow_mod(b,MOD-2)%MOD;
    int np=(1-p+MOD)%MOD;
    if(p==REV)
    {
        prefact();
        int ans=0;
        for(int k=1;k<=n-1;k++)
        {
            int f=1LL*comb(n,k);
            int e=1LL*k*(n-k)%(MOD-1);
            int res=pow_mod(pow_mod(2,e),MOD-2);
            f=1LL*f*res%MOD;
            ans=(ans+1LL*f*g[k])%MOD;
        }
        printf("%d\n",ans);
    }
    else
    {
        int f=1,ans=0;
        for(int k=1;k<=n-1;k++)
        {
            int pp=pow_mod(p,n-k+1)-pow_mod(np,n-k+1);
            if(pp<0) pp+=MOD;
            f=1LL*f*pp%MOD;
            pp=pow_mod(p,k)-pow_mod(np,k);
            if(pp<0) pp+=MOD;
            f=1LL*f*pow_mod(pp,MOD-2)%MOD;
            ans=(ans+1LL*f*g[k])%MOD;
        }
        printf("%d\n",ans);
    }
    return 0;
}
