#include<bits/stdc++.h>
#define MAXN 105
#define MAXM 10005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef long double db;
int n,x;
int a[MAXN];
db dp[2][MAXN][MAXM];
const db threshold=1e-12;
int main()
{
    scanf("%d%d",&n,&x);
    db s=0.0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        s+=a[i];
    }
    dp[0][0][0]=1.0;
    for(int i=0;i<n;i++)
    {
        int now=i&1,nxt=now^1;
        memset(dp[nxt],0,sizeof(dp[nxt]));
        for(int j=0;j<=i;j++)
        {
            for(int k=0;k<=10000;k++)
            {
                dp[nxt][j][k]+=dp[now][j][k];
                dp[nxt][j+1][k+a[i+1]]+=dp[now][j][k]*(j+1)/(n-j);
            }
        }
    }
    db ans=0.0;
    for(int i=0;i<=n-1;i++)
        for(int j=0;j<=s;j++)
            ans+=dp[n&1][i][j]*(min((s-j)/(n-i),((db)n/(n-i)+1)*x/2.0));
    printf("%.10Lf\n",ans);
    return 0;
}
