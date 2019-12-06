#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define MAXLOGN 20
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define log adskoada
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
vector<int> G[MAXN];
bool centroid[MAXN];
int n,q,all,tot,root;
string str;
int sz[MAXN],deep[MAXN],d[MAXN],fa[MAXN];
set<P> ms[MAXN];
int st[MAXLOGN+1][2*MAXN];
int vs[MAXN*2-1];
int depth[MAXN*2-1];
int id[MAXN],cntall[MAXN];
unordered_map<int,int> cnt[MAXN],whichson[MAXN],resp_centroid[MAXN];
unordered_map<int,ll> sum[MAXN];
ll sumall[MAXN];
void dfs(int v,int p,int d,int &k)
{
    id[v]=k;
    vs[k]=v;
    depth[k++]=d;
    for(int i=0;i<(int)G[v].size();i++)
    {
        if(G[v][i]!=p)
        {
            dfs(G[v][i],v,d+1,k);
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
    dfs(1,0,0,k);
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
int dis(int u,int v)
{
    return depth[id[u]]+depth[id[v]]-2*depth[id[lca(u,v)]];
}
P getroot(int v,int p,int t)
{
    P res=P(INT_MAX,-1);
	int m=0;
    sz[v]=1;
    for(auto to:G[v])
    {
        if(to==p||centroid[to]) continue;
        res=min(res,getroot(to,v,t));
        m=max(m,sz[to]);
        sz[v]+=sz[to];
    }
    m=max(m,t-sz[v]);
    res=min(res,P(m,v));
    return res;
}
void dfs2(int v,int p,int son,int rt)
{
    whichson[rt][v]=son;
    for(auto to:G[v])
    {
        if(to==p||centroid[to]) continue;
        dfs2(to,v,son,rt);
    }
}
void solve(int v,int p)
{
    centroid[v]=true; fa[v]=p; 
    for(auto to:G[v])
    {
        if(centroid[to]) continue;
        ms[v].insert(P(0,to));
        cnt[v][to]=sum[v][to]=0;
        dfs2(to,v,to,v);
        int rt=getroot(to,v,sz[to]).S;
        resp_centroid[v][to]=rt;
        solve(rt,v);
    }
}
void update(int v,int delta)
{
    all+=delta;
    int u=v;
    cntall[v]+=delta;
    while(fa[v])
    {
        v=fa[v];
        int son=whichson[v][u];
        ms[v].erase(P(cnt[v][son],son));
        cnt[v][son]+=delta; cntall[v]+=delta;
        ms[v].insert(P(cnt[v][son],son));
        sum[v][son]+=delta*dis(v,u); sumall[v]+=delta*dis(v,u);
    }
}
vector<P> fat;

int descend(int v)
{
    if(!ms[v].size()) return v;
    auto p=*(--ms[v].end());
    for(auto pp:fat)
    {
        if(whichson[v][pp.F])
        {
            int son=whichson[v][pp.F];
            cnt[v][son]+=pp.S;
            if(cnt[v][son]>p.F) p=P(cnt[v][son],son);
        }
    }
    for(auto pp:fat) 
    {
        if(whichson[v][pp.F])
        {
            int son=whichson[v][pp.F];
            cnt[v][son]-=pp.S;
        }
    }
    if(2*p.F<all) return v;
    int val=all-p.F;
    int rt=resp_centroid[v][p.S];
    if(p.S!=rt) fat.push_back(P(p.S,val));
    return descend(rt);
}
ll get_ans(int v)
{
    ll ans=sumall[v];
    int u=v;
    while(fa[v])
    {
        v=fa[v];
        int son=whichson[v][u];
        ans+=sumall[v]+1LL*dis(v,u)*cntall[v];
        ans-=sum[v][son]+1LL*dis(v,u)*cnt[v][son];
    }
    return ans;
}
void build()
{
    root=getroot(1,0,n).S;
    solve(root,0);
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v); G[v].push_back(u);
    }
    init(n);
    build();
    scanf("%d",&q);
    for(int i=0;i<q;i++)
    {
        cin>>str;
        int v;
        scanf("%d",&v);
        if(str[0]=='+') update(v,1); else update(v,-1);
        int rt=descend(root);
        fat.clear();
        printf("%lld\n",get_ans(rt));
    }
    return 0;
}