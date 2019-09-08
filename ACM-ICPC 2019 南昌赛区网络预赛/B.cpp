#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,V,E,S,K,C;
struct edge{int to,cost;};
vector<int> v;
int d[MAXN];
vector<edge> G[MAXN];
int dijkstra(vector<int> v)
{
    priority_queue<P,vector<P>,greater<P> > que;
    fill(d+1,d+V+1,INF);
    for(auto s:v)
    {
        d[s]=0;
        que.push(P(0,s));
    }
    while(!que.empty())
    {
        P p=que.top(); que.pop();
        int v=p.second;
        if(d[v]<p.first) continue;
        for(int i=0;i<G[v].size();i++)
        {
            edge e=G[v][i];
            if(d[e.to]>d[v]+e.cost)
            {
                d[e.to]=d[v]+e.cost;
                que.push(P(d[e.to],e.to));
            }
        }
    }
    int ans=0;
    for(int i=1;i<=V;i++) ans=max(ans,d[i]);
    return ans;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d%d",&V,&E,&S,&K,&C);
        v.clear();
        for(int i=0;i<K;i++)
        {
            int x;
            scanf("%d",&x);
            v.push_back(x);
        }
        for(int i=1;i<=V;i++) G[i].clear();
        for(int i=0;i<E;i++)
        {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            G[u].push_back((edge){v,w}); G[v].push_back((edge){u,w});
        }
        int dist1=dijkstra(vector<int>{S}),dist2=dijkstra(v);
        if(dist2*C>=dist1) printf("%d\n",dist1); else printf("%d\n",dist2);
    }
    return 0;
}
