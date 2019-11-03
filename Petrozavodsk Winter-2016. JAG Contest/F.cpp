#include<bits/stdc++.h>
#define MAXN 100005
#define INF 100000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int N,M,A,B,C;
vector<int> a,b,c;
vector<int> G[MAXN];
vector<int> GG[MAXN];
int d[4][MAXN],minlab[4][MAXN];
int label[MAXN];
int mini[MAXN];
bool vis[4];
void bfs(int id,int v)
{
    fill(d[id]+1,d[id]+N+4,INF);
    for(int i=1;i<=N+3;i++) minlab[id][i]=mini[i];
    queue<int> que; d[id][v]=0; que.push(v);
    while(que.size())
    {
        int x=que.front();
        que.pop();
        for(auto to:G[x])
        {
            if(d[id][to]==INF)
            {
                d[id][to]=d[id][x]+1;
                que.push(to);
            }
            if(d[id][to]==d[id][x]+1) minlab[id][to]=min(minlab[id][to],minlab[id][x]);
        }
    }
}

int main()
{
    scanf("%d%d%d%d",&N,&A,&B,&C);
    for(int i=1;i<=A;i++)
    {
        int x; scanf("%d",&x);
        a.push_back(x);
        label[x]=1;
    }
    for(int i=1;i<=B;i++)
    {
        int x;scanf("%d",&x);
        b.push_back(x);
        label[x]=2;
    }
    for(int i=1;i<=C;i++)
    {
        int x;scanf("%d",&x);
        c.push_back(x);
        label[x]=3;
    }
    scanf("%d",&M);
    for(int i=0;i<M;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(label[x]&&label[x]==label[y]) continue;
        int u=label[x]?N+label[x]:x,v=label[y]?N+label[y]:y;
        G[u].push_back(v); G[v].push_back(u);
    }
    mini[N+1]=mini[N+2]=mini[N+3]=INF;
    for(int i=1;i<=N;i++)
    {
        if(!label[i]) mini[i]=i;
        else mini[N+label[i]]=min(mini[N+label[i]],i);
    }
    bfs(1,N+1); bfs(2,N+2); bfs(3,N+3);
    int sum=INF,id=-1;
    for(int i=1;i<=N+3;i++)
    {
        if(label[i]) continue;
        //printf("%d %d %d %d %d %d %d\n",i,d[1][i],d[2][i],d[3][i],minlab[1][i],minlab[2][i],minlab[3][i]);
        if(d[1][i]+d[2][i]+d[3][i]<sum||(d[1][i]+d[2][i]+d[3][i]==sum&&min(min(minlab[1][i],minlab[2][i]),minlab[3][i])<id))
        {
            sum=d[1][i]+d[2][i]+d[3][i];
            id=min(min(minlab[1][i],minlab[2][i]),minlab[3][i]);
        }
    }
    printf("%d %d\n",sum,id);
    return 0;
}
