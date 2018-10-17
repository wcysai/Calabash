/*************************************************************************
    > File Name: L.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-10-17 22:47:30
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define REV  250000002
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll n,cur=0;
vector<ll> save;
map<ll,ll> vis;
ll pow_mod(ll a,ll i,ll m)
{
    ll s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%m;
        a=1LL*a*a%m;
        i>>=1;
    }
    return s;
}
int main()
{
    scanf("%lld",&n);
    save.push_back(1);
    vis[1]=cur++;
    ll t=n-1;
    ll now=1,ans=1;
    bool f=false;
    while(t--)
    {
        now=(now-1LL*now*now%MOD*REV%MOD+MOD)%MOD;
        ans=now;
        if(!f)
        {
            if(vis.find(now)!=vis.end())
            {
                ll cyc=cur-vis[now];
                t%=cyc;
                f=true;
            }
            else
            {
                save.push_back(ans);
                vis[ans]=cur++;
            }
        }
    }
    ll e=pow_mod(2,n-1,MOD-1);
    e=(e-1+MOD)%MOD;
    ll Q=pow_mod(4,e,MOD);
    printf("%lld %lld\n",1LL*ans*Q%MOD,Q);
    return 0;
}

