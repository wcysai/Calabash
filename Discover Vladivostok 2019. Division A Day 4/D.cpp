#include<bits/stdc++.h>
#define MAXN 200005
#define MAXLOGN 20
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
struct edge{ll to,cost;};
ll n,q;
vector<edge> G[MAXN];
ll st[MAXLOGN][MAXN],vs[MAXN*2-1],depth[MAXN*2-1],id[MAXN],fa[MAXN];
ll sz[MAXN],d[MAXN*2-1];
bool centroid[MAXN];
ll ans;
struct upd
{
    ll dist,tot,color;
};
vector<upd> sta[MAXN];
void dfs(ll v,ll p,ll dist,ll dep,ll &k)
{
    id[v]=k;
    vs[k]=v;
    depth[k]=dep;
    d[k++]=dist;
    for(ll i=0;i<(int)G[v].size();i++)
    {
        if(G[v][i].to!=p)
        {
            dfs(G[v][i].to,v,dist+G[v][i].cost,dep+1,k);
            vs[k]=v;
            depth[k]=dep;
            d[k++]=dist;
        }
    }
}
ll getMin(ll x,ll y)
{
    return depth[x]<depth[y]?x:y;
}
void rmq_init(ll n)
{
    for(ll i=1;i<=n;i++) st[0][i]=i;
    for(ll i=1;1<<i<=n;i++)
        for(ll j=1;j+(1<<i)-1<=n;j++)
            st[i][j]=getMin(st[i-1][j],st[i-1][j+(1<<(i-1))]);
}
void init(ll V)
{
    ll k=0;
    dfs(1,0,0,0,k);
    rmq_init(V*2-1);
}
ll query(ll l,ll r)
{
    ll k=31-__builtin_clz(r-l+1);
    return getMin(st[k][l],st[k][r-(1<<k)+1]);
}
ll lca(ll u,ll v)
{
    if(u==v) return u;
    return vs[query(min(id[u],id[v]),max(id[u],id[v]))];
}
ll dis(ll u,ll v)
{
    return d[id[u]]+d[id[v]]-2*d[id[lca(u,v)]];
}
void add_edge(ll u,ll v,ll cost)
{
    G[u].push_back((edge){v,cost});
    G[v].push_back((edge){u,cost});
}
P getroot(ll v,ll p,ll t)
{
    P res=P(INT_MAX,-1);
    ll m=0;
    sz[v]=1;
    for(ll i=0;i<(int)G[v].size();i++)
    {
        ll to=G[v][i].to,cost=G[v][i].cost;
        if(to==p||centroid[to]) continue;
        res=min(res,getroot(to,v,t));
        m=max(m,sz[to]);
        sz[v]+=sz[to];
    }
    m=max(m,t-sz[v]);
    res=min(res,P(m,v));
    return res;
}
void solve(ll v,ll p)
{
    fa[v]=p;
    centroid[v]=true;
    for(ll i=0;i<(int)G[v].size();i++)
    {
        ll to=G[v][i].to,cost=G[v][i].cost;
        if(centroid[to]) continue;
        ll rt=getroot(to,v,sz[to]).S;
        solve(rt,v);
    }
}
void build()
{
    memset(centroid,false,sizeof(centroid));
    ll rt=getroot(1,0,n).S;
    solve(rt,0);
}
void update(ll v,ll dist,ll tot,ll color)
{
    ll u=v;
    do
    {
        if(dist-dis(u,v)>=0)
        {
            while((int)sta[v].size()>0&&sta[v].back().dist<=dist-dis(u,v)) sta[v].pop_back();
            sta[v].push_back((upd){dist-dis(u,v),tot,color});
        }
        v=fa[v];
    }while(v);
}
ll query(ll v)
{
    ll cur=0,col=0,u=v;
    do
    {
        ll dist=dis(u,v);
        if(sta[v].size()&&sta[v][0].dist>=dist)
        {
            ll l=0,r=(int)sta[v].size();
            while(r-l>1)
            {
                ll mid=(l+r)/2;
                if(sta[v][mid].dist>=dist) l=mid; else r=mid;
            }
            if(sta[v][l].tot>cur)
            {
                cur=sta[v][l].tot;
                col=sta[v][l].color;
            }
        }
        v=fa[v];
    }while(v);
    return col;
}
int main()
{
    scanf("%lld",&n);
    for(int i=0;i<n-1;i++)
    {
        ll u,v,w;
        scanf("%lld%lld%lld",&u,&v,&w);
        add_edge(u,v,w);
    }
    init(n);
    build();
    scanf("%lld",&q);
    for(ll i=0;i<q;i++)
    {
        ll type,v,d,c;
        scanf("%lld",&type);
        if(type==1)
        {
            scanf("%lld%lld%lld",&v,&d,&c);
            update(v,d,i+1,c);
        }
        else
        {
            scanf("%lld",&v);
            printf("%lld\n",query(v));
        }
    }
    return 0;
}
