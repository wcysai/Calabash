#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,m;
int c[MAXN][MAXN],d[MAXN];
ll dp[MAXN][MAXN];
int main()
{
    scanf("%d",&T);
    for(int t=1;t<=T;t++)
    {
        scanf("%d%d",&n,&m);
        memset(dp,0,sizeof(dp));
        memset(c,0,sizeof(c));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%d",&c[i][j]);
        for(int i=1;i<=m;i++) scanf("%d",&d[i]);
        for(int i=1;i<=n;i++)
            for(int j=m;j>=0;j--)
                dp[i][j]=max(0LL,dp[i][j+1]-c[i][j+1]);
        ll ans=0,cur=0;
        for(int i=0;i<=m;i++)
        {
            cur+=d[i];
            for(int j=1;j<=n;j++) cur-=c[j][i];
            ll sum=0,mini=INF;
            for(int j=1;j<=n;j++) sum+=dp[j][i],mini=min(mini,dp[j][i]);
            ans=max(ans,sum+cur-mini);
        }
        printf("Case #%d: %lld\n",t,ans);
    }
    return 0;
}
