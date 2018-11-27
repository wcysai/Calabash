/*************************************************************************
    > File Name: I.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-11-28 01:14:25
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll n,q,tot,t,now,mx=0;
P st[MAXN];
vector<int> G[MAXN];
ll sum[MAXN],k[MAXN];
ll get(P u,P v) {return (v.S-u.S)/(u.F-v.F);}
void dfs(ll v,ll p,ll d)
{
    sum[d]++;mx=max(mx,d);
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs(to,v,d+1);
    }
}
void add(ll u,ll v)
{
    P p=P(u,v);
    while(t-now>1&&get(st[t-1],p)<=get(st[t-1],st[t-2])) t--;
    st[t++]=p;
}
bool cmp(P x,P y)
{
    if(x.S!=y.S) return x.S<y.S;
    return x.F<y.F;
}
ll query(ll x)
{
    ll l=-1,r=t-1;
    while(r-l>1)
    {
        ll mid=(l+r)/2;
        if(st[mid].F*x+st[mid].S<=st[mid+1].F*x+st[mid+1].S) l=mid;
        else r=mid;
    }
    return st[r].F*x+st[r].S;
}
int main()
{
    scanf("%lld%lld",&n,&q);
    for(ll i=1;i<=q;i++) scanf("%lld",&k[i]);
    for(ll i=2;i<=n;i++) 
    {
        ll x;scanf("%lld",&x);
        G[x].push_back(i);G[i].push_back(x);
    }
    dfs(1,0,1);
    for(ll i=mx-1;i>=0;i--) sum[i]+=sum[i+1];
    for(ll i=0;i<=mx;i++) add(i,sum[i+1]);
    for(ll i=1;i<=q;i++)
    {
        ll ans=(query(k[i])-1+k[i])/k[i];
        printf("%lld%c",ans,i==q?'\n':' ');
    }
    return 0;
}

