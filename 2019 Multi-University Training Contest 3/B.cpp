#include<bits/stdc++.h>
#define MAXLOGN 20
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
vector<int> G[MAXN],rG[MAXN],dt[MAXN],bucket[MAXN];
int sdom[MAXN],idom[MAXN],arr[MAXN],rev[MAXN],par[MAXN],dsu[MAXN],label[MAXN];
int T,n,m,q,t;
int pa[MAXLOGN][MAXN];
int depth[MAXN],indeg[MAXN];
bool reach[MAXN];
int find(int u,int x=0)
{
	if(u==dsu[u]) return x?-1:u;
	int v=find(dsu[u],x+1);
	if(v<0) return u;
	if(sdom[label[dsu[u]]]<sdom[label[u]])
		label[u]=label[dsu[u]];
	dsu[u]=v;
	return x?v:label[u];
}
void unite(int u,int v)
{
	dsu[v]=u;
}
void dfs(int v)
{
	t++;arr[v]=t;rev[t]=v;
	label[t]=t;sdom[t]=t;dsu[t]=t;
	for(int i=0;i<(int)G[v].size();i++)
	{
		int to=G[v][i];
		if(!arr[to]) dfs(to),par[arr[to]]=arr[v];
		rG[arr[to]].push_back(arr[v]);
	}
}
void build_dominator_tree(int r)
{
    dfs(r);int N=t;
	for(int i=N;i>=1;i--)
	{
		for(int j=0;j<(int)rG[i].size();j++)
			sdom[i]=min(sdom[i],sdom[find(rG[i][j])]);
		if(i>1) bucket[sdom[i]].push_back(i);
		for(int j=0;j<(int)bucket[i].size();j++)
		{
			int w=bucket[i][j],v=find(w);
			if(sdom[v]==sdom[w]) idom[w]=sdom[w];
			else idom[w]=v;
		}
		if(i>1) unite(par[i],i);
	}
	for(int i=2;i<=N;i++)
	{
		if(idom[i]!=sdom[i]) idom[i]=idom[idom[i]];
		dt[rev[idom[i]]].push_back(rev[i]);
		dt[rev[i]].push_back(rev[idom[i]]);
		reach[rev[idom[i]]]=reach[rev[i]]=true;
	}
    for(int i=1;i<=N;i++) bucket[i].clear(),rG[i].clear();
}
void dfs(int v,int p,int d)
{
    pa[0][v]=p;
    depth[v]=d;
    for(int i=0;i<(int)dt[v].size();i++)
        if(dt[v][i]!=p) dfs(dt[v][i],v,d+1);
}
void init()
{
    dfs(n+1,0,0);
    for(int k=0;k+1<MAXLOGN;k++)
    {
        for(int v=1;v<=n+1;v++)
        {
            if(pa[k][v]<0) pa[k+1][v]=-1;
            else pa[k+1][v]=pa[k][pa[k][v]];
        }
    }
}
int get(int v,int x)
{
    for(int k=0;k<MAXLOGN;k++)
        if((x>>k)&1)
            v=pa[k][v];
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
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        t=0;
        for(int i=1;i<=n+1;i++) G[i].clear(),rG[i].clear(),dt[i].clear(),bucket[i].clear(),reach[i]=false,idom[i]=indeg[i]=par[i]=dsu[i]=sdom[i]=arr[i]=label[i]=rev[i]=0;
        for(int i=0;i<m;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            G[v].push_back(u);
            indeg[u]++;
        }
        for(int i=1;i<=n;i++) if(!indeg[i]) G[n+1].push_back(i);
        build_dominator_tree(n+1);
        init();
        scanf("%d",&q);
        for(int i=0;i<q;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            if(!reach[u]||!reach[v])
            {
                printf("%d\n",n);
                continue;
            }
            int x=lca(u,v);
            printf("%d\n",depth[u]+depth[v]-depth[x]);
        }
    }
    return 0;
}
