/*************************************************************************
    > File Name: D.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-12-01 16:50:36
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 505
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n;
char str[MAXN];
P dp[512][512][2][2][2];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD; if(a<0) a+=MOD;}
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
P solve(int now,int last,int less,int greater,int has)
{
    if(now==n+1) return P(1,0);
    if(dp[now][last][less][greater][has].F!=-1) return dp[now][last][less][greater][has];
    dp[now][last][less][greater][has]=P(0,0);
    P &cur=dp[now][last][less][greater][has];
    for(int i=0;i<=1;i++)
    {
        for(int j=0;j<=1;j++)
        {
            if(i<j&&!less) continue;
            if(i>str[now]-'0'&&!greater) continue;
            P p=solve(now+1,(i==1&&j==0?now:last),(less||j<i),(greater||(str[now]-'0'>i)),(i==0&&j==1)||has);
            add(cur.S,p.S);
            add(cur.F,p.F);
            if(!has&&i==0&&j==1) add(cur.S,1LL*(n-last)*p.F%MOD);
            if(i==1) add(cur.S,p.F);
            if(j==1) add(cur.S,-p.F);
        }
    }
    //printf("%d %d %d %d %d %d\n",now,last,less,greater,has,cur.S);
    return cur;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",str+1);
        n=strlen(str+1);
        for(int i=0;i<=n;i++)
            for(int ii=0;ii<=n;ii++)
                for(int j=0;j<=1;j++)
                    for(int k=0;k<=1;k++)
                        for(int l=0;l<=1;l++)
                            dp[i][ii][j][k][l]=P(-1,-1);
       printf("%d\n",solve(1,0,0,0,0).S); 
    }
    return 0;
}

