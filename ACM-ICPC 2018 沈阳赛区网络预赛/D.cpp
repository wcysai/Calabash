#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN = 1100;
const int MAXM = 110000;
const int INF = 0xffffff0;

struct EdgeNode
{
    int to;
    int w;
    int next;
}Edges[MAXM],Edges1[MAXM];

int Head[MAXN],Head1[MAXN];

struct Node
{
    int to;
    int g,f;
    bool operator < (const Node &r) const
    {
        if(r.f == f)
            return r.g < g;
        return r.f < f;
    }
};
int vis[MAXN],Dist[MAXN];

int A_Star(int start,int end,int N,int k)
{
    Node e,ne;
    int Cnt = 0;
    priority_queue<Node> que;
    if(start == end)
        k++;
    if(Dist[start] == INF)
        return -1;
    e.to = start;
    e.g = 0;
    e.f = e.g + Dist[e.to];
    que.push(e);
    while( !que.empty() )
    {
        e = que.top();
        que.pop();
        if(e.to == end)
            Cnt++;
        if(Cnt == k)
            return e.g;

        for(int i = Head[e.to]; i != -1; i = Edges[i].next)
        {
            ne.to = Edges[i].to;
            ne.g = e.g + Edges[i].w;
            ne.f = ne.g + Dist[ne.to];
            que.push(ne);
        }
    }
    return -1;
}
void SPFA(int s,int N)
{
    for(int i = 0; i <= N; ++i)
        Dist[i] = INF;
    memset(vis,0,sizeof(vis));
    vis[s] = 1;
    Dist[s] = 0;
    queue<int> Q;
    Q.push(s);
    while( !Q.empty() )
    {
        int u = Q.front();
        Q.pop();
        vis[u] = 0;
        for(int i = Head1[u]; i != -1; i = Edges1[i].next)
        {
            int temp = Dist[u] + Edges1[i].w;
            if(temp < Dist[Edges1[i].to])
            {
                Dist[Edges1[i].to] = temp;
                if(!vis[Edges1[i].to])
                {
                    vis[Edges1[i].to] = 1;
                    Q.push(Edges1[i].to);
                }
            }
        }
    }
}

int main()
{
    int N,M,u,v,w,s,t,k,tt;
    while(~scanf("%d%d",&N,&M))
    {
      
        scanf("%d%d%d%d",&s,&t,&k, &tt);
        memset(Edges,0,sizeof(Edges));
        memset(Edges1,0,sizeof(Edges1));
        memset(Head,-1,sizeof(Head));
        memset(Head1,-1,sizeof(Head1));
        for(int i = 0; i < M; ++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            Edges[i].to = v;
            Edges[i].w = w;
            Edges[i].next = Head[u];
            Head[u] = i;

            Edges1[i].to = u;
            Edges1[i].w = w;
            Edges1[i].next = Head1[v];
            Head1[v] = i;
        }
        SPFA(t,N);
        int kthlen = A_Star(s,t,N,k);
        puts(kthlen <= tt && kthlen >= 0 ? "yareyaredawa" : "Whitesnake!");
    }

    return 0;
}
