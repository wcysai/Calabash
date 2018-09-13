/*************************************************************************
    > File Name: E.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-06-15 21:53:22
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 505
#define MAXV 250005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
ll n,m,mp[MAXN][MAXN],x,y;
ll ans=0;
ll dx[8]={-1,-1,-1,0,0,1,1,1};
ll dy[8]={-1,0,1,-1,1,-1,0,1};
vector<ll> G[MAXV];
ll V;
ll d[MAXV];
bool used[MAXV];
void dijkstra(ll s)
{
    priority_queue<P> que;
    fill(d,d+V,INF);
    d[s]=-mp[s/m+1][s%m+1];
    que.push(P(d[s],s));
    memset(used,false,sizeof(used));
    used[s]=true;
    while(!que.empty())
    {
        P p=que.top(); que.pop();
        ll v=p.second;
        if(d[v]>p.first) continue;
        for(ll i=0;i<(int)G[v].size();i++)
        {
            int to=G[v][i];
            if(d[to]>d[v]&&!used[to])
            {
                d[to]=min(-mp[to/m+1][to%m+1],d[v]);
                que.push(P(d[to],to));
                used[to]=true;
            }
        }
    }
}
int main()
{
    scanf("%lld%lld",&n,&m);
    V=n*m;
    for(ll i=1;i<=n;i++)
        for(ll j=1;j<=m;j++)
            scanf("%lld",&mp[i][j]);
    scanf("%lld%lld",&x,&y);
    for(ll i=1;i<=n;i++)
        for(ll j=1;j<=m;j++)
        {
            if(mp[i][j]>=0) continue;
            for(ll k=0;k<8;k++)
            {
                ll ni=i+dx[k],nj=j+dy[k];
                if(ni<=0||nj<=0||ni>n||nj>m) continue;
                if(mp[ni][nj]>=0) continue;
                G[(i-1)*m+j-1].push_back((ni-1)*m+nj-1);
            }
        }
    dijkstra((x-1)*m+y-1);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(mp[i][j]<0&&d[(i-1)*m+(j-1)]!=INF) ans+=d[(i-1)*m+(j-1)];
    /*for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
            printf("%lld ",d[(i-1)*m+(j-1)]);
        puts("");
    }*/
    printf("%lld\n",ans);
    return 0;
}
