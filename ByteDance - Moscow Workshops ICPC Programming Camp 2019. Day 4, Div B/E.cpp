#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 905
#define MAXM 150005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
bool vis[MAXN];
int U[MAXM],V[MAXM];
struct edge
{
    int to,id;
};
vector<edge> G[MAXN];
vector<int> rG[MAXN];
int d[MAXN],d2[MAXN];
int res[MAXN],ans[MAXM],label[MAXN];
vector<int> SDT[MAXN];
void bfs(int s)
{
    memset(vis,false,sizeof(vis));
    fill(d+1,d+n+1,INF);
    d[s]=0;vis[s]=true;
    queue<int> que;
    que.push(s);
    while(que.size())
    {
        int v=que.front();que.pop();
        for(auto e:G[v])
        {
            int to=e.to;
            if(!vis[to])
            {
                d[to]=d[v]+1;
                SDT[v].push_back(to);
                vis[to]=true;
                que.push(to);
            }
        }
    }
}
void bfs2(int s,int lab)
{
    d2[s]=0;vis[s]=true;
    queue<int> que;
    que.push(s);
    while(que.size())
    {
        int v=que.front();que.pop();
        for(auto to:rG[v])
        {
            if(label[to]!=lab) continue;
            if(!vis[to])
            {
                d2[to]=d2[v]+1;
                vis[to]=true;
                que.push(to);
            }
        }
    }
}
void make_label(int v,int lab)
{
    label[v]=lab;
    for(auto to:SDT[v]) make_label(to,lab);
}
int main()
{
    while(scanf("%d%d",&n,&m)==2)
    {
        for(int i=1;i<=n;i++) G[i].clear(),rG[i].clear();
        for(int i=0;i<m;i++)
        {
            scanf("%d%d",&U[i],&V[i]);
            G[U[i]].push_back((edge){V[i],i});
            rG[V[i]].push_back(U[i]);
        }
        for(int i=1;i<=n;i++)
        {
            memset(label,0,sizeof(label));
            for(int j=1;j<=n;j++) SDT[j].clear();
            bfs(i);
            fill(d2+1,d2+n+1,INF);
            memset(vis,false,sizeof(vis));
            for(auto e:G[i]) 
            {
                res[e.to]=INF;
                make_label(e.to,e.to);
            }
            for(auto e:G[i]) bfs2(e.to,e.to);
            for(int j=0;j<m;j++)
            {
                if(U[j]==i||V[j]==i) continue;
                if(label[U[j]]==label[V[j]]) continue;
                if(d2[V[j]]==INF||d[U[j]]==INF) continue;
                res[label[V[j]]]=min(res[label[V[j]]],d[U[j]]+1+d2[V[j]]);
            }
            for(auto e:G[i]) ans[e.id]=res[e.to];
        }
        for(int i=0;i<m;i++) printf("%d%c",ans[i]==INF?0:ans[i],i==m-1?'\n':' ');
    }
    return 0;
}

