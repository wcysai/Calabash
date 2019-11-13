#include<bits/stdc++.h>
#define MAXN 300005
#define INF 1000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int N;
struct edge{int to,cost;};
vector<edge> G[MAXN];
int facost[MAXN];
ll f[MAXN],sum[MAXN],g[MAXN];
void add_edge(int u,int v,int x,int y)
{
    G[u].push_back((edge){v,y});
    G[v].push_back((edge){u,x});
}
void dfs(int v,int p)
{
    f[v]=0;
    for(auto e:G[v])
    {
        int to=e.to,cost=e.cost;
        if(to==p)
        {
            facost[v]=cost;
            continue;
        }
        dfs(to,v);
        f[v]+=min(1LL*cost,f[to]);
    }
    if(!f[v]) f[v]=INF;
}
void dfs2(int v,int p)
{
    for(auto e:G[v])
    {
        int to=e.to,cost=e.cost;
        if(to==p) continue;
        ll ccost=g[v]-min(1LL*cost,f[to]);
        if(ccost==0) ccost=INF;
        g[to]=f[to]+min(ccost,1LL*facost[to]);
        dfs2(to,v);
    }
}
int main()
{
    scanf("%d",&N);
    for(int i=0;i<N-1;i++)
    {
        int u,v,x,y;
        scanf("%d%d%d%d",&u,&v,&x,&y);
        add_edge(u,v,x,y);
    }
    dfs(1,0);
    g[1]=f[1]; dfs2(1,0);
    for(int i=1;i<=N;i++) printf("%lld\n",g[i]%INF);
    return 0;
}
