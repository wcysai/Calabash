/*************************************************************************
    > File Name: K.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-08-08 15:01:52
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100050
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll T,c,n,k;
ll prime[1200000];
bool is_prime[2000001];
ll inv[1200000];
ll sieve(ll n)
{
    ll p=0;
    for(ll i=0;i<=n;i++) is_prime[i]=true;
    is_prime[0]=is_prime[1]=false;
    for(ll i=2;i<=n;i++)
    {
        if(is_prime[i]) prime[p++]=i;
        for(ll j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            if(i%prime[j]==0) break;
        }
    }
    return p;
}
ll pow_mod(ll a,ll i)
{
    ll s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
int main()
{
    sieve(2000000);
    inv[1]=1;
    for(ll i=2;i<=100005;i++)
        inv[i]=1LL*(MOD-MOD/i)*inv[MOD%i]%MOD;
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld%lld%lld",&c,&n,&k);
        ll p=prime[c-1];
        //printf("%lld\n",p);
        ll cur=p,ans=0;
        for(ll i=1;i<=k;i++)
        {
            cur=1LL*cur*(p+i)%MOD;
            cur=1LL*cur*inv[i+1]%MOD;
            if(cur==1)
            {
                ans+=n;
                if(ans>=MOD) ans-=MOD;
            }
            else
            {
                ll res=pow_mod(cur,n+1)-cur;
                if(res<0) res+=MOD;
                res=1LL*res*pow_mod(cur-1,MOD-2)%MOD;
                ans+=res;
                if(ans>=MOD) ans-=MOD;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
