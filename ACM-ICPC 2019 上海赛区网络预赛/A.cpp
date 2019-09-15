#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
struct edge{ll to,cost;};
int n,q,w;
vector<edge> G[MAXN];
bool centroid[MAXN];
unordered_map<ll,ll> st[MAXN],ed[MAXN],whichson[MAXN];
ll rk[MAXN],cursz,curv;
ll sz[MAXN],deep[MAXN],d[MAXN],fa[MAXN];
ll root,ans,tot;
struct edge2
{
    ll u,v,cost;
}edges[MAXN];
void add_edge(ll u,ll v,ll cost)
{
    G[u].push_back((edge){v,cost});
    G[v].push_back((edge){u,cost});
}
P getroot(ll v,ll p,ll t)//search_centroid
{
    P res=P(INT_MAX,-1);
	ll m=0;
    sz[v]=1;
    for(ll i=0;i<(int)G[v].size();i++)
    {
        ll to=G[v][i].to;
        if(to==p||centroid[to]) continue;
        res=min(res,getroot(to,v,t));
        m=max(m,sz[to]);
        sz[v]+=sz[to];
    }
    m=max(m,t-sz[v]);
    res=min(res,P(m,v));
    return res;
}
struct segtree
{
    vector<ll> maxi,lazy;
    multiset<ll> ms;
    void resize(ll sz)
    {
        maxi.clear(); lazy.clear();
        maxi.resize(4*sz+1); lazy.resize(4*sz+1);
    }
    void pushup(ll k)
    {
        maxi[k]=max(maxi[k*2],maxi[k*2+1]);
    }
    void pushdown(ll k)
    {
        if(!lazy[k]) return;
        for(ll i=k*2;i<=k*2+1;i++)
        {
            maxi[i]+=lazy[k];
            lazy[i]+=lazy[k];
        }
        lazy[k]=0;
    }
    void update(ll k,ll l,ll r,ll x,ll y,ll v)
    {
        if(l>y||x>r) return;
        if(l>=x&&r<=y)
        {
            lazy[k]+=v;
            maxi[k]+=v;
            return;
        }
        pushdown(k);
        ll mid=(l+r)/2;
        update(k*2,l,mid,x,y,v); update(k*2+1,mid+1,r,x,y,v);
        pushup(k);
    }
    ll query(ll k,ll l,ll r,ll x,ll y)
    {
        if(l>y||x>r) return -INF;
        if(l>=x&&r<=y) return maxi[k];
        pushdown(k);
        ll mid=(l+r)/2;
        return max(query(k*2,l,mid,x,y),query(k*2+1,mid+1,r,x,y));
    }
    ll get_ans()
    {
        if(ms.size()==0) return 0;
        else if(ms.size()==1) return max(0LL,*(--ms.end()));
        else
        {
            auto it=ms.end();
            ll ret=0;
            it--; if(*it>0) ret+=*it;
            it--; if(*it>0) ret+=*it;
            return ret;
        }
    }
}seg[MAXN];
void getsz(ll v,ll p)
{
    sz[v]=1;
    for(ll i=0;i<(int)G[v].size();i++)
    {
        ll to=G[v][i].to;
        if(to==p||centroid[to]) continue;
        getsz(to,v);
        sz[v]+=sz[to];
    }
}
void dfs(ll v,ll p,ll c,ll son)
{
    whichson[curv][v]=son;
    st[curv][v]=++tot;
    for(ll i=0;i<(int)G[v].size();i++)
    {
        ll to=G[v][i].to,cost=G[v][i].cost;
        if(to==p||centroid[to]) continue;
        dfs(to,v,cost,son);
    }
    ed[curv][v]=tot;
    seg[curv].update(1,1,cursz,st[curv][v],ed[curv][v],c);
}
void build_segtree(ll v)
{
    seg[v].resize(sz[v]);
    tot=1;
    st[v][v]=1; ed[v][v]=sz[v];
    curv=v;
    cursz=sz[v];
    for(ll i=0;i<(int)G[v].size();i++)
    {
        ll to=G[v][i].to,cost=G[v][i].cost;
        if(centroid[to]) continue;
        dfs(to,v,cost,to);
    }
    for(ll i=0;i<(int)G[v].size();i++)
    {
        ll to=G[v][i].to;
        if(centroid[to]) continue;
        ll val=seg[v].query(1,1,cursz,st[curv][to],ed[curv][to]);
        seg[v].ms.insert(val);
    }
}
void solve(ll v,ll p,ll tot)
{
    rk[v]=tot;
    fa[v]=p;
    centroid[v]=true;
    getsz(v,0);
    build_segtree(v);
    for(ll i=0;i<(int)G[v].size();i++)
    {
        ll to=G[v][i].to,cost=G[v][i].cost;
        if(centroid[to]) continue;
        root=getroot(to,v,sz[to]).S;
        solve(root,v,tot+1);
    }
    root=v;
}
void centroid_decomposition()
{
    memset(centroid,false,sizeof(centroid));
    root=getroot(1,0,n).S;
    solve(root,0,0);
}
void update_edge(ll id,ll cost)
{
    ll u=edges[id].u,v=edges[id].v;
    if(rk[v]<rk[u]) swap(u,v);
    ll tmp=u,d=cost-edges[id].cost;
    while(tmp)
    {
        ll vert=(st[tmp][v]<=st[tmp][u]?u:v);
        ll affected=whichson[tmp][vert];
        ll val=seg[tmp].query(1,1,sz[tmp],st[tmp][affected],ed[tmp][affected]);
        seg[tmp].ms.erase(seg[tmp].ms.find(val));
        seg[tmp].update(1,1,sz[tmp],st[tmp][vert],ed[tmp][vert],d);
        val=seg[tmp].query(1,1,sz[tmp],st[tmp][affected],ed[tmp][affected]);
        seg[tmp].ms.insert(val);
        tmp=fa[tmp];
    }
    edges[id].cost=cost;
}
ll get_ans(ll u)
{
    ll ans=(seg[u].ms.size()==0?0:*(--seg[u].ms.end()));
    ll tmp=fa[u];
    while(tmp)
    {
        ll banned=whichson[tmp][u];
        ll val=seg[tmp].query(1,1,sz[tmp],st[tmp][banned],ed[tmp][banned]);
        ll d=seg[tmp].query(1,1,sz[tmp],st[tmp][u],st[tmp][u]);
        ll dist;
        if(seg[tmp].ms.size()==1) ans=max(ans,d);
        else
        {
            auto it=(--seg[tmp].ms.end());;
            if(*it==val) it--;
            ans=max(ans,d+*it);
        }
        tmp=fa[tmp];
    };
    return ans;
}
char ch[5];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;i++)
    {
        int u,v,cost;
        scanf("%d%d%d",&u,&v,&cost);
        edges[i].u=u; edges[i].v=v; edges[i].cost=cost;
        add_edge(u,v,cost);
    }
    centroid_decomposition();
    scanf("%d",&q);
    for(ll i=0;i<q;i++)
    {
        int x,y;
        scanf("%s",ch);
        if(ch[0]=='Q')
        {
            scanf("%d",&x);
            printf("%lld\n",get_ans(x));
        }
        else
        {
            scanf("%d%d",&x,&y);
            update_edge(x,y);
        }
    }
    return 0;
}


