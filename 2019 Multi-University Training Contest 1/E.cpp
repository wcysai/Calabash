##include<bits/stdc++.h>
#define MAXN 10005
#define INF 1000000000000000LL
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
ll T,n,m;
struct edge{ll to,cost;};
vector<edge> G[MAXN];
ll d1[MAXN],d2[MAXN];
ll u[MAXN],v[MAXN],w[MAXN];
ll dp[MAXN];
bool valid[MAXN];

void dijkstra(ll s,ll *d)
{
    priority_queue<P,vector<P>,greater<P> > que;
    fill(d+1,d+n+1,INF);
    d[s]=0;
    que.push(P(0LL,s));
    while(!que.empty())
    {
        P p=que.top(); que.pop();
        ll v=p.second;
        if(d[v]<p.first) continue;
        for(ll i=0;i<(int)G[v].size();i++)
        {
            edge e=G[v][i];
            if(d[e.to]>d[v]+e.cost)
            {
                d[e.to]=d[v]+e.cost;
                que.push(P(d[e.to],e.to));
            }
        }
    }
}
struct eedge{ll to,cap,rev;};
vector<eedge> GG[MAXN];
ll level[MAXN];
ll iter[MAXN];
void add_edge(ll from,ll to,ll cap)
{
    GG[from].push_back((eedge){to,cap,(int)GG[to].size()});
    GG[to].push_back((eedge){from,0,(int)GG[from].size()-1});
}
void bfs(ll s)
{
    memset(level,-1,sizeof(level));
    queue<int> que;
    level[s]=0;
    que.push(s);
    while(!que.empty())
    {
        ll v=que.front(); que.pop();
        for(ll i=0;i<(int)GG[v].size();i++)
        {
            eedge &e=GG[v][i];
            if(e.cap>0&&level[e.to]<0)
            {
                level[e.to]=level[v]+1;
                que.push(e.to);
            }
        }
    }
}

ll dfs(ll v,ll t,ll f)
{
    if(v==t) return f;
    for(ll &i=iter[v];i<(int)GG[v].size();i++)
    {
        eedge &e=GG[v][i];
        if(level[v]<level[e.to]&&e.cap>0)
        {
            ll d=dfs(e.to,t,min(f,e.cap));
            if(d>0)
            {
                e.cap-=d;
                GG[e.to][e.rev].cap+=d;
                return d;
            }
        }
    }
    return 0;
}
ll max_flow(ll s,ll t)
{
    ll flow=0;
    for(;;)
    {
        bfs(s);
        if(level[t]<0) return flow;
        memset(iter,0,sizeof(iter));
        ll f;
        while((f=dfs(s,t,INF))>0)
          flow+=f;
    }
}
int main()
{
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld%lld",&n,&m);
        for(ll i=1;i<=n;i++) G[i].clear();
        for(ll i=1;i<=m;i++)
        {
            scanf("%lld%lld%lld",&u[i],&v[i],&w[i]);
            G[u[i]].push_back((edge){v[i],w[i]});
        }
        dijkstra(1,d1);
        for(ll i=1;i<=n;i++) G[i].clear();
        for(ll i=1;i<=m;i++)
        {
            G[v[i]].push_back((edge){u[i],w[i]});
        }
        dijkstra(n,d2);
        ll dis=d1[n];
        if(dis==INF)
        {
            puts("0");
            continue;
        }
        memset(valid,false,sizeof(valid));
        for(ll i=1;i<=n;i++) if(d1[i]+d2[i]==dis) valid[i]=true;
        for(ll i=1;i<=n;i++) GG[i].clear();
        for(ll i=1;i<=n;i++)
        {
            if(!valid[i]) continue;
            for(auto e:G[i])
            {
                if(valid[e.to]&&d2[e.to]==d2[i]+e.cost)
                {
                    add_edge(e.to,i,e.cost);
                }
            }
        }
        printf("%lld\n",max_flow(1,n));
    }
    return 0;
}
