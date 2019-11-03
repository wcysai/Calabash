#include<bits/stdc++.h>
#define MAXN 1005
#define MAXK 55
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int N,K;
int a[MAXN];
int dp[2][MAXN][MAXN];
int opt[2][MAXN][MAXN];
int main()
{
    scanf("%d%d",&N,&K);
    for(int i=1;i<=N;i++) scanf("%d",&a[i]);
    sort(a+1,a+N+1);
    for(int i=1;i<=N;i++)
        for(int j=i;j<=N;j++)
        {
            dp[0][i][j]=(i==j?0:INF);
            opt[0][i][j]=i;
        }
    for(int k=1;k<=K;k++)
    {
        int now=k&1,last=now^1;
        for(int i=1;i<=N;i++)
            for(int j=i;j<=N;j++)
                dp[now][i][j]=INF;
        for(int len=1;len<=N;len++)
        {
            for(int i=1;i+len-1<=N;i++)
            {
                int j=i+len-1;
                if(len==1)
                {
                    dp[now][i][j]=0;
                    opt[now][i][j]=i;
                }
                for(int x=opt[now][i][j-1];x<=min(opt[now][i+1][j],j-1);x++)
                {
                    if(dp[last][i][x]+dp[last][x+1][j]+a[j]-a[x]<dp[now][i][j])
                    {
                        dp[now][i][j]=dp[last][i][x]+dp[last][x+1][j]+a[j]-a[x];
                        opt[now][i][j]=x;
                    }
                }
            }
        }
    }
    printf("%d\n",dp[K&1][1][N]);
    return 0;
}
