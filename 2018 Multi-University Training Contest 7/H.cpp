/*************************************************************************
    > File Name: H.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-08-13 15:21:28
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define MAXLOGN 16
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define MAXV 200030
#define MAXQ 200030
#define MAXLOGV 20
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
struct edge{ll id,to,cost;};
ll n,q,s,U,V,T;
ll a[MAXV],b[MAXV],w[MAXV];
ll type[MAXQ];
ll x[MAXQ],t[MAXQ];
ll st[MAXLOGV][MAXV*2];
ll pre[MAXV*2];
vector<edge> G[MAXV];
ll root;
ll vs[MAXV*2-1];
ll depth[MAXV*2-1];
ll id[MAXV];
ll es[MAXV*2];
ll bit[MAXV*2];
ll color[MAXV];
ll sum(ll i)
{
    ll s=0;
    while(i>0)
    {
        s+=bit[i];
        i-=i&-i;
    }
    return s;
}
void add(ll i,ll x)
{
    while(i<=(n-1)*2)
    {
        bit[i]+=x;
        i+=i&-i;
    }
}
void dfs(ll v,ll p,ll d,ll &k)
{
    id[v]=k;
    vs[k]=v;
    depth[k++]=d;
    for(ll i=0;i<(int)G[v].size();i++)
    {
        edge &e=G[v][i];
        if((e.to==U&&v==V)||(e.to==V&&v==U)) continue;
        if(e.to!=p)
        {
            add(k,e.cost);
            es[e.id*2]=k;
            dfs(e.to,v,d+1,k);
            vs[k]=v;
            depth[k++]=d;
            add(k,-e.cost);
            es[e.id*2+1]=k;
        }
    }
}
ll getMin(ll x, ll y)
{
    return depth[x] < depth[y] ? x : y;
}

void rmq_init(ll n)
{
    for(ll i=1;i<=n;++i) st[0][i]=i;
    for(ll i=1;1<<i<=n;++i)
        for(ll j=1;j+(1<<i)-1<=n;++j)
            st[i][j]=getMin(st[i-1][j],st[i-1][j+(1<<i)-1]);
}
void init(ll V)
{
    memset(bit,0,sizeof(bit));
    ll k=0;
    dfs(root,0,0,k);
    rmq_init(V*2-1);
}
ll query(ll l, ll r)
{
    ll k=31-__builtin_clz(r-l+1);
    return getMin(st[k][l],st[k][r-(1<<k)+1]);
}
ll lca(ll u,ll v)
{
    if(u==v) return u;
    return vs[query(min(id[u],id[v]),max(id[u],id[v]))];
}
bool flag;
void dfs2(ll v,ll p)
{
    if(flag) return;
    color[v]=1;
    for(ll i=0;i<(int)G[v].size();i++)
    {
        ll to=G[v][i].to;
        if(to==p) continue;
        if(color[to]==1) {U=v; V=to; flag=true; return;}
        dfs2(to,v);
    }
    color[v]=2;
}
ll dis(ll u,ll v)
{
    ll p=lca(u,v);
    return sum(id[v])+sum(id[u])-sum(id[p])*2;
}
void solve()
{
    root=1;
    for(ll i=1;i<=n;i++) G[i].clear();
    memset(color,0,sizeof(color));
    for(ll i=1;i<=n;i++)
    {
        G[a[i]].push_back((edge){i,b[i],w[i]});
        G[b[i]].push_back((edge){i,a[i],w[i]});
    }
    flag=false;
    dfs2(root,0);
    //printf("U=%lld V=%lld\n",U,V);
    ll save=0,dd=-1;
    for(ll i=1;i<=n;i++)
    {
        if((a[i]==U&&b[i]==V)||(a[i]==V&&b[i]==U))
        {
            dd=i;
            save=w[i];
            break;
        }
    }
    //printf("%lld %lld\n",dd,save);
    init(n);
    for(ll i=0;i<q;i++)
    {
        if(type[i]==1)
        {
            ll u=x[i],v=t[i];
            ll ans=dis(u,v); 
            //printf("%lld %lld %lld\n",u,v,ans);
            ans=min(ans,dis(u,U)+dis(v,V)+save);
            ans=min(ans,dis(u,V)+dis(v,U)+save);
            printf("%lld\n",ans);
        }
        else
        {
            if(x[i]==dd)
            {
                save=t[i];
                continue;
            }
            ll k=x[i];
            add(es[k*2],t[i]-w[k]);
            add(es[k*2+1],w[k]-t[i]);
            w[k]=t[i];
        }
    }
}
int main()
{
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld%lld",&n,&q);
        for(ll i=1;i<=n;i++)
        {
            scanf("%lld%lld%lld",&a[i],&b[i],&w[i]);
        }
        for(ll i=0;i<q;i++)
        {
            scanf("%lld%lld%lld",&type[i],&x[i],&t[i]);
        }
        solve();
    }
    return 0;
}
