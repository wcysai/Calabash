/*************************************************************************
    > File Name: A.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-09-02 14:01:23
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
ll n,k,a[MAXN];
ll prime[MAXN];
bool is_prime[MAXN];
vector<P> v;
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
int main()
{
    ll p=sieve(100000);
    v.push_back(P(1,1));
    ll last=0;
    for(ll i=0;i<p;i++)
    {
        ll x=prime[i],sz=(int)v.size();
        ll cur=1;
        for(ll j=0;j<sz;j++)
        {
            P res=v[j];
            cur=2;
            for(ll now=x;res.F<=INF/now;now*=x)
            {
                v.push_back(P(res.F*now,res.S*cur));
                cur++;
            }
        }
        sort(v.begin(),v.end());
        ll mx=0,mx2=0;
        for(auto it=v.begin();it!=v.end();it++)
        {
            if(it->S>mx) {mx2=mx; mx=it->S; continue;}
            else if(it->S>mx2) {mx2=it->S; continue;}
            else if(it->S<mx2) {v.erase(it); it--;}
        }
        if((int)v.size()==last) break; else last=(int)v.size();
    }
    scanf("%lld",&n);
    if(n>(int)v.size()) puts("-1"); else printf("%lld\n",v[n-1].F);
    return 0;
}
