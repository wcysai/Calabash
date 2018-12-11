#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 50005
#define MAXM 205
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int n,m;
vector<int> G[MAXN];
int dp[MAXN][MAXM][2],sz[MAXN];
int cur[MAXM][2],upd[MAXM][2];
//dp[i][j][0/1]: subtree at vertex i, j matchings in the subtree, i is unmatched/matched
void dfs(int v,int p)
{
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs(to,v);
    }
    memset(cur,0,sizeof(cur));
    cur[0][0]=1;
    sz[v]=1;
    for(auto to:G[v])
    {
        if(to==p) continue;
        memset(upd,0,sizeof(upd));
        for(int j=0;j<min(m,sz[to]+1);j++)
        {
            if(dp[to][j][1])
            {
                for(int i=0;i<min(m,sz[v]+1);i++) add(upd[(i+j)%m][0],2LL*cur[i][0]*dp[to][j][1]%MOD);
                for(int i=0;i<min(m,sz[v]+1);i++) add(upd[(i+j)%m][1],2LL*cur[i][1]*dp[to][j][1]%MOD);
            }
            if(dp[to][j][0])
            {
                for(int i=0;i<min(m,sz[v]+1);i++) add(upd[(i+j)%m][1],1LL*cur[i][0]*dp[to][j][0]%MOD);
                for(int i=0;i<min(m,sz[v]+1);i++) add(upd[(i+j)%m][0],1LL*cur[i][0]*dp[to][j][0]%MOD);
                for(int i=0;i<min(m,sz[v]+1);i++) add(upd[(i+j)%m][1],2LL*cur[i][1]*dp[to][j][0]%MOD);
            }
        }
        add(sz[v],sz[to]);
        for(int i=0;i<min(m,sz[v]+1);i++) cur[i][0]=upd[i][0],cur[i][1]=upd[i][1];
    }
    for(int i=0;i<min(m,sz[v]+1);i++) dp[v][i][0]=cur[i][0];
    for(int i=0;i<min(m,sz[v]+1);i++) dp[v][(i+1)%m][1]=cur[i][1];
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n-1;i++)
    {
        int u,v;scanf("%d%d",&u,&v);
        G[u].push_back(v);G[v].push_back(u);
    }
    memset(sz,0,sizeof(sz));
    memset(dp,0,sizeof(dp));dfs(1,0);
    int ans=0;add(ans,dp[1][0][0]);add(ans,dp[1][0][1]);
    printf("%d\n",ans);
    return 0;
}
