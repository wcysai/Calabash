#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define MAXM 300005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,s,t;
struct edge{int to,cost;};
typedef pair<int,int> P;
vector<edge> GG[MAXN];
int sz[MAXN];
void add_edge(int u,int v,int cost)
{
    GG[u].push_back((edge){v,cost});
    GG[v].push_back((edge){u,cost});
}
ll d[MAXN];
void dijkstra(int s)
{
    priority_queue<P,vector<P>,greater<P> > que;
    fill(d+1,d+n+1,INF);
    d[s]=0;
    que.push(P(0,s));
    while(!que.empty())
    {
        P p=que.top(); que.pop();
        int v=p.second;
        if(d[v]<p.first) continue;
        for(int i=0;i<(int)GG[v].size();i++)
        {
            edge e=GG[v][i];
            if(d[e.to]>d[v]+e.cost)
            {
                d[e.to]=d[v]+e.cost;
                que.push(P(d[e.to],e.to));
            }
        }
    }
}
vector<int> G[MAXN],rG[MAXN],dt[MAXN],bucket[MAXN];
int sdom[MAXN],idom[MAXN],arr[MAXN],rev[MAXN],par[MAXN],dsu[MAXN],label[MAXN];
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
void dfs2(int v)
{
    sz[v]=1;
    for(auto to:dt[v])
    {
        dfs2(to);
        sz[v]+=sz[to];
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&s);
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add_edge(u,v,w);
    }
    dijkstra(s);
    for(int i=1;i<=n;i++)
    {
        for(auto e:GG[i])
        {
            if(d[i]+e.cost==d[e.to]) G[i].push_back(e.to);
        }
    }
    dfs(s);n=t;
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
    dfs2(s);
    int ans=0;
    for(auto to:dt[s]) ans=max(ans,sz[to]);
    printf("%d\n",ans);
    return 0;
}

