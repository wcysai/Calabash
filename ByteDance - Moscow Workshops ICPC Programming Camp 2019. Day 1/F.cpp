//
// Created by bytedance on 19-2-16.
//
#include <bits/stdc++.h>
#define MAXN 10005
#define MAXC 505
#define INF 1000000000
#define MOD 1000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,c;
vector<int> G[MAXN];
int dp[MAXN][MAXC];
int sum1[MAXC],sum2[MAXC],ans[MAXC];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
void dfs(int v,int p)
{
    dp[v][0]=1;dp[v][c]=1;
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs(to,v);
        fill(sum1, sum1+c+1, 0);
        fill(sum2, sum2+c+1, 0);
        fill(ans, ans+c+1, 0);
        sum1[c]=dp[v][c];
        for(int i=c-1;i>=0;i--)
        {
            sum1[i]=sum1[i+1];
            add(sum1[i],dp[v][i]);
        }
        sum2[c]=dp[to][c];
        for(int i=c-1;i>=0;i--)
        {
            sum2[i]=sum2[i+1];
            add(sum2[i],dp[to][i]);
        }
        ans[0]=1LL*dp[v][0]*sum2[c-1]%MOD;
        for(int i=1;i<=c;i++)
        {
            add(ans[i],1LL*dp[v][i]*sum2[max(i,c-i-1)]%MOD);
            add(ans[i],1LL*dp[to][i-1]*sum1[max(i,c-i)]%MOD);
        }
        for(int i=0;i<=c;i++) dp[v][i]=ans[i];
    }
}
int main()
{
    int tot=0;
    while(scanf("%d%d",&n,&c)==2)
    {
        tot++;
        if(!n&&!c) break;
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=1;i<=n;i++)
            for(int j=0;j<=c;j++)
                dp[i][j]=0;
        for(int i=0;i<n-1;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            G[u].push_back(v);G[v].push_back(u);
        }
        dfs(1,0);
        int res=0;
        for(int i=0;i<=c;i++) add(res,dp[1][i]);
        printf("Case #%d: %d\n",tot,res);
    }
}
