/*************************************************************************
    > File Name: L.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-11-29 15:58:04
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
int N,X,Y,a[MAXN],cnt0,cnt1,cnt2;
int dp[2][MAXN][3][4];
//dp[now][rem][last][mask]:
//currently at grid now
//still have rem 2s left
//the most recent grid is last
//the condition of used 0/1 is represented by mask
//encoded using rolling array
void relax(int &a,const int &b) {a=min(a,b);}
void clear(int x)
{
    for(int j=0;j<=cnt2;j++)
        for(int k=0;k<=2;k++)
            for(int l=0;l<=3;l++)
                dp[x][j][k][l]=INF;
}
int main()
{
    scanf("%d%d%d",&N,&X,&Y);
    cnt0=cnt1=cnt2=0;
    bool consec=false;
    for(int i=1;i<=N;i++) 
    {
        scanf("%d",&a[i]);
        if(a[i]==X) a[i]=0;
        else if(a[i]==Y) a[i]=1;
        else a[i]=2;
        if(a[i]==0) cnt0++;
        else if(a[i]==1) cnt1++;
        else cnt2++;
        if(i>1&&a[i]==2&&a[i-1]==2) consec=true;
    }
    if(cnt0==0||cnt1==0) {puts("0"); return 0;}
    else if(cnt2==0) {puts("-1"); return 0;}
    int ans=INF;
    if(a[N]==2||a[1]==2||consec) 
    {
        ans=min(ans,cnt0);
        ans=min(ans,cnt1);
    }
    else
    {
        ans=min(ans,cnt0+1);
        ans=min(ans,cnt1+1);
    }
    clear(0);clear(1);
    dp[0][cnt2][2][0]=cnt2;
    for(int i=0;i<N;i++)
    {
        int now=i&1,next=1-now;
        clear(next);
        for(int j=0;j<=cnt2;j++)
        {
            for(int last=0;last<=2;last++)
            {
                for(int mask=0;mask<=3;mask++)
                {
                    if(dp[now][j][last][mask]==INF) continue;
                    int cur=dp[now][j][last][mask];
                    if(a[i+1]==2)
                    {
                        relax(dp[next][j][last][mask],cur);
                        if(j>0) relax(dp[next][j-1][2][mask],cur-1);
                    }
                    else if(a[i+1]==0) 
                    {
                        relax(dp[next][j][last][mask],cur+1);
                        if(last!=1) relax(dp[next][j][0][mask|1],cur);
                        if(j>0) relax(dp[next][j-1][0][mask|1],cur);
                    }
                    else
                    {
                        relax(dp[next][j][last][mask],cur+1);
                        if(last!=0) relax(dp[next][j][1][mask|2],cur);
                        if(j>0) relax(dp[next][j-1][1][mask|2],cur);
                    }
                }
            }
        }
    }
    for(int j=0;j<=cnt2;j++)
        for(int last=0;last<=2;last++)
            relax(ans,dp[N&1][j][last][3]);
    printf("%d\n",ans);
    return 0;
}

