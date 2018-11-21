/*************************************************************************
    > File Name: J.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-11-19 18:07:35
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 20005
#define MAXM 25000
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,dep[MAXN];
vector<int> G[MAXN];
int dp[11][60000],p[11],vis[MAXN],c[MAXN];
int st[11],tot;
int bit(int s,int w)
{
    return (s/p[w])%3;
}
void relax(int &a,int b)
{
    a=min(a,b);
}
/*
 dp[v][0] : chosen
 dp[v][1] : not chosen and not satisfied
 dp[v][2] : not chosen but satisfied
 */
void dfs(int v,int d)
{
    vis[v]=true;dep[v]=d;
    memset(dp[dep[v]],0x3f,sizeof(dp[dep[v]]));
    if(!d) 
    {
        dp[0][0]=c[v];
        dp[0][1]=0;
        dp[0][2]=INF;
    }
    else
    {
        static bool ok[MAXN];
        memset(ok,false,sizeof(ok));
        for(auto to:G[v])
        {
            if(vis[to]) ok[dep[to]]=true;
        }
        for(int s=0;s<p[dep[v]];s++)
        {
            if(dp[dep[v]-1][s]==INF) continue;
            bool has=false;
            int news=s;
            for(int i=0;i<dep[v];i++)
            {
                has|=ok[i]&&bit(s,i)==0;
                news+=p[i]*(ok[i]&&bit(s,i)==1);
            }
            if(has) relax(dp[dep[v]][s+p[dep[v]]*2],dp[dep[v]-1][s]);
            else relax(dp[dep[v]][s+p[dep[v]]],dp[dep[v]-1][s]);
            relax(dp[dep[v]][news],dp[dep[v]-1][s]+c[v]);
        }
    }
    for(auto to:G[v])
    {
        if(!vis[to])
        {
            dfs(to,d+1);
            for(int s=0;s<p[dep[v]+1];s++)
            {
                dp[dep[v]][s]=min(dp[dep[v]+1][s],dp[dep[v]+1][s+p[dep[v]+1]*2]);
            }
        }
    }
}
int main()
{
    p[0]=1;
    for(int i=1;i<=10;i++) p[i]=3*p[i-1];
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&c[i]);
    for(int i=0;i<m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);G[v].push_back(u);
    }
    memset(vis,false,sizeof(vis));
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        if(!vis[i])
        {
            dfs(i,0);
            ans+=min(dp[0][0],dp[0][2]);
        }
    }
    printf("%d\n",ans);
    return 0;
}

