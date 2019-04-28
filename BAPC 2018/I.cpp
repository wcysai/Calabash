#include<bits/stdc++.h>
#define int ll
#define MAXN 200005
#define MAXS 21
#define MOD 1000000007
#define F first
#define S second
const long long INF = 0x3f3f3f3f3f3f3f3fLL;
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
struct edge{int to,cost;};
struct edge2{int to,cap,rev;};
vector<edge2> g[MAXN];
int level[MAXN],iter[MAXN];
vector<edge> G[MAXN];
int n,m,s,p[MAXN];
int a[MAXS],b[MAXS];
int d[MAXS][MAXN];
void dijkstra(int id,int s)
{
    priority_queue<P,vector<P>,greater<P> > que;
    fill(d[id]+1,d[id]+n+1,INF);
    d[id][s]=0;
    que.push(P(0,s));
    while(!que.empty())
    {
        P p=que.top(); que.pop();
        int v=p.S;
        if(d[id][v]<p.F) continue;
        for(int i=0;i<(int)G[v].size();i++)
        {
            edge e=G[v][i];
            if(d[id][e.to]>d[id][v]+e.cost)
            {
                d[id][e.to]=d[id][v]+e.cost;
                que.push(P(d[id][e.to],e.to));
            }
        }
    }
}
void add_edge(int from,int to,int cap)
{
    g[from].push_back((edge2){to,cap,(int)g[to].size()});
    g[to].push_back((edge2){from,0,(int)g[from].size()-1});
}
void bfs(int s)
{
    memset(level,-1,sizeof(level));
    queue<int> que;
    level[s]=0;
    que.push(s);
    while(!que.empty())
    {
        int v=que.front(); que.pop();
        for(int i=0;i<(int)g[v].size();i++)
        {
            edge2 &e=g[v][i];
            if(e.cap>0&&level[e.to]<0)
            {
                level[e.to]=level[v]+1;
                que.push(e.to);
            }
        }
    }
}
int dfs(int v,int t,int f)
{
    if(v==t) return f;
    for(int &i=iter[v];i<(int)g[v].size();i++)
    {
        edge2 &e=g[v][i];
        if(level[v]<level[e.to]&&e.cap>0)
        {
            int d=dfs(e.to,t,min(f,e.cap));
            if(d>0)
            {
                e.cap-=d;
                g[e.to][e.rev].cap+=d;
                return d;
            }
        }
    }
    return 0;
}
int max_flow(int s,int t)
{
    int flow=0;
    for(;;)
    {
        bfs(s);
        if(level[t]<0) return flow;
        memset(iter,0,sizeof(iter));
        int f;
        while((f=dfs(s,t,INF))>0) flow+=f;
    }
}
ll res[(1<<MAXS)];
bool check(ll x)
{
    memset(res,0,sizeof(res));
    for(int i=1;i<=n;i++)
    {
        int mask=0;
        for(int j=1;j<=s;j++) if(d[j][i]<=x) mask|=(1<<(j-1));
        res[mask]+=p[i];
    }
    for(int i=0;i<2000;i++) g[i].clear();
    int V=(1<<s)+s+2;
    int S=V,T=V-1;
    for(int i=0;i<(1<<s);i++)
        for(int j=0;j<s;j++)
            if((i>>j)&1) add_edge(i+1,(1<<s)+j+1,INF);
    ll sum=0;
    for(int i=0;i<(1<<s);i++) 
    {
        add_edge(S,i+1,res[i]);
        sum+=res[i];
    }
    for(int j=0;j<s;j++) add_edge((1<<s)+j+1,T,b[j+1]);
    return max_flow(S,T)==sum;
}
signed main()
{
    scanf("%lld%lld%lld",&n,&m,&s);
    for(int i=1;i<=n;i++) scanf("%lld",&p[i]);
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        scanf("%lld%lld%lld",&u,&v,&w);
        G[u].push_back((edge){v,w}); G[v].push_back((edge){u,w});
    }
    for(int i=1;i<=s;i++) scanf("%lld%lld",&a[i],&b[i]);
    for(int i=1;i<=s;i++) dijkstra(i,a[i]);
    ll l=-1,r=INF;
    while(r-l>1)
    {
        ll mid=(l+r)/2;
        if(check(mid)) r=mid; else l=mid;
    }
    printf("%lld\n",r);
    return 0;
}
