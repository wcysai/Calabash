/*************************************************************************
    > File Name: B.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-08-01 12:54:04
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
const ll block=300;
ll T,n,m;
ll fact[MAXN],invf[MAXN];
vector<ll> db[400];
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
ll comb(ll n,ll k)
{
    if(n<k) return 0;
    return 1LL*fact[n]*invf[k]%MOD*invf[n-k]%MOD;
}
int main()
{
    fact[0]=invf[0]=1;
    for(ll i=1;i<=100005;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[100005]=pow_mod(fact[100005],MOD-2);
    for(ll i=100004;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    for(ll i=0;block*i<=100000;i++)
    {
        ll id=i*300;
        ll now=1;db[i].clear();
        for(ll j=id;j<=100000;j++)
        {
            db[i].push_back(now);
            now=(2LL*now+comb(j,j-id+1))%MOD;
        }
    }
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld%lld",&n,&m);
        ll tn=n,tm=m;
        while((tn-tm)%block!=0) tn--;
        ll now=db[(tn-tm)/block][tm];
        //printf("%lld %lld %lld\n",tn,tm,now);
        while(tn<n)
        {
            now=(2LL*now-comb(tn,tm)+MOD)%MOD;
            tn++;
        }
        printf("%lld\n",now);
    }
    return 0;
}
