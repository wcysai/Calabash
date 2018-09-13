/*************************************************************************
    > File Name: L.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-08-22 12:53:02
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 205
#define MAXV 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int tot,n,m,K,W;
int s[MAXN],t[MAXN],v[MAXN],op[MAXN];
struct edge{int to,cap,cost,rev;};
int dist[MAXV],h[MAXV],prevv[MAXV],preve[MAXV];
int V;
vector<edge> G[MAXV];
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
        priority_queue<P,vector<P>,greater<P> >que;
        fill(dist,dist+V,INF);
        dist[s]=0;
        que.push(P(0,s));
        while(!que.empty())
        {
            P p=que.top(); que.pop();
            int v=p.second;
            if(dist[v]<p.first) continue;
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
int main()
{
    scanf("%d",&tot);
    while(tot--)
    {
        scanf("%d%d%d%d",&n,&m,&K,&W);
        for(int i=1;i<=m;i++)
            scanf("%d%d%d%d",&s[i],&t[i],&v[i],&op[i]);
        V=2*m+2;
        for(int i=0;i<V;i++) G[i].clear();
        int S=0,T=2*m+1;
        for(int i=1;i<=m;i++) add_edge(S,i,1,0);
        add_edge(S,T,INF,0);
        for(int i=1;i<=m;i++) add_edge(i,i+m,1,-v[i]);
        for(int i=1;i<=m;i++)
            for(int j=1;j<=m;j++)
                if(t[i]<=s[j]) add_edge(i+m,j,1,(op[i]==op[j])*W);
        for(int i=1;i<=m;i++) add_edge(i+m,T,1,0);
        printf("%d\n",-min_cost_flow(S,T,K));
    }
    return 0;
}
