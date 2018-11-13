#include<bits/stdc++.h>
#define MAXN 305
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define next dfksiofkosd
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
int n;
P a[MAXN];
int dp[2][MAXN][MAXN];
int cnt[MAXN];
bool cmp(P x,P y) {return x.F>y.F;}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&a[i].F,&a[i].S);
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++)
        for(int j=1;j<i;j++)
            if(a[j].S>a[i].F) cnt[i]++;
    dp[0][0][0]=1;
    for(int i=0;i<n;i++)
    {
        int now=i&1,next=(i+1)&1;
        memset(dp[next],0,sizeof(dp[next]));
        for(int j=0;j<=i;j++)
        {
            int num=cnt[i+1]-(i-j);
            for(int k=0;k<=num;k++)
            {
                if(!dp[now][j][k]) continue;
                if(num>=0) add(dp[next][j+1][num],dp[now][j][k]);
                if(k) add(dp[next][j][k-1],1LL*k*dp[now][j][k]%MOD);
                add(dp[next][j][k],1LL*(num-k)*dp[now][j][k]%MOD);
            }
        }
    }
    int ans=0;
    for(int i=0;i<=n;i++) add(ans,dp[n&1][i][0]);
    printf("%d\n",ans);
    return 0;
}
