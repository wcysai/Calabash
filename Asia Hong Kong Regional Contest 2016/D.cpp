#include<bits/stdc++.h>
#define MAXN 75
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,K,p[MAXN],c[MAXN];
vector<int> v;
ll dp[MAXN][MAXN][2*MAXN*MAXN],mdp[MAXN][MAXN][2*MAXN*MAXN];
int main()
{
    scanf("%d%d",&n,&K);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&p[i],&c[i]);
        for(int j=max(1,p[i]-n);j<=p[i]+n;j++) v.push_back(j);
    }
    v.push_back(0);
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    for(int i=0;i<=n;i++)
        for(int j=0;j<=n;j++)
            for(int k=0;k<(int)v.size();k++)
                dp[i][j][k]=mdp[i][j][k]=INF;
    dp[0][0][0]=0;
    for(int k=0;k<(int)v.size();k++) mdp[0][0][k]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            for(int k=0;k<(int)v.size();k++)
            {
                dp[i][j][k]=dp[i-1][j][k]+(p[i]>v[k]?1LL*(p[i]-v[k])*c[i]:0);
                if(j&&k) dp[i][j][k]=min(dp[i][j][k],mdp[i-1][j-1][k-1]+1LL*max(v[k]-p[i],p[i]-v[k])*c[i]);
            }
            mdp[i][j][0]=dp[i][j][0];
            for(int k=1;k<(int)v.size();k++) mdp[i][j][k]=min(mdp[i][j][k-1],dp[i][j][k]);
        }
    }
    ll ans=INF;
    for(int j=K;j<=n;j++)
        for(int k=0;k<(int)v.size();k++)
            ans=min(ans,dp[n][j][k]);
    printf("%lld\n",ans);
    return 0;
}
