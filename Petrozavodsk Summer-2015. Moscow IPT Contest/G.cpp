#include<bits/stdc++.h>
#define MAXN 100005
#define MAXLOGN 18
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef long double db;
int n,q,pa[MAXLOGN][MAXN],depth[MAXN],deg[MAXN];
vector<int> G[MAXN];
db f[MAXLOGN][MAXN],g[MAXLOGN][MAXN];
void dfs1(int v,int p,int d)
{
    pa[0][v]=p;
    depth[v]=d;
    f[0][v]=deg[v];
    db s=0;
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs1(to,v,d+1);
        s+=f[0][to];
    }
    f[0][v]+=s;
}
void dfs2(int v,int p)
{
    db s=g[0][v];
    for(auto to:G[v])
    {
        if(to==p) continue;
        s+=f[0][to];
    }
    for(auto to:G[v])
    {
        if(to==p) continue;
        g[0][to]=deg[v]+(s-f[0][to]);
        dfs2(to,v);
    }
}
void init(int V)
{
    dfs1(1,-1,0);
    dfs2(1,0);
    f[0][1]=0;
    for(int k=0;k+1<MAXLOGN;k++)
    {
        for(int v=1;v<=V;v++)
        {
            if(pa[k][v]<0) pa[k+1][v]=-1;
            else pa[k+1][v]=pa[k][pa[k][v]];
        }
    }
    for(int k=0;k+1<MAXLOGN;k++)
    {
        for(int v=1;v<=V;v++)
        {
            if(pa[k][v]<0) f[k+1][v]=f[k][v];
            else f[k+1][v]=f[k][v]+f[k][pa[k][v]];
        }
    }
    for(int k=0;k+1<MAXLOGN;k++)
    {
        for(int v=1;v<=V;v++)
        {
            if(pa[k][v]<0) g[k+1][v]=g[k][v];
            else g[k+1][v]=g[k][v]+g[k][pa[k][v]];
        }
    }
}
int get(int v,int x)
{
    for(int k=0;k<MAXLOGN;k++)
        if((x>>k)&1) v=pa[k][v];
    return v;
}
int lca(int u,int v)
{
    if(depth[u]>depth[v]) swap(u,v);
    v=get(v,depth[v]-depth[u]);
    if(u==v) return u;
    for(int k=MAXLOGN-1;k>=0;k--)
    {
        if(pa[k][u]!=pa[k][v])
        {
            u=pa[k][u];
            v=pa[k][v];
        }
    }
    return pa[0][u];
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);G[v].push_back(u);
        deg[u]++;deg[v]++;
    }
    memset(pa,-1,sizeof(pa));
    memset(f,0,sizeof(f));
    memset(g,0,sizeof(g));
    init(n);
    scanf("%d",&q);
    for(int i=0;i<q;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        int l=lca(u,v);
        db ans=0;
        int x=depth[u]-depth[l];
        for(int k=0;k<MAXLOGN;k++)
            if((x>>k)&1) {ans+=f[k][u]; u=pa[k][u];}
        x=depth[v]-depth[l];
        for(int k=0;k<MAXLOGN;k++)
            if((x>>k)&1) {ans+=g[k][v]; v=pa[k][v];}
        printf("%.10Lf\n",ans);
    }
    return 0;
}
