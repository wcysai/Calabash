//
// Created by calabash_boy on 18-5-29.
//
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
P a[MAXN],b[MAXN];
struct edge{int to,cap,cost,rev;};
int dist[MAXN],h[MAXN],prevv[MAXN],preve[MAXN];
int V;
vector<edge> G[MAXN];
void add_edge(int from,int to,int cap,int cost)
{
    G[from].push_back((edge){to,cap,cost,G[to].size()});
    G[to].push_back((edge){from,0,-cost,G[from].size()-1});
}
int min_cost_flow(int s,int t,int f)
{
    int res=0;
    fill(h,h+V,0);
    while(f>0)
    {
        priority_queue<P,vector<P>,greater<P> >que;
        fill(dist,dist+V,INF);
        dist[s]=0;
        que.push(P(0,s));
        while(!que.empty())
        {
            P p=que.top(); que.pop();
            int v=p.second;
            if(dist[v]<p.first) continue;
            for(int i=0;i<G[v].size();i++)
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
        if(dist[t]==INF)
        {
            return -1;
        }
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
int dis(P p,P q)
{
    return max(p.x-q.x,q.x-p.x)+max(p.y-q.y,q.y-p.y);
}
int rx,ry,ans;
int main()
{
    scanf("%d%d",&n,&m);
    int s=0;
    for(int i=0;i<n;i++)
        scanf("%d%d",&a[i].x,&a[i].y);
    for(int i=0;i<m;i++)
        scanf("%d%d",&b[i].x,&b[i].y);
    P rest;
    scanf("%d%d",&rest.x,&rest.y);
    ans=0;
    for(int i=0;i<n;i++)
        ans+=dis(a[i],rest);
    V=n+m+3;//s:0,t:1,rest:2,courier,3~m+2,wine:m+3~n+m+2
    for(int i=3;i<=m+2;i++)
        add_edge(0,i,1,0);
    add_edge(0,2,INF,0);
    for(int i=3;i<=m+2;i++)
        for(int j=m+3;j<=n+m+2;j++)
            add_edge(i,j,1,dis(b[i-3],a[j-m-3]));
    for(int j=m+3;j<=n+m+2;j++)
        add_edge(2,j,1,dis(rest,a[j-m-3]));
    for(int j=m+3;j<=n+m+2;j++)
        add_edge(j,1,1,0);
    int res=min_cost_flow(0,1,n);
    if(res==ans)
    {
        int inc=INF;
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                inc=min(inc,dis(b[i],a[j])-dis(a[j],rest));
        printf("%d\n",ans+res+inc);
    }
    else printf("%d\n",ans+res);
    return 0;
}
