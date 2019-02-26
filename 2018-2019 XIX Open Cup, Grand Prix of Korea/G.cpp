#include<bits/stdc++.h>
#define MAXN 250005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,K;
int a[MAXN];
ll dp[MAXN][10][10][3];
void upd(ll &a,ll b) {a=min(a,b);}
int main()
{
    scanf("%d%d",&n,&K);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=0;i<=n;i++)
        for(int j=0;j<=9;j++)
            for(int k=0;k<=9;k++)
                for(int l=0;l<3;l++)
                    dp[i][j][k][l]=INF;
    dp[0][0][0][1]=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<=K;j++)
            for(int k=0;k<=K;k++)
                for(int l=0;l<3;l++)
                {
                    if(dp[i][j][k][l]==INF) continue;
                    upd(dp[i+1][j][k][0],dp[i][j][k][l]+a[i+1]);
                    if(k!=K) upd(dp[i+1][j][k+1][0],dp[i][j][k][l]);
                    if(l!=2)
                    {
                        upd(dp[i+1][j][k][l+1],dp[i][j][k][l]);
                        if(j!=K) upd(dp[i+1][j+1][k][l+1],dp[i][j][k][l]+a[i+1]);
                    }
                }
    ll ans=INF;
    for(int i=0;i<=K;i++)
        for(int j=0;j<2;j++)
            ans=min(ans,dp[n][i][i][j]);
    printf("%lld\n",ans);
    return 0;
}
