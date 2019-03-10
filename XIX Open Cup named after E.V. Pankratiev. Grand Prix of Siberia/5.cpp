const int MAXN = 100005;
#include<bits/stdc++.h>
#define MAXN 2005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k;
char gr[MAXN][MAXN];
vector<int> G[MAXN];
bool vis[MAXN];
vector<int> nodes;
vector<int> ans[MAXN];
bitset<2005> b[MAXN];
bitset<2005> cur;
int color[MAXN];
int d[MAXN][MAXN];
bool colored;
int curr;
void dfs(int v)
{
    vis[v]=true;
    nodes.push_back(v);
    for(auto to:G[v]) if(!vis[to]) dfs(to);
}
void bfs(int v)
{
    queue<int> que;
    que.push(v);
    cur.reset();cur.set(v);
    d[v][v]=0;
    int dis=0;
    while(que.size())
    {
        int u=que.front();que.pop();
        bitset<2005> tmp=(~cur)&b[u];
        if(d[v][u]>dis) dis++;
        for(int i=tmp._Find_first();i<tmp.size();i=tmp._Find_next(i)) 
        {
            d[v][i]=dis+1;
            que.push(i);
        }
        cur|=tmp; 
    }
}
void color_node(int v,int c)
{
    color[v]=c;
    ans[c].push_back(v);
    colored=true;
}
void color_graph()
{
    int sz=(int)nodes.size();
    if(k==0)
    {
        for(auto v: nodes) color_node(v,1);
        return;
    }
    int maxi=0;
    int u=-1,v=-1;
    for(int i=0;i<sz;i++)
        for(int j=i;j<sz;j++)
        {
            if(d[nodes[i]][nodes[j]]+1>maxi&&d[nodes[i]][nodes[j]]+1<=k)
            {
                maxi=d[nodes[i]][nodes[j]]+1;
                u=nodes[i];v=nodes[j];
            }
        }
    if(maxi==0)
    {
        if(!colored)
        {
            k--;color_node(nodes[0],++curr);
        }
        else assert(0);
        return;   
    }
    else
    {
        k-=maxi;
        for(auto x:nodes)
        {
            if(d[u][x]>d[u][v]) color_node(x,curr+maxi);
            else color_node(x,curr+d[u][x]+1);
        }
        curr+=maxi;
        return;
    }
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%s",gr[i]+1);
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
        {
            if(gr[i][j]=='1')
            {
                G[i].push_back(j);
                G[j].push_back(i);
                b[i].set(j);b[j].set(i);
            }
        }
    memset(vis,false,sizeof(vis));
    for(int i=1;i<=n;i++) 
        if(!vis[i])
        {
            dfs(i);
            for(auto v:nodes) bfs(v);
            color_graph();
            nodes.clear();
        }
    if(k>0) puts("Nope");
    else
    {
        puts("Yep");
        for(int i=1;i<=curr;i++) 
        {
            printf("%d ",(int)ans[i].size());
            for(auto v:ans[i]) printf("%d ",v);
            puts("");
        }
    }
    return 0;
}
