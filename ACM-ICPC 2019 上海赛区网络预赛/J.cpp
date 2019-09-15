#include<bits/stdc++.h>
#define MAXN 305
#define MAXM 150005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,a[MAXN];
int dp[MAXN][MAXM];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;           }
int main()
{
    scanf("%d",&T);
    for(int tot=1;tot<=T;tot++)
    {
        scanf("%d",&n);
        int sum=0;
        for(int i=0;i<n;i++)
        {
            scanf("%d",&a[i]);
            sum+=a[i];
        }
        int need=(sum+1)/2;
        sort(a,a+n,greater<int>());
        memset(dp,0,sizeof(dp));
        dp[0][0]=1;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<=min(sum,i*500);j++)
            {
                if(!dp[i][j]) continue;
                add(dp[i+1][j],dp[i][j]);
                add(dp[i+1][j+a[i]],dp[i][j]);
            }
        }
        int ans=0;
        for(int i=n-1;i>=0;i--)
            for(int j=0;j<=sum;j++)
                if(j+a[i]>=sum-(j+a[i])&&j<=sum-(j+a[i])) add(ans,dp[i][j]);
        printf("%d\n",ans);
    }
    return 0;
}
