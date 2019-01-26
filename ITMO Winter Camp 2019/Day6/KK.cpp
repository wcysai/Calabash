#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
struct edge{int to,cap,cost,rev;};
int dist[MAXN],h[MAXN],prevv[MAXN],preve[MAXN];
int V,n,m;
vector<edge> G[MAXN];
void add_edge(int from,int to,int cap,int cost)
{
    G[from].push_back((edge){to,cap,cost,(int)G[to].size()});
    G[to].push_back((edge){from,0,-cost,(int)G[from].size()-1});
}
int min_cost_flow(int s,int t,int f)
{
    int res=0;
    fill(h,h+V,0);
    while(f>0)
    {
        priority_queue<P,vector<P>,greater<P> > que;
        fill(dist,dist+V,INF);
        dist[s]=0;
        que.push(P(0,s));
        while(!que.empty())
        {
            P p=que.top();que.pop();
            int v=p.second;
            if(dist[v]<p.F) continue;
            for(int i=0;i<(int)G[v].size();i++)
            {
                edge &e=G[v][i];
                if(e.cap>0&&dist[e.to]>dist[v]+e.cost+h[v]-h[e.to])
                {
                    dist[e.to]=dist[v]+e.cost+h[v]-h[e.to];
                    prevv[e.to]=v;
                    preve[e.to]=i;
                    que.push(P(dist[e.to],e.to));
                }
            }
        }
        if(dist[t]==INF) return -1;
        for(int v=0;v<V;v++) h[v]+=dist[v];
        int d=f;
        for(int v=t;v!=s;v=prevv[v])
        {
            d=min(d,G[prevv[v]][preve[v]].cap);
        }
        f-=d;
        res+=d*h[t];
        for(int v=t;v!=s;v=prevv[v])
        {
            edge &e=G[prevv[v]][preve[v]];
            e.cap-=d;
            G[v][e.rev].cap+=d;
        }
    }
    return res;
}

int min1[305], min2[305];

int main()
{
    freopen("kingandroads.in","r",stdin);
    freopen("kingandroads.out","w",stdout);
    scanf("%d%d",&n,&m);
    for (int i = 1; i <= n; i++) min1[i] = min2[i] = INT_MAX;
    vector<tuple<int, int, int>> edges;
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        min1[u] = min(min1[u], w);
        min2[v] = min(min2[v], w);
        edges.emplace_back(u, v, w);
    }
    int ans = 0;
    for (int i=1; i<=n; i++) {
        if (min1[i]==INT_MAX or min2[i]==INT_MAX) {
            puts("NIE");
            return 0;
        }
        ans += min1[i] + min2[i];
    }
    V=2*n+2;
    for (auto p  : edges) {
        int u, v, w; tie(u, v, w) = p;
        add_edge(u,n+v, 1,w-min1[u]-min2[v]);
    }
    for(int i=1;i<=n;i++) add_edge(0,i,1,0);
    for(int i=n+1;i<=2*n;i++) add_edge(i,2*n+1,1,0);
    ans+=min_cost_flow(0,2*n+1,n);
    printf("%d\n",ans);
    return 0;
}

