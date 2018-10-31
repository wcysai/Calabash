#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 30005
#define MAXM 60005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
struct edge{int to,cost;};
int n,m,k;
bool centroid[MAXN];
int sz[MAXN],d[MAXN];
P cnt[MAXN];
P deep[MAXN];
int ans;
bool vis[MAXN];
vector<edge> G[MAXN],GG[MAXN];
int curmax;
void dijkstra(int s)
{
    priority_queue<P,vector<P>,greater<P> >que;
    fill(d+1,d+n+1,INF);
    d[s]=0;
    que.push(P(0,s));
    while(!que.empty())
    {
        P p=que.top();que.pop();
        int v=p.S;
        if(d[v]<p.F) continue;
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
void build(int v)
{
    vector<int> nxt;nxt.clear();
    for(auto e:GG[v])
    {
        if(vis[e.to]) continue;
        if(d[v]+e.cost!=d[e.to]) continue;
        G[v].push_back((edge){e.to,e.cost});G[e.to].push_back((edge){v,e.cost});
        vis[e.to]=true;
        nxt.push_back(e.to);
    }
    sort(nxt.begin(),nxt.end());
    for(int i=0;i<(int)nxt.size();i++)
        build(nxt[i]);
}
P getroot(int v,int p,int t)
{
    P res=P(INT_MAX,-1);
    int m=0;
    sz[v]=1;
    for(int i=0;i<(int)G[v].size();i++)
    {
        int to=G[v][i].to;
        if(to==p||centroid[to]) continue;
        res=min(res,getroot(to,v,t));
        m=max(m,sz[to]);
        sz[v]+=sz[to];
    }
    m=max(m,t-sz[v]);
    res=min(res,P(m,v));
    return res;
}
void getdeep(int v,int p,int len)
{
    deep[++deep[0].F]=P(d[v],len);
    for(int i=0;i<(int)G[v].size();i++)
    {
        int to=G[v][i].to;
        if(to==p||centroid[to]) continue;
        d[to]=d[v]+G[v][i].cost;
        getdeep(to,v,len+1);
    }
}
void cal(int v,int cost)
{
    d[v]=cost;deep[0].F=0;
    getdeep(v,0,1);
    for(int i=1;i<=deep[0].F;i++)
    {
        if(deep[i].S>k-1) continue;
        if(deep[i].F+cnt[k-1-deep[i].S].S>curmax)
        {
            curmax=deep[i].F+cnt[k-1-deep[i].S].S;
            ans=cnt[k-1-deep[i].S].F;
        }
        else if(deep[i].F+cnt[k-1-deep[i].S].S==curmax) ans+=cnt[k-1-deep[i].S].F;
    }
    for(int i=1;i<=deep[0].F;i++)
    {
        if(deep[i].F>cnt[deep[i].S].S) {cnt[deep[i].S].S=deep[i].F; cnt[deep[i].S].F=1;}
        else if(deep[i].F==cnt[deep[i].S].S) cnt[deep[i].S].F++;
    }
}
void solve(int v)
{
    centroid[v]=true;
    for(int i=0;i<=sz[v];i++) cnt[i]=P(0,0);
    cnt[0]=P(1,0);
    for(int i=0;i<(int)G[v].size();i++)
    {
        int to=G[v][i].to,cost=G[v][i].cost;
        if(centroid[to]) continue;
        cal(to,cost);
    }
    for(int i=0;i<(int)G[v].size();i++)
    {
        int to=G[v][i].to,cost=G[v][i].cost;
        if(centroid[to]) continue;
        int rt=getroot(to,v,sz[to]).S;
        solve(rt);
    }
}
void ac()
{
    ans=0;
    int rt=getroot(1,0,n).S;
    solve(rt);
    printf("%d %d\n",curmax,ans);
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        GG[u].push_back((edge){v,w});GG[v].push_back((edge){u,w});
    }
    dijkstra(1);
    memset(vis,false,sizeof(vis));
    vis[1]=true;
    build(1);
    ac();
    return 0;
}
