#include<bits/stdc++.h>
#define MAXN 20
#define MAXM (1<<20)
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
ll val[2][MAXM];
ll dp[2][MAXM];
bool vis[2][MAXM];
ll solve(int color,int mask)
{
    if(__builtin_popcount(mask)==0) return val[color][mask];
    if(vis[color][mask]) return dp[color][mask];
    vis[color][mask]=true;
    dp[color][mask]=val[color][mask];
    for(int i=0;i<n;i++)
    {
        if(mask&(1<<i))
        {
            ll res=val[color][mask]-val[color][mask^(1<<i)]+min(solve(color^1,mask^(1<<i)),solve(color,mask^(1<<i)));
            dp[color][mask]=min(dp[color][mask],res);
        }
    }
    return dp[color][mask];
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<(1<<n);i++) scanf("%lld",&val[0][i]);
    for(int i=0;i<(1<<n);i++) scanf("%lld",&val[1][i]);
    for(int i=0;i<n;i++)
        for(int mask=0;mask<(1<<n);mask++)
            if(mask&(1<<i)) 
            {
                val[0][mask]+=val[0][mask^(1<<i)];
                val[1][mask]+=val[1][mask^(1<<i)];
            }
    memset(vis,false,sizeof(vis));
    printf("%lld\n",min(solve(0,(1<<n)-1),solve(1,(1<<n)-1)));
    return 0;
}