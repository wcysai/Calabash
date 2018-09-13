/*************************************************************************
    > File Name: C.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-08-20 13:31:09
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 300005
#define INF 1000000000
#define MOD 998244353
#define REV 499122177
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll prime[MAXN];
bool is_prime[MAXN];
ll cnt[50];
ll phi[MAXN];
ll genphi(ll n)
{
    ll p=0;
    memset(phi,0,sizeof(phi));
    memset(is_prime,true,sizeof(is_prime));
    phi[1]=1;
    for(ll i=2;i<=n;i++)
    {
        if(is_prime[i]) {prime[p++]=i; phi[i]=i-1;}
        for(ll j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            phi[i*prime[j]]=phi[i]*(i%prime[j]?prime[j]-1:prime[j]);
            if(i%prime[j]==0) break;
        }
    }
    return p;
}

ll t,n,f[MAXN],g[MAXN]; //f[i]:pi(n/i),g[i]:pi(i)
ll _mod(ll x)
{
    if(x<0) return x+MOD;
    if(x>=MOD) return x-MOD;
    return x;
}
ll sum(ll x)
{
    if(x>=MOD) x=x%MOD;
    return (1LL*x*(x+1)/2)%MOD;
}
void PrimeCount(ll n)
{
    ll i,j,m=0;
    for(m=1;m*m<=n;m++) f[m]=_mod(sum(n/m)-1);
    for(i=2;i<=m;i++) g[i]=_mod(i+g[i-1]);
    for(i=2;i<=m;i++)
    {
        if(g[i]==g[i-1]) continue;
        for(j=1;j<=min(m-1,n/i/i);++j)
        {
            if(i*j<m) f[j]=_mod((f[j]-1LL*i*(f[i*j]-g[i-1]))%MOD);
            else f[j]=_mod((f[j]-1LL*i*(g[n/i/j]-g[i-1]))%MOD);
        }
        for(j=m+1;j>=i*i;j--) g[j]=_mod((g[j]-i*(g[j/i]-g[i-1]))%MOD);
    }
}
int main()
{
    ll p=genphi(200500);
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld",&n);PrimeCount(n);
        //printf("%lld\n",f[1]);
        ll ans=0;
        ll sq;
        for(sq=0;(sq+1)*(sq+1)<=n;sq++);
       // printf("sq=%lld\n",sq);
        for(ll i=0;n/prime[i]>=sq;i++)
        {
            //printf("%lld\n",prime[i]);
            ll pp=prime[i],tot=0;
            memset(cnt,0,sizeof(cnt));
            cnt[0]=n;
            for(ll s=pp;s<=n;s*=pp)
            {
                tot++;
                cnt[tot]=n/s;
            }
            for(ll j=0;j<tot;j++) cnt[j]-=cnt[j+1];
            for(ll j=2;j<=tot;j++) cnt[j&1]+=cnt[j];
            //printf("%lld %lld %lld\n",pp,cnt[0],cnt[1]);
            ans=(ans+(cnt[0]%MOD)*(cnt[1]%MOD)%MOD*pp)%MOD;
        }
        //printf("%lld\n",ans);
        //assert(0);
        for(ll k=1;(k+1)*(k+1)<=n;k++)
        {
            ans=_mod((ans+k*(n-k)%MOD*(f[k]-f[k+1]))%MOD);
        }
        for(ll k=2;k*k<=n;k++)
            ans=_mod(ans+1LL*phi[k]*(n/(k*k))%MOD);
        printf("%lld\n",ans);
    }
}
