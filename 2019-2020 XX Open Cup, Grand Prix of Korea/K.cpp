#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 250005
#define MAXLOGN 19
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int N,tot;
ll mini;
struct edge{int to,cost;};
struct edge2{int to; ll cost;};
vector<edge> T1[MAXN],T2[MAXN];
vector<edge2> vt[MAXN];
int st[MAXLOGN][4*MAXN];
int dfn[MAXN],sta[MAXN];
ll dis[MAXN],ans[MAXN];
int vs[MAXN*2-1];
int depth[MAXN*2-1];
int id[MAXN];
bool realv[MAXN];
vector<int> auxi;

namespace IO {
    const int MX = 4e7; //1e7Õ¼ÓÃÄÚ´æ11000kb
    char buf[MX]; int c, sz;
    void begin() {
        c = 0;
        sz = fread(buf, 1, MX, stdin);
    }
    inline bool read(int &t) {
        while(c < sz && buf[c] != '-' && (buf[c] < '0' || buf[c] > '9')) c++;
        if(c >= sz) return false;
        bool flag = 0; if(buf[c] == '-') flag = 1, c++;
        for(t = 0; c < sz && '0' <= buf[c] && buf[c] <= '9'; c++) t = t * 10 + buf[c] - '0';
        if(flag) t = -t;
        return true;
    }
}

void add_edge_t1(int u,int v,int cost)
{
    T1[u].push_back((edge){v,cost});
    T1[v].push_back((edge){u,cost});
}
void add_edge_t2(int u,int v,int cost)
{
    T2[u].push_back((edge){v,cost});
    T2[v].push_back((edge){u,cost});
}
void add_edge_vt(int u,int v)
{
    ll cost=max(dis[u]-dis[v],dis[v]-dis[u]);
    vt[u].push_back((edge2){v,cost});
    vt[v].push_back((edge2){u,cost});
}
bool cmp(int x,int y)
{
    return dfn[x]<dfn[y];
}
void dfs(int v,int p,int d,ll sum,int &k)
{
    id[v]=k;
    vs[k]=v;
    dfn[v]=++tot;
    dis[v]=sum;
    depth[k++]=d;
    for(auto e:T2[v])
    {
        int to=e.to,cost=e.cost;
        if(to!=p)
        {
            dfs(to,v,d+1,cost+sum,k);
            vs[k]=v;
            depth[k++]=d;
        }
    }
}
int getMin(int x, int y)
{
    return depth[x]<depth[y]?x:y;
}

void rmq_init(int n)
{
    for(int i=1;i<=n;++i) st[0][i]=i;
    for(int i=1;1<<i<n;++i)
        for(int j=1;j+(1<<i)-1<=n;++j)
            st[i][j]=getMin(st[i-1][j],st[i-1][j+(1<<(i-1))]);
}
void init(int V)
{
    int k=0;
    dfs(1,0,0,0,k);
    rmq_init(V*2-1);
}
int query(int l, int r)
{
    int k=31-__builtin_clz(r-l+1);
    return getMin(st[k][l],st[k][r-(1<<k)+1]);
}
int lca(int u,int v)
{
    if(u==v) return u;
    return vs[query(min(id[u],id[v]),max(id[u],id[v]))];
}
ll get_dist(int u,int v)
{
    return dis[u]+dis[v]-2*dis[lca(u,v)];
}
int sz[MAXN];
ll dist[MAXN];
bool centroid[MAXN],centroid_vt[MAXN];
int sz_vt[MAXN];
ll dist_vt[MAXN];
int build_vt(vector<int> &a)
{
    sort(a.begin(),a.end(),cmp);
    a.erase(unique(a.begin(),a.end()),a.end());
    for(auto x:a) realv[x]=true;
    assert(a.size()>0);
    int t=0;
    sta[t++]=a[0];
    vector<int> newly; newly.clear();
    for(int i=1;i<(int)a.size();i++)
    {
        if(t==0) {sta[t++]=a[i]; continue;}
        int l=lca(a[i],sta[t-1]);
        while(t>1&&dfn[sta[t-2]]>=dfn[l]) add_edge_vt(sta[t-2],sta[t-1]),t--;
        if(l!=sta[t-1]) {add_edge_vt(l,sta[t-1]),sta[t-1]=l; newly.push_back(l);}
        sta[t++]=a[i];
    }
    while(t>1) add_edge_vt(sta[t-2],sta[t-1]),t--;
    for(auto it:newly) a.push_back(it);
    return sta[0];
}
void destruct_vt(vector<int> &a)
{
    for(auto x:a)
    {
        centroid_vt[x]=false;
        vt[x].clear(); realv[x]=false;
    }
}

