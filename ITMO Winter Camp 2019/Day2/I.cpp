#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
ll n,m,t[MAXN];
vector<ll> G[MAXN];
vector<P> v;
vector<ll> dis;
ll bit[MAXN+1];
ll sum(ll i)
{
    ll s=0;
    while(i)
    {
        s+=bit[i];
        i-=i&-i;
    }
    return s;
}
void add(ll i,ll x)
{
    while(i<=MAXN)
    {
        bit[i]+=x;
        i+=i&-i;
    }
}
int main()
{
    freopen("optimize.in","r",stdin);
    freopen("optimize.out","w",stdout);
    scanf("%lld%lld",&n,&m);
    for(ll i=1;i<=m;i++) scanf("%lld",&t[i]);
    for(ll i=1;i<=n;i++)
    {
        ll k;scanf("%lld",&k);
        for(ll j=0;j<k;j++)
        {
            ll x;scanf("%lld",&x);
            G[i].push_back(t[x]);
        }
    }
    for(ll i=1;i<=n;i++)
    {
        if(!G[i].size()) continue;
        ll sum=0;
        for(auto x:G[i]) sum+=x;
        for(auto x:G[i]) {v.push_back(P(x,sum-x)); dis.push_back(sum-x);}
    }
    sort(dis.begin(),dis.end());
    dis.erase(unique(dis.begin(),dis.end()),dis.end());
    ll ans=0;
    sort(v.begin(),v.end());
    ll sz=(int)v.size(),now=0;
    while(now<sz)
    {
        ll st=now;
        while(now<sz-1&&v[now].F==v[now+1].F) now++;
        for(ll i=st;i<=now;i++)
        {
            ll id=lower_bound(dis.begin(),dis.end(),v[i].S)-dis.begin()+1;
            ans+=sum(id-1);
        }
        for(ll i=st;i<=now;i++)
        {
            ll id=lower_bound(dis.begin(),dis.end(),v[i].S)-dis.begin()+1;
            add(id,1);
        }
        now++;
    }
    printf("%lld\n",ans);
    return 0;
}

