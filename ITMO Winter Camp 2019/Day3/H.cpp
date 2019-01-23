#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXK 15
#define MAXN 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int k,n[MAXK],m[MAXK];
vector<int> G[MAXK][MAXN];
int d[MAXK][MAXN];
void add_edge(int id,int u,int v)
{
    G[id][u].push_back(n[id]+v);
    G[id][n[id]+v].push_back(u);
    G[id][v].push_back(n[id]+u);
    G[id][n[id]+u].push_back(v);
}
void dijkstra(int id,int s)
{
    priority_queue<P,vector<P>, greater<P> >que;
    fill(d[id]+1,d[id]+2*n[id]+1,INF);
    d[id][s]=0;
    que.push(P(0,s));
    while(!que.empty())
    {
        P p=que.top();que.pop();
        int v=p.S;
        if(d[id][v]<p.F) continue;
        for(auto to:G[id][v])
        {   
            if(d[id][to]>d[id][v]+1)
            {
                d[id][to]=d[id][v]+1;
                que.push(P(d[id][to],to));
            }
        }
    }
}
int main()
{
    freopen("puzzle.in","r",stdin);
    freopen("puzzle.out","w",stdout);
    scanf("%d",&k);
    for(int i=1;i<=k;i++)
    {
        scanf("%d%d",&n[i],&m[i]);
        for(int j=0;j<m[i];j++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            add_edge(i,u,v);
        }
    }
    for(int i=1;i<=k;i++) dijkstra(i,1);
    int ans=INF,res1=0,res2=0;
    for(int i=1;i<=k;i++)
    {
        res1=max(res1,d[i][n[i]]);
        res2=max(res2,d[i][2*n[i]]);
    }
    ans=min(ans,res1);ans=min(ans,res2);
    if(ans==INF) puts("Impossible"); else printf("%d\n",ans);
    return 0;
}

