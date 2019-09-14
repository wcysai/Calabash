#include<bits/stdc++.h>
#define MAXN 10005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
struct edge{int to,cost;};
int n;
vector<edge> G[MAXN];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
int cnt[MAXN][3],dp[MAXN][3];
int ans[3];
void dfs(int v,int p)
{
    for(auto e:G[v])
    {
        int to=e.to,cost=e.cost;
        if(to==p) continue;
        dfs(to,v);
        for(int j=0;j<3;j++)
        {
            for(int k=0;k<3;k++)
            {
                int rem=(j+k+cost)%3;
                add(ans[rem],1LL*cnt[to][j]*dp[v][k]%MOD);
                add(ans[rem],1LL*dp[to][j]*cnt[v][k]%MOD);
                add(ans[rem],1LL*cnt[to][j]*cnt[v][k]%MOD*cost%MOD);
            }
        }
        for(int j=0;j<3;j++)
        {
            int rem=(cost+j)%3;
            add(cnt[v][rem],cnt[to][j]);
            add(dp[v][rem],(1LL*cnt[to][j]*cost+dp[to][j])%MOD);
        }
    }
    cnt[v][0]++;
    for(int j=0;j<3;j++) add(ans[j],dp[v][j]);
}
int main()
{
    while(scanf("%d",&n)==1)
    {
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=0;i<n-1;i++)
        {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            u++; v++;
            G[u].push_back((edge){v,w}); G[v].push_back((edge){u,w});
        }
        ans[0]=ans[1]=ans[2]=0;
        for(int i=1;i<=n;i++)
            for(int j=0;j<3;j++)
                cnt[i][j]=dp[i][j]=0;
        dfs(1,0);
        for(int j=0;j<3;j++) ans[j]=2LL*ans[j]%MOD;
        for(int j=0;j<3;j++) printf("%d%c",ans[j],j==2?'\n':' ');
    }
    return 0;
}
