#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 300005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
vector<int> G[MAXN];
int sz[MAXN];
ll f[MAXN],g[MAXN];
P a[MAXN];
void dfs(int v,int p)
{
    sz[v]=1;f[v]=0;
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs(to,v);
        sz[v]+=sz[to];
        f[v]+=f[to]+sz[to];
    }
}
void dfs2(int v,int p)
{
    for(auto to:G[v])
    {
        if(to==p) continue;
        g[to]=f[v]-f[to]+g[v]+n-sz[to]-sz[to];
        dfs2(to,v);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        a[i]=P(u,v);
        G[u].push_back(v);G[v].push_back(u);
    }
    dfs(1,0);dfs2(1,0);
    for(int i=0;i<n-1;i++)
    {
        int u=a[i].F,v=a[i].S;
        if(f[u]<f[v]) swap(u,v);
        printf("%lld\n",sz[v]*g[v]+f[v]*(n-sz[v]));
    }
    return 0;
}

