#include<bits/stdc++.h>
#define MAXN 300005
#define MAXM 400005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
vector<int> G[MAXN],rG[MAXN],dt[MAXN],bucket[MAXN];
int sdom[MAXN],idom[MAXN],arr[MAXN],rev[MAXN],par[MAXN],dsu[MAXN],label[MAXN];
int n,m,t,r;
int sz[MAXN];
vector<int> redu;
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
    dfs(r);int n=t;
	for(int i=n;i>=1;i--)
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
	for(int i=2;i<=n;i++)
	{
		if(idom[i]!=sdom[i]) idom[i]=idom[idom[i]];
		dt[rev[idom[i]]].push_back(rev[i]);
	}
}
void dfs2(int v)
{
    sz[v]=1;
    for(auto to:dt[v])
    {
        dfs2(to);
        sz[v]+=sz[to];
    }
    if(sz[v]==1&&v>n-m) redu.push_back(v-(n-m));
}
int main()
{
    scanf("%d%d%d",&n,&m,&r);
    for(int i=0;i<m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        n++;G[u].push_back(n);G[n].push_back(v);
    }
    build_dominator_tree(r);
    dfs2(r);
    for(int i=n-m+1;i<=n;i++) if(!arr[i]) redu.push_back(i-(n-m));
    sort(redu.begin(),redu.end());
    printf("%d\n",(int)redu.size());
    for(auto v:redu) printf("%d ",v);
    puts("");
    return 0;
}
	
