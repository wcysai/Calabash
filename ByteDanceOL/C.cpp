/*************************************************************************
    > File Name: C.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-12-01 13:29:22
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n;
struct edge {int to,t;};
vector<edge> G[MAXN];
int dp[MAXN];
vector<int> ans;
void dfs(int v,int p)
{
    dp[v]=0;
    for(auto e:G[v])
    {
        if(e.to==p) continue;
        dfs(e.to,v);
        if(e.t==1) dp[v]^=(dp[e.to]+1); 
        else if(e.t&1) {dp[v]^=dp[e.to]; dp[v]^=1;}
        else dp[v]^=dp[e.to];
    }
}
void dfs2(int v,int p,int need)
{
    for(auto e:G[v])
    {
        if(e.to==p) continue;
        if(e.t==1)
        {
            if((dp[v]^(1+dp[e.to]))==need) ans.push_back(e.to);
            if((dp[v]^(1+dp[e.to])^need)>0) dfs2(e.to,v,(dp[v]^(1+dp[e.to])^need)-1);
        }
        else if(e.t&1)
        {
            if((dp[v]^1)==need) ans.push_back(e.to);
            dfs2(e.to,v,(dp[v]^dp[e.to]^need));
        }
        else if(e.t==2)
        {
            if((dp[v]^(1+dp[e.to])^dp[e.to])==need) ans.push_back(e.to);
            dfs2(e.to,v,dp[v]^dp[e.to]^need);
        }
        else 
        {
            if((dp[v]^1)==need) ans.push_back(e.to);
            dfs2(e.to,v,(dp[v]^dp[e.to]^need));          
        }
    }
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=2;i<=n;i++)
        {
            int x,w;scanf("%d%d",&x,&w);
            G[x].push_back((edge){i,w});
            G[i].push_back((edge){x,w});
        }
        dfs(1,0);
        //for(int i=1;i<=n;i++) printf("%d %d\n",i,dp[i]);
        ans.clear();
        dfs2(1,0,0);
        sort(ans.begin(),ans.end());
        printf("%d\n",(int)ans.size());
        if((int)ans.size()==0) puts("");
        for(int i=0;i<(int)ans.size();i++)
            printf("%d%c",ans[i],i==(int)ans.size()-1?'\n':' ');
    }
    return 0;
}

