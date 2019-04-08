#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#define INT64 "%lld"
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF=(1LL<<61)-1;

ll hp[3],atk[3];
ll dp[100][200][200];

ll K(ll h)
{
    ll t=(sqrtl(1+8*h)-1)/2;
    while(t*(t+1)/2>h)t--;
    while(t*(t+1)/2<h)t++;
    return t;
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        for(int i=0;i<3;i++)
            scanf(INT64,&hp[i]);
        for(int i=0;i<3;i++)
            scanf(INT64,&atk[i]);
        for(int i=0;i<100;i++)
            for(int j=0;j<200;j++)
                for(int k=0;k<200;k++)
                    dp[i][j][k]=INF;
        dp[0][0][0]=0;
        for(int i=1;i<100;i++)
            for(int j=0;j<200;j++)
                for(int k=0;k<200;k++)
                    if(dp[i-1][j][k]<INF)
                    {
                        ll cost=atk[0]*(j<hp[0])+atk[1]*(k<hp[1])+atk[2]*(i*(i-1)/2-j-k<hp[2]);
                        if(j<hp[0])dp[i][j+i][k]=min(dp[i][j+i][k],dp[i-1][j][k]+cost);
                        if(k<hp[1])dp[i][j][k+i]=min(dp[i][j][k+i],dp[i-1][j][k]+cost);
                        if(i*(i-1)/2-j-k<hp[2])dp[i][j][k]=min(dp[i][j][k],dp[i-1][j][k]+cost);
                    }
        ll res=INF;
        for(int i=0;i<100;i++)
            for(int j=0;j<200;j++)
                for(int k=0;k<200;k++)
                    if(dp[i][j][k]<INF && j>=hp[0] && k>=hp[1] && i*(i+1)/2-j-k>=hp[2])
                        res=min(res,dp[i][j][k]);
        for(int i=99;i<100;i++)
            for(int j=0;j<200;j++)
                for(int k=0;k<200;k++)
                    if(dp[i][j][k]<INF)
                    {
                        ll satk[2]={atk[0]*(j<hp[0]),atk[1]*(k<hp[1])};
                        if(satk[0]>satk[1])swap(satk[0],satk[1]);
                        ll t=K(max(1LL*i*(i+1)/2,hp[2]+j+k));
                        res=min(res,dp[i][j][k]+(t+2-i)*satk[0]+(t+1-i)*satk[1]+(t-i)*atk[2]);
                    }
        printf(INT64 "\n",res);
    }
    return 0;
}
