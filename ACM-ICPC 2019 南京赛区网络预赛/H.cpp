#include<bits/stdc++.h>
#define MAXV 1000
#define MAXE 10000
#define INF 1000000000000000000LL
using namespace std;
typedef long long ll;
struct edge{ll to,cost;};
typedef pair<int,int> P;
ll T,V,E;
vector<edge> G[MAXV];
ll d[MAXV];
bool inque[MAXV];
queue<int> que;
void add_edge(ll from,ll to,ll cost)
{
    G[from].push_back((edge){to,cost});
}
void spfa(ll s)
{
    fill(d,d+V,INF);
    fill(inque,inque+V,false);
    d[s]=0;
    while(!que.empty()) que.pop();
    que.push(s);
    inque[s]=true;
    while(!que.empty())
    {
        ll u=que.front();
        que.pop();
        for(ll i=0;i<G[u].size();i++)
        {
            if(d[u]+G[u][i].cost<d[G[u][i].to])
            {
                d[G[u][i].to]=d[u]+G[u][i].cost;
                if(!inque[G[u][i].to])
                {
                    inque[G[u][i].to]=true;
                    que.push(G[u][i].to);
                }
            }
        }
        inque[u]=false;
    }
}
int main()
{
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld%lld",&V,&E);
        for(ll i=0;i<V;i++) G[i].clear();
        for(ll i=0;i<E;i++)
        {
            ll u,v,cost;
            scanf("%lld%lld%lld",&u,&v,&cost);
            add_edge(u,v,cost);
        }
        for(ll i=0;i<6;i++)
        {
            ll s,t;
            scanf("%lld%lld",&s,&t);
            spfa(t);
            ll dist=d[s];
            printf("%lld\n",-dist);
            add_edge(s,t,-dist);
        }
    }
    return 0;
}