P getroot_vt(int v,int p,int t)
{
    P res=P(INT_MAX,-1);
    int m=0;
    sz_vt[v]=1;
    for(int i=0;i<(int)vt[v].size();i++)
    {
        int to=vt[v][i].to;
        if(to==p||centroid_vt[to]) continue;
        res=min(res,getroot_vt(to,v,t));
        m=max(m,sz_vt[to]);
        sz_vt[v]+=sz_vt[to];
    }
    m=max(m,t-sz_vt[v]);
    res=min(res,P(m,v));
    return res;
}

void getdeep_vt(int v,int p,ll d)
{
    dist_vt[v]=d+dist[v];
    for(auto e:vt[v])
    {
        int to=e.to;
        ll cost=e.cost;
        if(to==p||centroid_vt[to]) continue;
        getdeep_vt(to,v,d+cost);
    }
}

void apply_min(int v,int p)
{
    if(realv[v]) ans[v]=min(ans[v],mini+dist_vt[v]);
    for(auto e:vt[v])
    {
        int to=e.to;
        if(to==p||centroid_vt[to]) continue;
        apply_min(to,v);
    }
}

void update_min(int v,int p)
{
    if(realv[v]) mini=min(mini,dist_vt[v]);
    for(auto e:vt[v])
    {
        int to=e.to;
        if(to==p||centroid_vt[to]) continue;
        update_min(to,v);
    }
}

void solve_vt(int v)
{
    //printf("solving rt %d\n",v);
    centroid_vt[v]=true;
    getdeep_vt(v,v,0);
    //printf("getting depth_vt\n");
    //for(int i=1;i<=N;i++) printf("%d %lld\n",i,dist_vt[i]);
    mini=INF;
    for(auto e:vt[v])
    {
        int to=e.to;
        if(centroid_vt[to]) continue;
        apply_min(to,v); update_min(to,v);
    }
    if(realv[v]) ans[v]=min(ans[v],mini+dist_vt[v]);
    if(realv[v]) mini=dist_vt[v]; else mini=INF;
    for(int j=(int)vt[v].size()-1;j>=0;j--)
    {
        int to=vt[v][j].to;
        if(centroid_vt[to]) continue;
        apply_min(to,v); update_min(to,v);
    }
    for(auto e:vt[v])
    {
        int to=e.to;
        if(centroid_vt[to]) continue;
        int rt=getroot_vt(to,v,sz_vt[to]).S;
        solve_vt(rt);
    }
}


P getroot(int v,int p,int t)
{
    P res=P(INT_MAX,-1);
    int m=0;
    sz[v]=1;
    for(int i=0;i<(int)T1[v].size();i++)
    {
        int to=T1[v][i].to;
        if(to==p||centroid[to]) continue;
        res=min(res,getroot(to,v,t));
        m=max(m,sz[to]);
        sz[v]+=sz[to];
    }
    m=max(m,t-sz[v]);
    res=min(res,P(m,v));
    return res;
}
void getdeep(int v,int p,ll d)
{
    dist[v]=d;
    auxi.push_back(v);
    for(auto e:T1[v])
    {
        int to=e.to,cost=e.cost;
        if(to==p||centroid[to]) continue;
        getdeep(to,v,d+cost);
    }
}
void solve(int v)
{
    auxi.clear();
    centroid[v]=true;
    getdeep(v,v,0);
    int root=build_vt(auxi);
    int rt=getroot_vt(root,0,(int)auxi.size()).S;
    /*printf("solving %d\n",v);
    printf("getting depth\n");
    for(int i=1;i<=N;i++) printf("%d %lld\n",i,dist[i]);
    printf("auxiliary verices: ");
    for(auto x:auxi) printf("%d ",x);
    puts("");*/
    solve_vt(rt);
    destruct_vt(auxi);
    //for(int i=1;i<=N;i++) printf("%d %lld\n",i,ans[i]);
    for(auto e:T1[v])
    {
        int to=e.to;
        if(centroid[to]) continue;
        rt=getroot(to,v,sz[to]).S;
        solve(rt);
    }
}
int main()
{
    //freopen("1.in","r",stdin);
    IO::begin();
    IO::read(N);
    for(int i=0;i<N-1;i++)
    {
        int u,v,cost;
        IO::read(u); IO::read(v); IO::read(cost);
        add_edge_t1(u,v,cost);
    }
    for(int i=0;i<N-1;i++)
    {
        int u,v,cost;
        IO::read(u); IO::read(v); IO::read(cost);
        add_edge_t2(u,v,cost);
    }
    init(N);
    for(int i=1;i<=N;i++) ans[i]=INF;
    int rt=getroot(1,0,N).S;
    solve(rt);
    for(int i=1;i<=N;i++) printf("%lld\n",ans[i]);
    return 0;
}
