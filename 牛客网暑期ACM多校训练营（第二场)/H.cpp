/*************************************************************************
    > File Name: H.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-08-05 10:44:06
 ************************************************************************/
 
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 400005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll n,w[MAXN];
vector<int> G[MAXN];
ll f[MAXN][4],g[MAXN][4];
void mx(ll &u,ll v) {u=max(u,v);}
void dfs(ll v,ll p)
{
    ll a[4][3]={0},b[4][3]={0},c[4][3]={0};
    for(ll i=0;i<(int)G[v].size();i++)
    {
        ll to=G[v][i];
        if(to==p) continue;
        dfs(to,v);
        memset(b,0,sizeof(b));
        for(ll x=0;x<=3;x++) b[x][0]=f[to][x],b[x][1]=g[to][x];
        memset(c,0,sizeof(c));
        for(ll x=0;x<=3;x++)
            for(ll y=0;x+y<=3;y++)
                for(ll p=0;p<=2;p++)
                    for(ll q=0;p+q<=2;q++)
                        mx(c[x+y][p+q],a[x][p]+b[y][q]);
        memcpy(a,c,sizeof(c));
    }
    for(ll x=0;x<=3;x++) mx(f[v][x],a[x][0]);
    for(ll x=1;x<=3;x++)
        for(ll y=0;y<=2;y++)
            mx(f[v][x],a[x-1][y]+w[v]);
    for(ll x=0;x<=3;x++)
        for(ll y=0;y<=1;y++)
            mx(g[v][x],a[x][y]+w[v]);
}
int main()
{
    scanf("%lld",&n);
    for(ll i=1;i<=n;i++) scanf("%lld",&w[i]);
    for(ll i=0;i<n-1;i++)
    {
        ll u,v;
        scanf("%lld%lld",&u,&v);
        G[u].push_back(v);G[v].push_back(u);
    }
    dfs(1,0);
    printf("%lld\n",f[1][3]);
    return 0;
}
