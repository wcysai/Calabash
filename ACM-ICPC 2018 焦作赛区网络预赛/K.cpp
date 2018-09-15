/*************************************************************************
    > File Name: K.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-09-15 12:27:45
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 25
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,q,v[MAXN],c[MAXN];
int cnt[505],pow2[25];
int dp[405][10005];
int W=10000;
int main()
{
    pow2[0]=1;
    for(int i=1;i<=20;i++) pow2[i]=2LL*pow2[i-1]%MOD;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&q);
        for(int i=1;i<=n;i++) scanf("%d%d",&v[i],&c[i]);
        memset(dp,0,sizeof(dp));
        dp[0][0]=1;
        int tot=0;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<c[i+1];j++)
            {
                for(int k=0;k<=W;k++)
                {
                    if(!dp[tot][k]) continue;
                    dp[tot+1][k]=(dp[tot+1][k]+dp[tot][k])%MOD;
                    if(k+pow2[j]*v[i+1]<=W) dp[tot+1][k+pow2[j]*v[i+1]]=(dp[tot+1][k+pow2[j]*v[i+1]]+dp[tot][k])%MOD;
                }
                tot++;
            }
        }
        for(int i=0;i<q;i++)
        {
            int x;scanf("%d",&x);
            printf("%d\n",dp[tot][x]);
        }
    }
    return 0;
}
