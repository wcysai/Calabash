#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define MAXLOGN 18
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q,tot,st[2*MAXN],ed[2*MAXN],loc[2*MAXN];
struct edge{int to,cost;};
vector<edge> G[MAXN];
int spt[MAXLOGN+1][4*MAXN];
int vs[MAXN*2],depth[MAXN*2];
int id[MAXN],pos[MAXN],cnt[MAXN],val[MAXN],now;
bool vis[MAXN];
void add_edge(int u,int v,int w)
{
    G[u].push_back((edge){v,w});
    G[v].push_back((edge){u,w});
}
void dfs(int v,int p,int d,int &k)
{
    st[v]=++tot; loc[tot]=v;
    id[v]=k;
    vs[k]=v;
    depth[k++]=d;
    for(auto e:G[v])
    {
        int to=e.to,cost=e.cost;
        if(to==p) continue;
        dfs(to,v,d+1,k);
        val[to]=cost;
        vs[k]=v;
        depth[k++]=d;
    }
    ed[v]=++tot;
    loc[tot]=v;
}
int getMin(int x,int y)
{
    return depth[x]<depth[y]?x:y;
}
void rmq_init(int n)
{
    for(int i=1;i<=n;i++) spt[0][i]=i;
    for(int i=1;i<<i<n;i++)
        for(int j=1;j+(1<<i)-1<=n;j++)
            spt[i][j]=getMin(spt[i-1][j],spt[i-1][j+(1<<(i-1))]);
}
void init(int V)
{
    int k=0;
    dfs(1,0,0,k);
    rmq_init(V*2-1);
}
int query(int l,int r)
{
    int k=31-__builtin_clz(r-l+1);
    return getMin(spt[k][l],spt[k][r-(1<<k)+1]);
}
int lca(int u,int v)
{
    if(u==v) return u;
    return vs[query(min(id[u],id[v]),max(id[u],id[v]))];
}
struct qry
{
    int l,r,z,id;
}Q[MAXN];
bool cmp(qry a,qry b)
{
    return pos[a.l]==pos[b.l]?a.r<b.r:pos[a.l]<pos[b.l];
}
void deal(int x)
{
    if(val[x]>=100000) return;
    if(!vis[x])
    {
        cnt[val[x]]++;
        while(cnt[now]) now++;
    }
    else
    {
        cnt[val[x]]--;
        if(!cnt[val[x]]&&val[x]<now) now=val[x];
    }
    vis[x]^=1;
}
int ans[MAXN];
const int blocks=600;
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=0;i<n-1;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add_edge(u,v,w);
    }
    val[1]=INF;
    init(n);
    for(int i=1;i<=tot;i++) pos[i]=(i-1)/blocks+1;
    for(int i=1;i<=q;i++)
    {
        Q[i].id=i;
        int u,v;
        scanf("%d%d",&u,&v);
        if(st[u]>st[v]) swap(u,v);
        int z=lca(u,v);
        if(z==u) Q[i].l=st[u],Q[i].r=st[v];
        else Q[i].l=ed[u],Q[i].r=st[v],Q[i].z=z;
    }
    sort(Q+1,Q+q+1,cmp);
    int l=1,r=0;
    memset(vis,false,sizeof(vis));
    for(int i=1;i<=q;i++)
    {
        if(r<Q[i].r) {for(r++;r<=Q[i].r;r++) deal(loc[r]); r--;}
        if(r>Q[i].r) {for(;r>Q[i].r;r--) deal(loc[r]); }
        if(l<Q[i].l) {for(;l<Q[i].l;l++) deal(loc[l]); }
        if(l>Q[i].l) {for(l--;l>=Q[i].l;l--) deal(loc[l]); l++;}
        if(!Q[i].z) deal(loc[Q[i].l]);
        ans[Q[i].id]=now;
        if(!Q[i].z) deal(loc[Q[i].l]);
    }
    for(int i=1;i<=q;i++) printf("%d\n",ans[i]);          
    return 0;
}
