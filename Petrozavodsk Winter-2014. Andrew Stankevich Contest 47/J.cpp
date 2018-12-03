/*************************************************************************
    > File Name: J.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-12-03 16:26:46
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 2005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int h,w,sum[MAXN][MAXN],l[MAXN][MAXN],u[MAXN][MAXN],dp[MAXN][MAXN];
char str[MAXN][MAXN];
int ans;
void solve()
{
    for(int i=1;i<=h;i++)
    {
        for(int j=1;j<=w;j++)
        {
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+(str[i][j]=='#'?1:0);
            l[i][j]=j;if(str[i][j-1]=='#') l[i][j]=l[i][j-1];
            u[i][j]=i;if(str[i-1][j]=='#') u[i][j]=u[i-1][j];
        }
    }
    for(int i=1;i<=h;i++)
        for(int j=1;j<=w;j++)
            dp[i][j]=0;
    for(int i=1;i<=h;i++)
    {
        for(int j=1;j<=w;j++)
        {
            if(str[i][j]!='#'||sum[i-1][j-1]==0) continue;
            dp[i][j]=dp[u[i][j]][l[i][j]]+1;
            ans=max(ans,dp[i][j]);
        }
    }
}
int main()
{
    freopen("jinxiety.in","r",stdin);
    freopen("jinxiety.out","w",stdout);
    while(scanf("%d%d",&h,&w)==2)
    {
        if(!h&&!w) break;
        ans=0;
        for(int i=1;i<=h;i++) scanf("%s",str[i]+1);
        solve();
        for(int i=1;i<=h;i++) reverse(str[i]+1,str[i]+w+1);
        solve();
        printf("%d\n",ans);
    }
    return 0;
}

