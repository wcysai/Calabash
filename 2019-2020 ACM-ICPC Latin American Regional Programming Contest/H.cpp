#include<bits/stdc++.h>
#define MAXN 78
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef long double db;
db dp[MAXN][MAXN][MAXN];
db ddp[MAXN][MAXN][MAXN];
bool relaxed[MAXN][MAXN][MAXN];
db solve(int C,int H,int X)
{
    if(C==75) return 1.0;
    else if(H==75) return 0.0;
    if(C+X>75) return 1.0-dp[H][C][0];
    if(relaxed[C][H][X]) return dp[C][H][X];
    relaxed[C][H][X]=true;
    db res=0.0;
    res=1.0/6*(1.0-dp[H][C][0]); //rolls 1
    for(int i=2;i<=6;i++)
    {
        res+=1.0/6*solve(C,H,X+i);
    }
    if(X!=0) dp[C][H][X]=max(1.0-solve(H,C+X,0),res); //holds
    else dp[C][H][X]=res;
    return dp[C][H][X];
}
db hold(int C,int H,int X)
{
    return 1.0-solve(H,C+X,0);
}
db cont(int C,int H,int X)
{
    db res=1.0/6*(1.0-solve(H,C,0));
    for(int i=2;i<=6;i++) res+=1.0/6*solve(C,H,X+i);
    return res;
}
int Q;
int main()
{
    memset(dp,0,sizeof(dp));
    for(int iter=0;iter<200;iter++)
    {
        memset(relaxed,false,sizeof(relaxed));
        for(int i=0;i<=75;i++)
            for(int j=0;j<=75;j++)
                for(int k=0;i+k<=75;k++)
                    solve(i,j,k);
    }
    relaxed[0][0][0]=false;
    scanf("%d",&Q);
    while(Q--)
    {
        int C,H,X;
        scanf("%d%d%d",&C,&H,&X);
        if(hold(C,H,X)>cont(C,H,X)) puts("H"); else puts("C");
    }
    return 0;

}
