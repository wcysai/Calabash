/*************************************************************************
    > File Name: C.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-07-28 13:15:58
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
int T,limit;
ll n;
vector<int> v;
int dp[65][125][2][2];
int abx(int x){return max(-x,x);}
int _mod(int x) {return x>=MOD?x-MOD:x;}
int dfs(int now,int sum,int flag,int last,int limit)
{
    if(now==-1) return abx(sum);
    if(!limit&&dp[now][sum+60][flag][last]!=-1) return dp[now][sum+60][flag][last];
    int ed=limit?v[now]:1;
    int res=0;
    for(int i=0;i<=ed;i++)
    {
        if(!flag) res+=dfs(now-1,sum,i,i,limit&&(i==ed));
        else
        {
            if(i^last) res+=dfs(now-1,sum-1,1,i,limit&&(i==ed));
            else res+=dfs(now-1,sum+1,1,i,limit&&(i==ed));
        }
    }
    res=_mod(res);
    if(!limit) dp[now][sum+60][flag][last]=res;
    return res;
}
int main()
{
    scanf("%d",&T);
    memset(dp,-1,sizeof(dp));
    while(T--)
    {
        v.clear();
        scanf("%lld",&n);
        while(n) {v.push_back(n&1); n>>=1;}
        limit=v.size();
        int ans=dfs(limit-1,0,0,0,1);
        printf("%d\n",ans);
    }
    return 0;
}
