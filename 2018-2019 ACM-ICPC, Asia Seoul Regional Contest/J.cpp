#include<bits/stdc++.h>
#define MAXN 1005
#define MAXM 8005
#define MAXC 25
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int N,W,C,H,M;
bool human[MAXN],base[MAXN];
bool vis[MAXN][MAXN];
vector<int> G[MAXN][MAXC];
bool bfs()
{
    memset(vis,false,sizeof(vis));
    queue<P> que;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            if(base[i]&&base[j]) que.push(P(i,j));
    while(que.size())
    {
        P p=que.front(); que.pop();
        if(human[p.F]^human[p.S]) return true;
        if(vis[p.F][p.S]) continue;
        vis[p.F][p.S]=true;
        for(int i=1;i<=C;i++)
        {
            for(auto to1:G[p.F][i])
                for(auto to2:G[p.S][i])
                {
                    if(vis[to1][to2]) continue;
                    if(human[to1]^human[to2]) return true;
                    que.push(P(to1,to2));
                } 
        }
    }
    return false;
}
int main()
{
    scanf("%d%d%d%d%d",&N,&W,&C,&H,&M);
    memset(human,false,sizeof(human));
    memset(base,false,sizeof(base));
    for(int i=0;i<H;i++)
    {
        int x;
        scanf("%d",&x); x++;
        human[x]=true;
    }
    for(int i=0;i<M;i++)
    {
        int x;
        scanf("%d",&x); x++;
        base[x]=true;
    }
    for(int i=0;i<W;i++)
    {
        int s,c,t;
        scanf("%d%d%d",&s,&c,&t);
        s++; t++;
        G[t][c].push_back(s);
    }
    if(bfs()) puts("YES"); else puts("NO");
    return 0;
}
