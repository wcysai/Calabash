/*************************************************************************
    > File Name: E.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-07-19 15:28:44
 ************************************************************************/
 
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,p,a[MAXN],dp[MAXN][12][12],sum[MAXN][12];
int _mod(int x)
{
    if(x>=MOD) return x-MOD; else return x;
}
int main()
{
    while(scanf("%d%d%d",&n,&m,&p)==3)
    {
        for(int i=1;i<=n;i++)
            for(int j=0;j<=min(i,m);j++)
                for(int k=1;k<=p;k++) dp[i][j][k]=0;
        for(int i=1;i<=n;i++)
            for(int j=0;j<=min(i,m);j++) sum[i][j]=0;
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        dp[1][0][a[1]]=1;sum[1][0]=1;sum[1][1]=1;
        for(int i=2;i<=n;i++)
        {
            for(int j=0;j<=min(i-1,m);j++)
            {
                sum[i][j]=0;
                dp[i][j][a[i]]=sum[i-1][j];
                if(j>=1)
                {
                    for(int k=1;k<=p;k++)
                    {
                        if(k==a[i]) continue;
                        dp[i][j][k]=dp[i-1][j-1][k];
                    }
                }
                for(int k=1;k<=p;k++) sum[i][j]=_mod(sum[i][j]+dp[i][j][k]);
                //printf("%d ",sum[i][j]);
            }
            if(i<=m) sum[i][i]=1;
            //puts("");
        }
        //printf("dp%d\n",dp[2][1][2]);
        printf("%d\n",sum[n][m]);
    }
    return 0;
}
