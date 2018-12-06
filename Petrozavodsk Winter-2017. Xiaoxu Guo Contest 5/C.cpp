/*************************************************************************
    > File Name: C.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-12-06 19:35:12
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
int n,m;
vector<int> G[MAXN];
int p3[15];
int dp[2][1600000];
void add(int &a,int b) {a+=b; if(a>=4) a-=4;}
//dp[i][mask] currently at node i, color of the recent 13 nodes represented by mask
//0:grey 1:black 2:white
//white and black nodes can't be adjacent
int main()
{
    scanf("%d%d",&n,&m);
    p3[0]=1;
    for(int i=1;i<=13;i++) p3[i]=3*p3[i-1];
    //printf("%d\n",p3[13]);
    for(int i=0;i<m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        if(u<v) G[v].push_back(u); else G[u].push_back(v);
    }
    memset(dp,0,sizeof(dp));
    dp[0][0]=1;
    for(int i=0;i<n;i++)
    {
        int next=(i+1)&1,now=1-next;
        memset(dp[next],0,sizeof(dp[next]));
        for(int mask=0;mask<p3[13];mask++)
        {
            if(!dp[now][mask]) continue;
            bool black=false,white=false;
            for(auto to:G[i+1])
            {
                int d=i+1-to;
                if((mask/p3[d-1])%3==1) black=true;
                if((mask/p3[d-1])%3==2) white=true;
            }
            int newmask=(mask%p3[12])*3;
            add(dp[next][newmask],dp[now][mask]);
            if(!black) add(dp[next][newmask+2],dp[now][mask]);
            if(!white) add(dp[next][newmask+1],dp[now][mask]);
        }
    }
    int ans=0;
    for(int mask=0;mask<p3[13];mask++) add(ans,dp[n&1][mask]);
    add(ans,3);
    assert(ans%2==0);
    if(ans==2) puts("1"); else puts("0");
    return 0;
}

