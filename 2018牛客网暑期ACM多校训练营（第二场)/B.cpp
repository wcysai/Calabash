/*************************************************************************
    > File Name: B.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-08-05 08:53:57
 ************************************************************************/
 
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll n,k,p[MAXN],d[MAXN],f[MAXN];
bool used[MAXN],mark[MAXN];
vector<int> G[MAXN];
ll g[MAXN][2];//f[v][0]:can use discount,f[v][1]:can't used discount
ll dp[MAXN][2],ans=0;
void dfs(ll v)
{
    used[v]=true;
    ll res=INF,s=0;
    for(ll i=0;i<(int)G[v].size();i++)
    {
        ll to=G[v][i];
        if(mark[to]) continue;
        dfs(to);
        res=min(res,g[to][1]-g[to][0]);
        s+=g[to][0];
    }
    g[v][1]=p[v]+s;
    g[v][0]=min(p[v]-d[v]+s,s+res);
}
void solve(ll v)
{
    while(!used[v]) {used[v]=true; v=f[v];}
    vector<int> vi;vi.clear();vi.push_back(v);
    while(f[vi.back()]!=v) vi.push_back(f[vi.back()]);
    for(ll i=0;i<(int)vi.size();i++) mark[vi[i]]=true;
    for(ll i=0;i<(int)vi.size();i++) dfs(vi[i]);
    ll res=INF;
    for(ll choose=0;choose<=1;choose++)
    {
        dp[0][1]=g[vi[0]][1];
        dp[0][0]=choose?g[vi[0]][1]-p[vi[0]]:g[vi[0]][0];
        for(ll i=1;i<(int)vi.size();i++)
        {
            dp[i][0]=min(dp[i-1][0]+g[vi[i]][0],dp[i-1][1]+g[vi[i]][1]-p[vi[i]]);
            dp[i][1]=dp[i-1][0]+g[vi[i]][1];
        }
        res=min(res,dp[vi.size()-1][choose]);
    }
    ans+=res;
}
int main()
{
    scanf("%lld",&n);
    for(ll i=1;i<=n;i++) scanf("%lld",&p[i]);
    for(ll i=1;i<=n;i++) scanf("%lld",&d[i]);
    for(ll i=1;i<=n;i++)
    {
        scanf("%lld",&f[i]);
        if(f[i]!=i) G[f[i]].push_back(i);
    }
    memset(used,false,sizeof(used));
    memset(mark,false,sizeof(mark));
    for(ll i=1;i<=n;i++) if(!used[i]) solve(i);
    printf("%lld\n",ans);
    return 0;
}
