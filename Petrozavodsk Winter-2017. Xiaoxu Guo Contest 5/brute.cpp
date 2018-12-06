/*************************************************************************
    > File Name: brute.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-12-07 00:24:28
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,tot;
vector<int> G[MAXN];
P E[MAXN];
int dp[10][200][10][10];
//dp[step][mask][st][now]
//now moving step edges
//visited edges denoted by mask
//started from vertex st
//currently at vertex now
void add(int &a,int b) {a+=b;}
map<P,int> mp;
int main()
{
    tot=0;
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);G[v].push_back(u);
        mp[P(u,v)]=mp[P(v,u)]=tot;E[tot++]=P(u,v);
    }
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=n;i++) dp[0][0][i][i]=1;
    for(int step=0;step<6;step++)
    {
        for(int mask=0;mask<(1<<tot);mask++)
        {
            for(int st=1;st<=n;st++)
            {
                for(int now=1;now<=n;now++)
                {
                    if(!dp[step][mask][st][now]) continue;
                    for(auto to:G[now])
                    {
                        int id=mp[P(now,to)];
                        add(dp[step+1][mask|(1<<id)][st][to],dp[step][mask][st][now]);
                    }
                }
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++) add(ans,dp[6][(1<<tot)-1][i][i]);
    printf("%d\n",ans);
    return 0;
}

