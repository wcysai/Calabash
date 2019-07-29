#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 200005
#define MAXM 500005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> P;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef __gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;
vector<int> G[MAXN],GG[MAXN];
int n,m,dfn[MAXN],low[MAXN],st[MAXN];
int U[MAXM],V[MAXM];
int vis[MAXN];
int cmp[MAXN],cnt,tot,t,T,p;
vector<int> cc[MAXN];
void dfs(int v,int banned=-1)
{
    dfn[v]=low[v]=++tot;
    vis[v]=1;
    st[t++]=v;
    if(banned!=-1)
    {
        for(auto to:GG[v])
        {
            if(to==banned) continue;
            if(!vis[to])
            {
                dfs(to,banned);
                low[v]=min(low[v],low[to]);
            }
            else if(vis[to]==1) low[v]=min(low[v],dfn[to]);
        }
    }
    else
    {
        for(auto to:G[v])
        {
            if(!vis[to])
            {
                dfs(to);
                low[v]=min(low[v],low[to]);
            }
            else if(vis[to]==1) low[v]=min(low[v],dfn[to]);
        }
    }
    if(dfn[v]==low[v])
    {
        int u;
        cnt++;
        if(banned!=-1) return;
        do
        {
            u=st[t-1]; t--;
            cmp[u]=cnt;cc[cnt].push_back(u);
            vis[u]=2;
        }while(u!=v);
    }
}
int tarjan()
{
    t=tot=cnt=0;
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++) if(!dfn[i]) dfs(i);
    return cnt;
}
vector<int> rG[MAXN],dt[MAXN],bucket[MAXN];
int id,sdom[MAXN],idom[MAXN],arr[MAXN],rev[MAXN],par[MAXN],dsu[MAXN],label[MAXN];
bool pro[MAXN];
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
void dfs2(int v)
{
	T++;arr[v]=T;rev[T]=v;
	label[T]=T;sdom[T]=T;dsu[T]=T;
	for(int i=0;i<(int)GG[v].size();i++)
	{
		int to=GG[v][i];
		if(!arr[to]) dfs2(to),par[arr[to]]=arr[v];
		rG[arr[to]].push_back(arr[v]);
	}
}
void build_dominator_tree(int r)
{
    T=0; dfs2(r);int N=T;
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
	}
    for(int i=1;i<=N;i++) bucket[i].clear();
    for(int i=1;i<=N;i++) rG[i].clear();
}
void add_positive_edge()
{
    for(int i=1;i<=n;i++) GG[i].clear();
    for(int i=0;i<m;i++)
        if(cmp[U[i]]==cmp[V[i]])
            GG[U[i]].push_back(V[i]);
}
void add_reverse_edge()
{
    for(int i=1;i<=n;i++) GG[i].clear();
    for(int i=0;i<m;i++)
        if(cmp[U[i]]==cmp[V[i]])
            GG[V[i]].push_back(U[i]);
}
void dfs3(int v,int r)
{
    if(dt[v].size()!=0&&v!=r) pro[v]=true;
    for(auto to:dt[v]) dfs3(to,r);
}
void check()
{
    for(int i=1;i<=n;i++) dt[i].clear();
    for(int i=1;i<=n;i++) arr[i]=rev[i]=par[i]=sdom[i]=idom[i]=0;
    for(int i=1;i<=p;i++)
    {
        if(cc[i].size()<=1) continue;
        int s=cc[i][0];
        for(int j=0;j<(int)cc[i].size();j++) vis[cc[i][j]]=0;
        cnt=tot=t=0;
        for(int j=1;j<(int)cc[i].size();j++)
            if(!vis[cc[i][j]]) dfs(cc[i][j],s);
        if(cnt>=2) pro[s]=true;
        build_dominator_tree(s);
        dfs3(s,s);
    }
}
set<P> mp;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {  
        scanf("%d%d",&U[i],&V[i]);
        G[U[i]].push_back(V[i]);
    }
    memset(pro,false,sizeof(pro));
    p=tarjan(); 
    add_positive_edge();check();
    add_reverse_edge();check();
    for(int i=1;i<=n;i++) if(pro[i]) puts("YES"); else puts("NO");
    return 0;
}

