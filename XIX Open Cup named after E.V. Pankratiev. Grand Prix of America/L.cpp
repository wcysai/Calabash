#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,n1,n2;
vector<int> G[2*MAXN];
int mx[2*MAXN],my[2*MAXN];
queue<int> que;
int dx[2*MAXN],dy[2*MAXN];
bool vis[2*MAXN];
bool find(int u)
{
    for(int i=0;i<(int)G[u].size();i++)
    {
        if(!vis[G[u][i]]&&dy[G[u][i]]==dx[u]+1)
        {
            vis[G[u][i]]=true;
            if(!my[G[u][i]]||find(my[G[u][i]]))
            {
                mx[u]=G[u][i];
                my[G[u][i]]=u;
                return true;
            }
        }
    }
    return false;
}
int matching()
{
    memset(mx,0,sizeof(mx));
    memset(my,0,sizeof(my));
    int ans=0;
    while(true)
    {
        bool flag=false;
        while(!que.empty()) que.pop();
        memset(dx,0,sizeof(dx));
        memset(dy,0,sizeof(dy));
        for(int i=1;i<=n1;i++) if(!mx[i]) que.push(i);
        while(!que.empty())
        {
            int u=que.front(); que.pop();
            for(int i=0;i<(int)G[u].size();i++)
                if(!dy[G[u][i]])
                {
                    dy[G[u][i]]=dx[u]+1;
                    if(my[G[u][i]])
                    {
                        dx[my[G[u][i]]]=dy[G[u][i]]+1;
                        que.push(my[G[u][i]]);
                    }
                    else flag=true;
                }
        }
        if(!flag) break;
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n1;i++) if(!mx[i]&&find(i)) ans++;
    }
    return ans;
}
set<int> ans;
void bfs(int s,bool fl=true)
{
    queue<int> que;
    que.push(s);vis[s]=true;
    vector<int> valid; valid.clear(); valid.push_back(fl?s:s-n);
    while(que.size())
    {
        int u=que.front(); que.pop();
        for(auto to:G[u])
        {
            int v=fl?my[to]:mx[to];
            if(!v) continue;
            if(v==u) continue;
            if(!vis[v])
            {
                 vis[v]=true;que.push(v);
                 valid.push_back(fl?v:v-n);
            }
        }
    }
    for(auto x:valid) ans.insert(x);
}
int main()
{
    scanf("%d%d",&n,&m);
    n1=n2=n;
    for(int i=0;i<m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(n+v);
        G[n+v].push_back(u);
    }
    int res=n-1-matching();
    printf("%d\n",res);
    if(res==0) return 0;
    for(int i=1;i<=n;i++) if(!mx[i]) ans.insert(i);
    for(int i=n+1;i<=2*n;i++) if(!my[i]) ans.insert(i-n);
    memset(vis,false,sizeof(vis));
    for(int i=1;i<=n;i++) if(!vis[i]&&!mx[i]) bfs(i);
    for(int i=n+1;i<=2*n;i++) if(!vis[i]&&!my[i]) bfs(i,false);
    for(auto x:ans) printf("%d ",x);
    return 0;
}
