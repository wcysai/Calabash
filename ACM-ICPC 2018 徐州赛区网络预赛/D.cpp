/*************************************************************************
    > File Name: D.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-09-09 12:32:29
 ************************************************************************/
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 20000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
bool is_prime[MAXN];
ll cnt;
int miu[MAXN],prime[MAXN];
ll n,m;
ll p;
int f[MAXN];
map<ll,int> mp;
ll genmiu(ll n)
{
    ll p=0;
    memset(miu,0,sizeof(miu));
    miu[1]=1;
     for(ll i=0;i<=n;i++) is_prime[i]=true;
    is_prime[0]=is_prime[1]=false;
    for(ll i=2;i<=n;i++)
    {
        if(is_prime[i]) {prime[p++]=i; miu[i]=-1;}
        for(ll j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            miu[i*prime[j]]=i%prime[j]?-miu[i]:0;
            if(i%prime[j]==0) break;
        }
    }
    for(ll i=1;i<=n;i++) f[i]=(f[i-1]+miu[i]);
    return p;
}
ll calc(ll x)
{
	if(x<=20000000) return f[x];
	if(mp.find(x)!=mp.end()) return mp[x];
	ll ans=1;
	for(ll i=2,r;i<=x;i=r+1)
	{
		r=x/(x/i);
		ans-=1LL*calc(x/i)*(r-i+1);
	}
	return mp[x]=ans;
}
ll tot=0;
map<P,int> save;
vector<ll> fact;
ll find_ans(ll n,ll m)
{
    if(save.find(P(n,m))!=save.end()) return save[P(n,m)];
    if(n==1) return calc(m);
    if(m==0) return 0;
    ll sz=(int)fact.size();
    vector<ll> v;v.clear();
    for(ll i=0;i<sz;i++)
        if(n%fact[i]==0) v.push_back(fact[i]);
    sz=(int)v.size();
    ll res=(sz&1)?1:-1,ans=0;
    for(ll i=0;i<(1<<sz);i++)
    {
        ll cnt=0;ll s=1;
        for(ll j=0;j<sz;j++) 
            if((i>>j)&1) cnt++,s=s*v[j];
        ans+=res*((cnt&1)?1:-1)*find_ans(s,m/s);
    }
    return ans;
}
int main()
{
	p=genmiu(20000000);
    scanf("%lld%lld",&m,&n);
    fact.clear();
    ll t=n;
    for(ll i=0;i<p&&prime[i]*prime[i]<=t;i++)
    {
        ll cnt=0;
        if(t==1) break;
        if(t<=20000000&&is_prime[t]) {fact.push_back(t); t=1; break;}
        while(t%prime[i]==0)
        {
            t=t/prime[i];
            cnt++;
        }
        if(cnt>0) fact.push_back(prime[i]);
        if(cnt>1) {puts("0"); return 0;} 
    }
    if(t!=1) fact.push_back((ll)t);
	printf("%lld\n",find_ans(n,m));
}
