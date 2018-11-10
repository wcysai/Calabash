#include<bits/stdc++.h>
#define MAXN 500005
#define INF 1000000001
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
int n,m,a[MAXN],b[MAXN],dp[MAXN];
int ans=0;
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    fill(dp,dp+n,INF);
    for(int i=0;i<n;i++)
        *lower_bound(dp,dp+n,a[i])=a[i];
    ans+=lower_bound(dp,dp+n,INF)-dp;
    scanf("%d",&m);
    for(int i=0;i<m;i++) scanf("%d",&b[i]);
    fill(dp,dp+m,INF);
    for(int i=0;i<m;i++)
        *lower_bound(dp,dp+m,b[i])=b[i];
    ans+=lower_bound(dp,dp+m,INF)-dp;
    printf("%d\n",ans);
    return 0;
}
