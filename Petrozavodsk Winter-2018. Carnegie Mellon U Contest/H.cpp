#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
P dp[1<<24];
ll n,s;
int w[25];
int main()
{
    scanf("%d%d",&n,&s);
    for(ll i=0;i<n;i++) scanf("%d",&w[i]);
    dp[0]=P(1,0);
    for(int i=1;i<(1<<n);i++)
    {
        dp[i]=P(100,0);
        for(int j=0;j<n;j++)
        {
            if(i&(1<<j))
            {
                if(dp[i^(1<<j)].S+w[j]<=s) dp[i]=min(dp[i],P(dp[i^(1<<j)].F,dp[i^(1<<j)].S+w[j]));
                dp[i]=min(dp[i],P(dp[i^(1<<j)].F+1,min(dp[i^(1<<j)].S,w[j])));
            }
        }
    }
    printf("%d\n",dp[(1<<n)-1].F);
    return 0;
}
